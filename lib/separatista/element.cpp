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

#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLDateTime.hpp>
#include <xercesc/framework/psvi/XSValue.hpp>

#include "separatista.h"
#include "element.h"
#include "debug/debug.h"

using namespace Separatista;

Element::Element(const ElementDescriptor *pElementDescriptor)
{
	DEBUG_METHOD;

	m_pElementDescriptor = pElementDescriptor;
}

const ElementDescriptor* Element::getElementDescriptor() const
{
	DEBUG_METHOD;

	return m_pElementDescriptor;
}

void Element::addElementListener(ElementListener *pElementListener)
{
	DEBUG_METHOD;

	m_ElementListeners.push_back(pElementListener);
}

void Element::removeElementListener(ElementListener *pElementListener)
{
	DEBUG_METHOD;

	m_ElementListeners.erase(std::remove(m_ElementListeners.begin(), m_ElementListeners.end(), pElementListener), m_ElementListeners.end());
}

const wchar_t* Element::getTag() const
{
	DEBUG_METHOD
	return m_pElementDescriptor->m_pTag;
}

Element* Element::getElementByTag(const wchar_t *pTagName, size_t nIndex) const
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Child elements not supported by this element")), this);
}

Element* Element::createElementByTag(const wchar_t *pTagName, size_t nIndex)
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Child elements not supported by this element")), this);
}

void Element::destroyElement(Element *pElement)
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Child elements not supported by this element.")), this);
}

void Element::deleteElement(Element *pParentElement, Element *pChildElement)
{
	DEBUG_METHOD;
	pParentElement->onElementDeleted(pChildElement);
	delete pChildElement;
}

Element::TagKeyRange Element::getAllByTagName(const wchar_t *pTagName)
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Child elements not supported by this element")), this);
}

const wchar_t* Element::getTextValue() const
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Values not supported by this element")), this);
}

void Element::setValue(const wchar_t *pValue, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Values not supported by this element")), this);
}

const wchar_t* Element::getAttributeValue(const wchar_t *pAtributeName) const
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Attributes not supported by this element")), this);
}

void Element::setAttributeValue(const wchar_t *pAttributeName, const wchar_t *pValue)
{
	DEBUG_METHOD;
	throw ElementException(SEPARATISTA_EXCEPTION(TEXT("Attributes not supported by this element")), this);
}

void Element::onElementValueChanged(const wchar_t *pNewValue)
{
	DEBUG_METHOD;

	for(auto it = m_ElementListeners.begin(); it != m_ElementListeners.end(); it++)
		(*it)->elementValueChanged(this, pNewValue);
}

void Element::onElementCreated(Element *pChildElement)
{
	DEBUG_METHOD;

	for (auto it = m_ElementListeners.begin(); it != m_ElementListeners.end(); it++)
		(*it)->elementCreated(this, pChildElement);
}

void Element::onElementDeleted(Element *pChildElement)
{
	DEBUG_METHOD;

	for (auto it = m_ElementListeners.begin(); it != m_ElementListeners.end(); it++)
		(*it)->elementDeleted(this, pChildElement);
}

time_t Element::getDateValue() const
{
	DEBUG_METHOD;

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

void Element::setValue(const time_t Value, bool bWithTime, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

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
		setValue(xmlch, errorOptions);
		xercesc::XMLString::release(&xmlch);
	}

}

int Element::getIntValue() const
{
	DEBUG_METHOD;

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

void Element::setValue(const int Value, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	std::wstring w = std::to_wstring(Value);

	setValue(w.data(), errorOptions);
}

double Element::getDoubleValue() const
{
	DEBUG_METHOD;

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

void Element::setValue(const double d, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	std::wostringstream wos;

	wos.imbue(std::locale::classic());
	wos << std::setprecision(2) << std::fixed << d;
	setValue(wos.str().data(), errorOptions);
}

bool Element::isEmpty() const
{
	DEBUG_METHOD;

	return std::wcslen(getTextValue()) == 0;
}

Element::TagKey::TagKey(const wchar_t *pTagName, size_t nIndex, const ElementDescriptor *pBranchElementDescriptor)
{
	DEBUG_METHOD;

	m_nIndex = nIndex;
	m_pTagName = pTagName;
	m_nHash = HashKey(pTagName);
	m_pBranchElementDescriptor = pBranchElementDescriptor;
}

bool Element::TagKey::operator<(const TagKey & Other) const
{
	DEBUG_METHOD;

	// If both tags are the same, the index makes the difference
	if (m_nHash == Other.m_nHash && std::wcscmp(m_pTagName, Other.m_pTagName) == 0)
		return m_nIndex < Other.m_nIndex;

	// The first tag found is the lesser value
	for (size_t i = 0; i < m_pBranchElementDescriptor->m_nElementCount; i++)
	{
		if (m_pBranchElementDescriptor->m_pElements[i].m_nHash == m_nHash && std::wcscmp(m_pBranchElementDescriptor->m_pElements[i].m_pTag, m_pTagName) == 0)
			return true;
		else if (m_pBranchElementDescriptor->m_pElements[i].m_nHash == Other.m_nHash && std::wcscmp(m_pBranchElementDescriptor->m_pElements[i].m_pTag, Other.m_pTagName) == 0)
			return false;
	}

	return false;
}

bool Element::TagKey::operator==(const TagKey & Other) const
{
	DEBUG_METHOD;

	return (m_nHash == Other.m_nHash && std::wcscmp(m_pTagName, Other.m_pTagName) == 0) ? m_nIndex == Other.m_nIndex : false;
}

unsigned int Element::TagKey::getHash() const
{
	DEBUG_METHOD;

	return m_nHash;
}

const wchar_t* Element::TagKey::getTagName() const
{
	DEBUG_METHOD;

	return m_pTagName;
}

unsigned int Element::TagKey::HashKey(const wchar_t *pTagName)
{
	DEBUG_METHOD;

	unsigned int hash = 0;

	size_t len = std::wcslen(pTagName);
	for (size_t n = 0; n < len; n++)
		hash += (pTagName[n] << n);
	return hash;
}
