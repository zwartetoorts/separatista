/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

#include "separatista/separatista.h"
#include "attributedleafelement.h"
#include "debug/debug.h"

using namespace Separatista;

AttributedLeafElement::AttributedLeafElement(const ChildElementDescriptor *pChildElementDescriptor)
	:LeafElement(pChildElementDescriptor)
{
	DEBUG_METHOD;
}

Element* AttributedLeafElement::createElement(const ChildElementDescriptor *pChildElementDescriptor)
{
	DEBUG_METHOD;

	return new AttributedLeafElement(pChildElementDescriptor);
}

IOErrorCode AttributedLeafElement::toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pDOMParent, const ErrorOptions errorOptions) const
{
	DEBUG_METHOD;
	IOErrorCode ret = Success;
	xercesc::DOMElement *pElement;

	ret = LeafElement::toDOMDocument(pDOMDocument, pDOMParent, errorOptions);
	pElement = pDOMParent->getLastElementChild();
	if (pElement)
	{
		try
		{
			for (auto it = m_Attributes.begin(); it != m_Attributes.end(); it++)
				pElement->setAttribute(it->first.c_str(), it->second.c_str());
		}
		catch (const xercesc::DOMException &e)
		{
			switch (errorOptions)
			{
			case ThrowExceptions:
				SEPARATISTA_THROW_EXCEPTION(ElementException, e.getMessage(), this);
			default:
				ret = Xerces;
				SEPARATISTA_REPORT(e);
			}
		}
	}
	return ret;
}

void AttributedLeafElement::fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	xercesc::DOMNamedNodeMap *pNodeMap;

	LeafElement::fromDOMDocument(pDOMElement, errorOptions);

	pNodeMap = pDOMElement->getAttributes();
	if (pNodeMap)
	{
		for (XMLSize_t c = 0; c < pNodeMap->getLength(); c++)
		{
			xercesc::DOMNode *pDOMNode = pNodeMap->item(c);
			if (pDOMNode)
			{
				m_Attributes.insert(
					std::make_pair<std::wstring, std::wstring>(pDOMNode->getNodeName(), pDOMNode->getNodeValue()));
			}
			else
				LOG(TEXT("BAD! DOMNodeMap returns NULL while index should be valid!"));
		}
	}
}

const wchar_t* AttributedLeafElement::getAttributeValue(const wchar_t *pAttributeName) const
{
	DEBUG_METHOD;

	auto it = m_Attributes.find(std::wstring(pAttributeName));
	if (it != m_Attributes.end())
		return it->second.c_str();
	return NULL;
}

void AttributedLeafElement::setAttributeValue(const wchar_t *pAttributeName, const wchar_t *pValue)
{
	DEBUG_METHOD;

	m_Attributes[pAttributeName] = pValue;
}
