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

BranchElement::BranchElement(const ChildElementDescriptor *pChildElementDescriptor) :
Element(pChildElementDescriptor)
{
	DEBUG_METHOD;
}

BranchElement::~BranchElement()
{
	DEBUG_METHOD;

	for (auto it = m_childElements.begin(); it != m_childElements.end(); it++)
	{
		Element *pElement = it->second;
		//m_childElements.erase(it++);
		Element::deleteElement(pElement);
	}
}

Element* BranchElement::createElement(const ChildElementDescriptor *pChildElementDescriptor)
{
	DEBUG_STATIC_METHOD;

	return new BranchElement(pChildElementDescriptor);
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

	pElement = getElementByTag(pTag, nIndex);
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
			if (hash == pElementDescriptor->m_pChildren[i].m_nHash && std::wcscmp(pElementDescriptor->m_pChildren[i].m_pTag, pTag) == 0 && 
				(pElementDescriptor->m_pChildren[i].m_nMax == 0 || nIndex < pElementDescriptor->m_pChildren[i].m_nMax))
			{
				// Create new element and register it
				Element *pElement = pElementDescriptor->m_pChildren[i].m_pElementDescriptor->m_pfCreateElement(&pElementDescriptor->m_pChildren[i]);
				if (pElement)
				{
					// Important: create TagKey with ElementDescriptor::m_pTag, not with pTag wich can be deleted at some time
					m_childElements.insert(std::pair<TagKey, Element*>(TagKey(pElementDescriptor->m_pChildren[i].m_pTag, nIndex, pElementDescriptor), pElement));
					onElementCreated(pElement);
				}
				return pElement;
			}
		}
		// Bad, element wasn't found
		SEPARATISTA_THROW_EXCEPTION(UnsupportedTagException, TEXT("Unsupported tag"), this, pTag);
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
			Element::deleteElement(pElement);
			return;
		}
	}
}

BranchElement::TagKeyRange BranchElement::getAllByTagName(const wchar_t * pTagName)
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
			tagKeyRange.m_end = it;
			++tagKeyRange.m_end;
		}
	}

	return tagKeyRange;
}


void BranchElement::fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	xercesc::DOMElement *pChildElement;
	const wchar_t *pPrevTag = NULL, *pCurrentTag;
	size_t index = 0;
	Element *pElement;

	// Check current tag
	if (std::wcscmp(pDOMElement->getTagName(), getTag()) != 0)
		return;

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

IOErrorCode BranchElement::toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pDOMParent, const ErrorOptions errorOptions) const
{
	DEBUG_METHOD;

	xercesc::DOMElement *pChildElement = NULL;
	IOErrorCode ret = Success;

	// Create my element
	try
	{
		pChildElement = pDOMDocument->createElementNS(pDOMParent->getNamespaceURI(), getTag());
		if (pChildElement)
		{
			pDOMParent->appendChild(pChildElement);

			// Iterate over all child elements
			for (auto it = m_childElements.begin(); it != m_childElements.end(); it++)
			{
				ret = it->second->toDOMDocument(pDOMDocument, pChildElement, errorOptions);
				if (ret != Success)
					return ret;
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
			SEPARATISTA_THROW_EXCEPTION(ElementException, e.getMessage(), this);
		default:
			ret = Xerces;
			SEPARATISTA_REPORT(e);
		}
	}
	return ret;
}