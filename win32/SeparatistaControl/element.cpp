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

#include <windows.h>
#include <olectl.h>
#include <string>
#include <sstream>

#include <xercesc/util/XMLDateTime.hpp>
#include <xercesc/framework/psvi/XSValue.hpp>

#include "element.h"

Element::Element(const wchar_t *pName)
{
	m_pTag = pName;
	m_pElementListener = NULL;
}

xercesc::DOMElement* Element::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, bool bForce)
{
	xercesc::DOMElement *pElement;

	// Check for empty value
	if (!bForce && m_value.empty())
		return NULL;

	try
	{
		pElement = pDocument->createElement(m_pTag);
		if (pElement)
		{
			// Set text content, if any
			if (!m_value.empty())
				pElement->setTextContent(m_value.data());
			pParent->appendChild(pElement);
		}
	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		return NULL;
	}

	return pElement;
}

Element::~Element()
{
}

ElementListener* Element::setElementListener(ElementListener *pElementListener)
{
	ElementListener *pOld = m_pElementListener;
	m_pElementListener = pElementListener;
	return pOld;
}

const wchar_t* Element::getTag() const
{
	return m_pTag;
}

void Element::Delete()
{
	m_value.clear();
	onDeleted();
}

const XMLCh* Element::getTextValue() const
{
	return m_value.data();
}

void Element::setValue(const XMLCh *pValue)
{
	m_value = pValue;
	onValueChanged();
}

time_t Element::getDateValue() const
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;
	std::tm tm;

	const XMLCh *pText = getTextValue();

	if (!pText)
		return -1;

	pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_dateTime, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
		return -1;

	tm.tm_year = pValue->fData.fValue.f_datetime.f_year - 1900;
	tm.tm_mon = pValue->fData.fValue.f_datetime.f_month - 1;
	tm.tm_mday = pValue->fData.fValue.f_datetime.f_day;
	tm.tm_hour = pValue->fData.fValue.f_datetime.f_hour;
	tm.tm_min = pValue->fData.fValue.f_datetime.f_min;
	tm.tm_sec = pValue->fData.fValue.f_datetime.f_milisec / 1000;

	return std::mktime(&tm);
}

void Element::setValue(const time_t Value)
{
	tm *ptm;
	char buffer[64];

	ptm = std::localtime(&Value);
	strftime(buffer, 64, "%Y-%m-%dT%H:%M:%S", ptm);

	XMLCh *xmlch = xercesc::XMLString::transcode(buffer);
	if (xmlch)
	{
		setValue(xmlch);
		xercesc::XMLString::release(&xmlch);
	}

}

int Element::getIntValue() const
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

void Element::setValue(const int Value)
{
	std::wstring w = std::to_wstring(Value);

	setValue(w.data());
}

void Element::onValueChanged()
{
	if (m_pElementListener)
		m_pElementListener->elementValueChanged(this, m_value.data());
}

void Element::onDeleted()
{
	if (m_pElementListener)
		m_pElementListener->elementDeleted(this);
}

double Element::getDoubleValue() const
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

void Element::setValue(double d)
{
	std::wostringstream wos;

	wos.imbue(std::locale::classic());
	wos.precision(2);
	wos << d;
	setValue(wos.str().data());
}

