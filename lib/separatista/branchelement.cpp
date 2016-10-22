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
		delete (*it).second;
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
				Max elements if 0 or index < max
			*/
			if (hash == pElementDescriptor->m_pElements[i].m_nHash && std::wcscmp(pElementDescriptor->m_pElements[i].m_pTag, pTag) == 0 && 
				(pElementDescriptor->m_pElements[i].m_nMax == 0 || nIndex < pElementDescriptor->m_pElements[i].m_nMax))
			{
				// Create new element and register it
				Element *pElement = pElementDescriptor->m_pElements[i].m_pfCreateElement(&pElementDescriptor->m_pElements[i]);
				if (pElement)
					m_childElements.insert(std::pair<TagKey, Element*>(TagKey(pTag, nIndex, pElementDescriptor), pElement));
				return pElement;
			}
		}
		// Bad, element wasn't found
		return NULL;
	}
	return pElement;
}

void BranchElement::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

}

BranchElement::TagKey::TagKey(const wchar_t *pTagName, size_t nIndex, const ElementDescriptor *pBranchElementDescriptor)
{
	DEBUG_METHOD;

	m_nIndex = nIndex;
	m_pTagName = pTagName;
	m_nHash = HashKey(pTagName);
	m_pBranchElementDescriptor = pBranchElementDescriptor;
}

bool Separatista::BranchElement::TagKey::operator<(const TagKey & Other) const
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

bool Separatista::BranchElement::TagKey::operator==(const TagKey & Other) const
{
	DEBUG_METHOD;

	return (m_nHash == Other.m_nHash && std::wcscmp(m_pTagName, Other.m_pTagName) == 0) ? m_nIndex == Other.m_nIndex : false;
}

unsigned int Separatista::BranchElement::TagKey::HashKey(const wchar_t *pTagName)
{
	DEBUG_METHOD;

	unsigned int hash = 0;

	size_t len = std::wcslen(pTagName);
	for (size_t n = 0; n < len; n++)
		hash += pTagName[n] << n;
	return hash;
}