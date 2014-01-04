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

DOMElement* Element::getChildElement(const wchar_t *pTagName, bool create)
{
	DOMElement *pChild = NULL;

	if (!m_pDocument || !m_pDOMElement)
		return NULL;

	for (pChild = m_pDOMElement->getFirstElementChild(); pChild != NULL; pChild = pChild->getNextElementSibling())
	{
		if (XMLString::compareString(pChild->getTagName(), pTagName) == 0)
			return pChild;
	}
	
	// Not found, so try to create and append
	if (!create)
		return NULL;

	try
	{
		pChild = m_pDocument->createElement(pTagName);
		if (!pChild)
			return NULL;

		m_pDOMElement->appendChild(pChild);
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
