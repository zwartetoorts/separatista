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
#include "element.h"
#include "debug/debug.h"

using namespace Separatista;

Element::Element(const wchar_t *pName)
{
	DEBUG_METHOD
	m_pTag = pName;
	m_pElementListener = NULL;
}

Element::~Element()
{
	DEBUG_METHOD
}

ElementListener* Element::setElementListener(ElementListener *pElementListener)
{
	DEBUG_METHOD
	ElementListener *pOld = m_pElementListener;
	m_pElementListener = pElementListener;
	return pOld;
}

xercesc::DOMElement* Element::createElement(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement;

	try
	{
		pElement = pDocument->createElementNS(pParent->getNamespaceURI(), m_pTag);
		if (pElement)
			pParent->appendChild(pElement);
	}
	catch (const xercesc::DOMException &e)
	{
		LOG(e.getMessage());
		return NULL;
	}

	return pElement;
}

const wchar_t* Element::getTag() const
{
	DEBUG_METHOD
	return m_pTag;
}

void Element::onValueChanged(const wchar_t *pNewValue)
{
	DEBUG_METHOD
	if (m_pElementListener)
		m_pElementListener->elementValueChanged(this, pNewValue);
}

void Element::onDeleted()
{
	DEBUG_METHOD
	if (m_pElementListener)
		m_pElementListener->elementDeleted(this);
}
