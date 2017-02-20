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

#include "leafelement.h"
#include "debug/debug.h"

using namespace Separatista;

LeafElement::LeafElement(const ChildElementDescriptor* pChildElementDescriptor) :
Element(pChildElementDescriptor)
{
	DEBUG_METHOD;
}

Element* LeafElement::createElement(const ChildElementDescriptor* pChildElementDescriptor)
{
	DEBUG_METHOD;

	return new LeafElement(pChildElementDescriptor);
}

xercesc::DOMElement* LeafElement::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions) const
{
	DEBUG_METHOD;

	xercesc::DOMElement *pElement = NULL;

	// Check for value
	if (isEmpty())
		return NULL;

	// Create element and set value
	try
	{
		pElement = pDocument->createElementNS(pParent->getNamespaceURI(), getTag());
		if (pElement)
		{
			pParent->appendChild(pElement);
			pElement->setTextContent(m_value.data());
		}
	}
	catch (const xercesc::DOMException &e)
	{
		if (pElement)
			delete pElement;
		switch (errorOptions)
		{
		case ThrowExceptions:
			SEPARATISTA_THROW_EXCEPTION(ElementException, e.getMessage(), this);
		default:
			SEPARATISTA_REPORT(e);
		}
		return NULL;
	}
	return pElement;
}

void LeafElement::fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	setValue(pDOMElement->getTextContent(), errorOptions);
}

const wchar_t* LeafElement::getTextValue() const
{
	DEBUG_METHOD;

	return m_value.data();
}

void LeafElement::setValue(const wchar_t *pValue, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	switch (errorOptions)
	{
	case Element::AcceptValue:
		m_value = pValue;
		onElementValueChanged(pValue);
		break;
	case Element::ClearValue:
		try
		{
			if (getElementDescriptor()->m_pTypeParent)
			{
				getElementDescriptor()->m_pTypeParent->m_pfnValidate(pValue, this);
			}

			if(getElementDescriptor()->m_pfnValidate)
				getElementDescriptor()->m_pfnValidate(pValue, this);
			m_value = pValue;
			onElementValueChanged(pValue);
		}
		catch (const InvalidValueException &)
		{
			m_value.clear();
			onElementValueChanged(pValue);
		}
		break;
	case Element::ThrowExceptions:
	default:
		if (getElementDescriptor()->m_pTypeParent)
		{
			getElementDescriptor()->m_pTypeParent->m_pfnValidate(pValue, this);
		}
		if (getElementDescriptor()->m_pfnValidate)
			getElementDescriptor()->m_pfnValidate(pValue, this);
		m_value = pValue;
		onElementValueChanged(pValue);
	}
}
