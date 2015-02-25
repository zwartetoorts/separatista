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
#include "documentiterator.h"
#include "debug/debug.h"

using namespace Separatista;

DOMDocumentIterator::DOMDocumentIterator(Separatista::DOMDocument *pDocument)
{
	// Move to first sepa element
	m_pElement = pDocument->getDocumentElement();
	if (m_pElement)
		m_pElement = m_pElement->getFirstElementChild();
}

DOMElement* DOMDocumentIterator::findElement(Element &element)
{
	DOMElement *pElement;

	// Enumerate all sibblings to find element
	for (pElement = m_pElement; pElement != NULL; pElement = pElement->getNextElementSibling())
	{
		// Compare tags
		if (std::wcscmp(pElement->getTagName(), element.getTag()) == 0)
			return pElement;
	}

	// Not found
	return NULL;
}

bool DOMDocumentIterator::fromDOMDocument(Element &element, const Element::ErrorOptions errorOptions)
{
	
	DOMElement *pElement;

	pElement = findElement(element);
	if (pElement)
	{
		// Don't iterate into leaf elements
		if (pElement->getFirstElementChild() != NULL)
			m_pElement = pElement->getFirstElementChild();
		element.fromDOMDocument(*this, errorOptions);
		m_pElement = pElement->getNextElementSibling();
		return true;
	}


	// Element wasn't found, check if it is allowed to be missing
	if (element.getOptions() != Element::Optional)
		throw MissingElementException(SEPARATISTA_EXCEPTION("Element is not optional"), &element);
	return false;
}

const wchar_t *DOMDocumentIterator::getTextValue() const
{
	if (m_pElement)
		return m_pElement->getTextContent();
	return NULL;
}

bool DOMDocumentIterator::isDone() const
{
	return m_pElement == NULL ? true : false;
}