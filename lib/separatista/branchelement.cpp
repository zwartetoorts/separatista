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

Element* BranchElement::createElement(const ElementDescriptor *pElementDescriptor)
{
	DEBUG_METHOD;

	return new BranchElement(pElementDescriptor);
}

Element* BranchElement::getElementByTag(const wchar_t *pTag) const
{
	auto element = m_childElements.find(TagKey(pTag, getElementDescriptor()));
	if (element == m_childElements.end())
		return NULL;
	
	return (*element).second;
}

Element* BranchElement::createElementByTag(const wchar_t *pTag)
{
	DEBUG_METHOD;

	Element *pElement = NULL;
	const ElementDescriptor *pElementDescriptor;

	pElement = getElementByTag(pTag);
	if (!pElement)
	{
		// Find the element descriptor
		pElementDescriptor = getElementDescriptor();
		for (size_t i = 0; i < pElementDescriptor->m_nElementCount; i++)
		{
			if (std::wcscmp(pElementDescriptor->m_pElements[i].m_pTag, pTag) == 0)
			{
				return pElementDescriptor->m_pElements[i].m_pfCreateElement(&pElementDescriptor->m_pElements[i]);
			}
		}
		// Bad, element wasn't found
	}
	return pElement;
}

void BranchElement::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

}

BranchElement::TagKey::TagKey(const wchar_t *pTagName, const ElementDescriptor *pBranchElementDescriptor)
{
	DEBUG_METHOD;

	m_pTagName = pTagName;
	m_pBranchElementDescriptor = pBranchElementDescriptor;
}

bool Separatista::BranchElement::TagKey::operator<(const TagKey & Other) const
{
	DEBUG_METHOD;

	// The first tag found is the lesser value
	for (size_t i = 0; i < m_pBranchElementDescriptor->m_nElementCount; i++)
	{
		if (std::wcscmp(m_pBranchElementDescriptor->m_pElements[i].m_pTag, m_pTagName) == 0)
			return true;
		else if (std::wcscmp(m_pBranchElementDescriptor->m_pElements[i].m_pTag, Other.m_pTagName) == 0)
			return false;
	}

	return false;
}

bool Separatista::BranchElement::TagKey::operator==(const TagKey & Other) const
{
	DEBUG_METHOD;

	return std::wcscmp(m_pTagName, Other.m_pTagName) == 0 ? true : false;
}

