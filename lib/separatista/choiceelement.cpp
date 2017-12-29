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

#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/choiceelement.h"
#include "separatista/debug/debug.h"

using namespace Separatista;

ChoiceElement::ChoiceElement(const ChildElementDescriptor *pChildElementDescriptor)
	:Element(pChildElementDescriptor)
{
	DEBUG_METHOD;

	m_pChosenElement = NULL;
}

ChoiceElement::~ChoiceElement()
{
	DEBUG_METHOD;
	Element *pElement;

	pElement = m_pChosenElement;
	m_pChosenElement = NULL;
	if (pElement)
		Element::deleteElement(pElement);
}

void ChoiceElement::fromDOMDocument(xercesc::DOMElement * pDOMElement, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	// Check current tag
	if (std::wcscmp(pDOMElement->getTagName(), getTag()) != 0)
		return;

	// Get the first child tag name
	xercesc::DOMElement *pDOMChildElement = pDOMElement->getFirstElementChild();
	if (!pDOMChildElement)
		return;

	const wchar_t *pDOMChildTagName = pDOMChildElement->getTagName();
	if (!pDOMChildTagName)
		return;

	// Construct a new element from the first child tag
	Element *pElement = createElementByTag(pDOMChildTagName);
	if (pElement)
	{
		pElement->fromDOMDocument(pDOMChildElement, errorOptions);
	}
	else
	{
		LOG(TEXT("BAD: Unsupported tag:"));
		LOG(pDOMChildTagName);
	}
}

IOErrorCode ChoiceElement::toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pDOMParent, const ErrorOptions errorOptions) const
{
	DEBUG_METHOD;

	xercesc::DOMElement *pChildElement = NULL;
	IOErrorCode ret = Success;

	// Create tag and call toDOMDocument
	try
	{
		pChildElement = pDOMDocument->createElementNS(pDOMParent->getNamespaceURI(), getTag());
		if (pChildElement)
		{
			pDOMParent->appendChild(pChildElement);
			if (m_pChosenElement)
			{
				ret = m_pChosenElement->toDOMDocument(pDOMDocument, pChildElement, errorOptions);
				if (ret != Success)
					return ret;
			}
		}
	}
	catch (const xercesc::DOMException &e)
	{
		if (pChildElement)
			delete pChildElement;
		switch(errorOptions)
		{
			case ThrowExceptions:
				SEPARATISTA_THROW_EXCEPTION(ElementException, e.getMessage(), this);
			default:
				ret = Xerces;
				SEPARATISTA_REPORT(e);
		}
	}
	return ret;
}

Element* ChoiceElement::createElement(const ChildElementDescriptor *pChildElementDescriptor)
{
	DEBUG_STATIC_METHOD;

	return new ChoiceElement(pChildElementDescriptor);
}

Element* ChoiceElement::getElementByTag(const wchar_t *pTagName, size_t nIndex) const
{
	DEBUG_METHOD;

	if (m_pChosenElement && std::wcscmp(m_pChosenElement->getTag(), pTagName) == 0)
		return m_pChosenElement;

	return NULL;
}

Element* ChoiceElement::createElementByTag(const wchar_t *pTagName, size_t nIndex)
{
	DEBUG_METHOD;

	Element *pElement;
	const ElementDescriptor *pElementDescriptor;
	unsigned int nHash;

	pElement = getElementByTag(pTagName, nIndex);
	if (pElement)
		return pElement;

	// Find ElementDesriptor for tag
	nHash = Element::TagKey::HashKey(pTagName);
	pElementDescriptor = getElementDescriptor();
	for (size_t i = 0; i < pElementDescriptor->m_nElementCount; i++)
	{
		if (pElementDescriptor->m_pChildren[i].m_nHash == nHash && std::wcscmp(pElementDescriptor->m_pChildren[i].m_pTag, pTagName) == 0)
		{
			// Found, create element and destroy old one on success.
			pElement = pElementDescriptor->m_pChildren[i].m_pElementDescriptor->m_pfCreateElement(&pElementDescriptor->m_pChildren[i]);
			if (pElement)
			{
				if (m_pChosenElement)
					Element::deleteElement(m_pChosenElement);
				m_pChosenElement = pElement;
				onElementCreated(pElement);
				return pElement;
			}
		}
	}
	// Not found, wrong tag or tag not supported 
	SEPARATISTA_THROW_EXCEPTION(UnsupportedTagException, TEXT("Unsupported tag"), this, pTagName);
}

void ChoiceElement::destroyElement(Element *pElement)
{
	DEBUG_METHOD;

	if (m_pChosenElement == pElement)
	{
		m_pChosenElement = NULL;
		Element::deleteElement(pElement);
	}
	else
	{
		LOG(TEXT("BAD: Destroying element that's not ours:"));
		LOG(pElement->getTag());
	}
}
