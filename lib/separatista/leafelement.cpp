/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
*   info@vanhetland.nl   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include <string>
#include <sstream>
#include <iomanip>

#include <xercesc/util/XMLDateTime.hpp>
#include <xercesc/framework/psvi/XSValue.hpp>

#include "separatista.h"
#include "leafelement.h"

using namespace Separatista;

LeafElement::LeafElement(const wchar_t *pTagName) :
Element(pTagName)
{

}

xercesc::DOMElement* LeafElement::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement;

	// Check for value
	if (isEmpty())
		return NULL;

	// Create element and set value
	pElement = createElement(pDocument, pParent);
	if (pElement)
		pElement->setTextContent(m_value.data());

	return pElement;
}

void LeafElement::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		setValue(pElementIterator->getCurrentElement()->getTextContent());
		pElementIterator->nextElement();
	}
}

void LeafElement::clear()
{
	m_value.clear();
	onDeleted();
}

const wchar_t* LeafElement::getTextValue() const
{
	return m_value.data();
}

void LeafElement::setValue(const wchar_t *pValue)
{
	m_value = pValue;
	onValueChanged(pValue);
}

time_t LeafElement::getDateValue() const
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;
	std::tm tm;

	const XMLCh *pText = getTextValue();

	if (!pText)
		return -1;

	// Try dateTime
	pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_dateTime, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
	{
		// Try date only
		pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_date, status);
		if (!pValue || status != xercesc::XSValue::st_Init)
			return -1;
	}

	tm.tm_year = pValue->fData.fValue.f_datetime.f_year - 1900;
	tm.tm_mon = pValue->fData.fValue.f_datetime.f_month - 1;
	tm.tm_mday = pValue->fData.fValue.f_datetime.f_day;
	tm.tm_hour = pValue->fData.fValue.f_datetime.f_hour;
	tm.tm_min = pValue->fData.fValue.f_datetime.f_min;
	tm.tm_sec = pValue->fData.fValue.f_datetime.f_milisec / 1000;

	return std::mktime(&tm);
}

void LeafElement::setValue(const time_t Value, bool bWithTime)
{
	tm *ptm;
	char buffer[64];

	ptm = std::localtime(&Value);
	if (!ptm)
		return;

	if (bWithTime)
		strftime(buffer, 64, "%Y-%m-%dT%H:%M:%S", ptm);
	else
		strftime(buffer, 64, "%Y-%m-%d", ptm);

	XMLCh *xmlch = xercesc::XMLString::transcode(buffer);
	if (xmlch)
	{
		setValue(xmlch);
		xercesc::XMLString::release(&xmlch);
	}

}

int LeafElement::getIntValue() const
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;
	const XMLCh *pText = getTextValue();

	if (!pText)
		return 0;

	pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_int, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
		return 0;

	return pValue->fData.fValue.f_int;
}

void LeafElement::setValue(const int Value)
{
	std::wstring w = std::to_wstring(Value);

	setValue(w.data());
}

double LeafElement::getDoubleValue() const
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;
	const XMLCh *pText = getTextValue();

	if (!pText)
		return (double)0;

	pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_double, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
		return (double)0;

	return pValue->fData.fValue.f_double;
}

void LeafElement::setValue(double d)
{
	std::wostringstream wos;

	wos.imbue(std::locale::classic());
	wos << std::setprecision(2) << std::fixed << d;
	setValue(wos.str().data());
}

bool LeafElement::isEmpty() const
{
	return m_value.empty();
}

