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

#include <xercesc/util/XMLString.hpp>

#include "element.h"

using namespace Separatista;
XERCES_CPP_NAMESPACE_USE

Element::Element()
{
	m_pDOMElement = NULL;
	m_pDocument = NULL;
}

Element::Element(DOMDocument *pDocument, DOMElement *pElement)
{
	m_pDocument = pDocument;
	m_pDOMElement = pElement;
}

Element::Element(DOMDocument *pDocument, DOMElement *pElement, const wchar_t *pTagName, bool create)
{
	m_pDocument = pDocument;
	m_pDOMElement = pElement;
	m_pDOMElement = getChildElement(pTagName, create);
}

const wchar_t* const* Element::getOrder()
{
	return NULL;
}

void Element::setDOMDocument(DOMDocument *pDocument)
{
	m_pDocument = pDocument;
}

DOMElement* Element::getDOMElement() const
{
	return m_pDOMElement;
}

void Element::setDOMElement(DOMElement *pElement)
{
	m_pDOMElement = pElement;
}

DOMElement* Element::getChildElement(unsigned int index, const wchar_t *pTagName, bool create)
{
	DOMElement *pChild = NULL;
	DOMNodeList *pNodeList;

	if (!m_pDocument || !m_pDOMElement)
		return NULL;
	
	// Check bounds
	pNodeList = m_pDOMElement->getElementsByTagName(pTagName);
	if (pNodeList != NULL && index < pNodeList->getLength())
		return (DOMElement*)pNodeList->item(index);

	// Not found, so try to create and append
	if (!create)
		return NULL;

	try
	{
		pChild = m_pDocument->createElement(pTagName);
		if (!pChild)
			return NULL;

		insertChildElement(pChild);
	}
	catch (...)
	{
		if (pChild)
		{
			pChild->release();
			pChild = NULL;
		}
	}
	return pChild;
}

DOMElement* Element::getChildElement(const wchar_t *pTagName, bool create)
{
	return getChildElement(0, pTagName, create);
}

const wchar_t* Element::getChildElementValue(const wchar_t *pTagName)
{
	return getChildElementValue(0, pTagName);
}

const wchar_t* Element::getChildElementValue(unsigned int index, const wchar_t *pTagName)
{
	DOMElement *pElement;

	try
	{
		pElement = getChildElement(index, pTagName, false);
		if (!pElement)
			return NULL;

		return pElement->getTextContent();
	}
	catch (const DOMException &e)
	{
		return NULL;
	}

}

void Element::setChildElementValue(const wchar_t *pTagName, const wchar_t *pValue)
{
	setChildElementValue(0, pTagName, pValue);
}

void Element::setChildElementValue(unsigned int index, const wchar_t *pTagName, const wchar_t *pValue)
{
	DOMElement *pElement;

	try
	{
		pElement = getChildElement(index, pTagName, true);
		if (!pElement)
			return;

		pElement->setTextContent(pValue);
	}
	catch (const DOMException &e)
	{
		return;
	}
}

DOMNodeList* Element::getElementsByTagName(const wchar_t *pTagName)
{
	if (!m_pDOMElement)
		return NULL;

	return m_pDOMElement->getElementsByTagName(pTagName);
}

void Element::insertChildElement(DOMElement *pElement)
{
	const wchar_t* const *ppOrder;
	const wchar_t *pTagName;

	if (!m_pDOMElement)
		return;

	pTagName = pElement->getTagName();
	
	// Keep searching the order table for pTagName
	bool bFound = false;
	for (ppOrder = getOrder(); ppOrder != NULL && *ppOrder != NULL; ppOrder++)
	{
		if (!bFound &&  XMLString::compareIString(*ppOrder, pTagName) == 0)
			bFound = true;
		else
		{
			// We found the next tag in the order table, try to find a child element by this name
			DOMElement *pSibbling = getChildElement(*ppOrder);
			if (pSibbling)
			{
				m_pDOMElement->insertBefore(pElement, pSibbling);
				return;
			}
			// No sibbling was found by this name, try the next in order
		}
	}

	// Not found or no order, so append at end
	m_pDOMElement->appendChild(pElement);
}

