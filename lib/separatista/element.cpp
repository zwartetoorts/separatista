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

#include <xercesc/util/XMLDateTime.hpp>
#include <xercesc/framework/psvi/XSValue.hpp>

#include "separatista.h"
#include "element.h"

using namespace Separatista;

Element::Element(const wchar_t *pName)
{
	m_pTag = pName;
	m_pElementListener = NULL;
}

Element::~Element()
{
}

ElementListener* Element::setElementListener(ElementListener *pElementListener)
{
	ElementListener *pOld = m_pElementListener;
	m_pElementListener = pElementListener;
	return pOld;
}

xercesc::DOMElement* Element::createElement(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement;

	try
	{
		pElement = pDocument->createElementNS(pParent->getNamespaceURI(), m_pTag);
		if (pElement)
			pParent->appendChild(pElement);
	}
	catch (const xercesc::DOMException &e)
	{
		SetDebugMessage(e.getMessage());
		return NULL;
	}

	return pElement;
}

const wchar_t* Element::getTag() const
{
	return m_pTag;
}

void Element::onValueChanged(const wchar_t *pNewValue)
{
	if (m_pElementListener)
		m_pElementListener->elementValueChanged(this, pNewValue);
}

void Element::onDeleted()
{
	if (m_pElementListener)
		m_pElementListener->elementDeleted(this);
}

