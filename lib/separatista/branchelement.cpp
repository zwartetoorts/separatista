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
#include <xercesc/dom/DOMDocumentTraversal.hpp>

#include "separatista.h"
#include "xerces_types.h"
#include "branchelement.h"
#include "debug/debug.h"

using namespace Separatista;

BranchElement::BranchElement(const ElementDescriptor *pElementDescriptor) :
Element(pElementDescriptor)
{
	DEBUG_METHOD
}

Separatista::BranchElement::~BranchElement()
{
	DEBUG_METHOD;
	for (auto it = m_childElements.begin(); it != m_childElements.end(); it++)
		Element::deleteElement(this, it->second);
}

Element* BranchElement::createElement(const ElementDescriptor *pElementDescriptor)
{
	DEBUG_METHOD;

	return new BranchElement(pElementDescriptor);
}

Element* BranchElement::getElementByTag(const wchar_t *pTag, size_t nIndex) const
{
	auto element = m_childElements.find(TagKey(pTag, nIndex, getElementDescriptor()));
	if (element == m_childElements.end())
		return NULL;
	
	return (*element).second;
}

Element* BranchElement::createElementByTag(const wchar_t *pTag, size_t nIndex)
{
	DEBUG_METHOD;

	Element *pElement = NULL;
	const ElementDescriptor *pElementDescriptor;
	unsigned int hash;

	pElement = getElementByTag(pTag);
	if (!pElement)
	{
		// Find the element descriptor
		pElementDescriptor = getElementDescriptor();
		hash = BranchElement::TagKey::HashKey(pTag);

		for (size_t i = 0; i < pElementDescriptor->m_nElementCount; i++)
		{
			/*
				Create if:
				Hash matches
				TagName matches
				Max elements is 0 or index < max
			*/
			if (hash == pElementDescriptor->m_pElements[i].m_nHash && std::wcscmp(pElementDescriptor->m_pElements[i].m_pTag, pTag) == 0 && 
				(pElementDescriptor->m_pElements[i].m_nMax == 0 || nIndex < pElementDescriptor->m_pElements[i].m_nMax))
			{
				// Create new element and register it
				Element *pElement = pElementDescriptor->m_pElements[i].m_pfCreateElement(&pElementDescriptor->m_pElements[i]);
				if (pElement)
				{
					m_childElements.insert(std::pair<TagKey, Element*>(TagKey(pTag, nIndex, pElementDescriptor), pElement));
					onElementCreated(pElement);
				}
				return pElement;
			}
		}
		// Bad, element wasn't found
		LOG(TEXT("BAD: Unknown Tag: "));
		LOG(pTag);
		return NULL;
	}
	return pElement;
}

void BranchElement::destroyElement(Element *pElement)
{
	DEBUG_METHOD;

	// Find element by pElement
	for (auto it = m_childElements.begin(); it != m_childElements.end(); it++)
	{
		if (it->second == pElement)
		{
			m_childElements.erase(it);
			Element::deleteElement(this, pElement);
			return;
		}
	}
}

BranchElement::TagKeyRange Separatista::BranchElement::getAllByTagName(const wchar_t * pTagName)
{
	DEBUG_METHOD;

	unsigned int nHash;
	TagKeyRange tagKeyRange;

	nHash = Element::TagKey::HashKey(pTagName);
	bool begin = true;
	// Initialize both iterators to the end
	tagKeyRange.m_begin = m_childElements.end();
	tagKeyRange.m_end = m_childElements.end();

	for (auto it = m_childElements.cbegin(); it != m_childElements.cend(); it++)
	{
		if (nHash == it->first.getHash() && std::wcscmp(pTagName, it->first.getTagName()) == 0)
		{
			if (begin)
			{
				tagKeyRange.m_begin = it;
				begin = false;
			}
			else
			{
				tagKeyRange.m_end = it;
				++tagKeyRange.m_end;
			}
		}
	}

	return tagKeyRange;
}


void BranchElement::fromDOMDocument(Separatista::DOMElement *pDOMElement, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	xercesc::DOMElement *pChildElement;
	const wchar_t *pPrevTag = NULL, *pCurrentTag;
	size_t index = 0;
	Element *pElement;

	// Iterate over all child elements
	for (pChildElement = pDOMElement->getFirstElementChild(); pChildElement != NULL; pChildElement = pChildElement->getNextElementSibling())
	{
		pCurrentTag = pChildElement->getTagName();
		if (pPrevTag && std::wcscmp(pPrevTag, pCurrentTag) == 0)
			index++;
		else
			index = 0;

		pElement = createElementByTag(pCurrentTag, index);
		if (pElement)
			pElement->fromDOMDocument(pChildElement, errorOptions);
		else
		{
			LOG(TEXT("BAD: Unsupported tag:"));
			LOG(pCurrentTag);
		}
		pPrevTag = pCurrentTag;
	}
}

DOMElement* BranchElement::toDOMDocument(Separatista::DOMDocument *pDOMDocument, Separatista::DOMElement *pDOMParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	xercesc::DOMElement *pChildElement = NULL;

	// Create my element
	try
	{
		pChildElement = pDOMDocument->createElement(getTag());
		if (pChildElement)
		{
			pDOMParent->appendChild(pChildElement);

			// Iterate over all child elements
			for (auto it = m_childElements.begin(); it != m_childElements.end(); it++)
			{
				it->second->toDOMDocument(pDOMDocument, pChildElement, errorOptions);
			}
		}
	}
	catch (const xercesc::DOMException &e)
	{
		if (pChildElement)
			delete pChildElement;
		switch (errorOptions)
		{
		case ThrowExceptions:
			throw ElementException(SEPARATISTA_EXCEPTION(e.getMessage()), this);
		default:
			SEPARATISTA_REPORT(e);
		}
		return NULL;
	}
	return pChildElement;
}