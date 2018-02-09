/***************************************************************************
*   Copyright (C) 2018 by Okkel Klaver                                    *
*   info@vanhetland.nl                                                    *
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

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filename.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include <separatista/debug/debug.h>

#include "simpleviewdata.h"

SimpleViewData::SimpleViewData(const wxFileName &FileName)
	:m_RootElement(Element::Root)
{
	if (FileName.FileExists() && FileName.IsFileReadable())
	{
		wxFileInputStream fis(FileName.GetFullPath());
		if (fis.IsOk())
		{
			wxTextInputStream tis(fis);
			while (fis.CanRead())
			{
				parseLine(tis.ReadLine(), &m_RootElement, new Element(Element::SimplePath));
			}
		}
	}
}

const SimpleViewData::Element* SimpleViewData::getRootElement() const
{
	return &m_RootElement;
}

const wxChar * SimpleViewData::parseLine(const wxChar *pLine, Element *pParent, Element *pElement)
{
	// Parse complete line
	wxString value;

	// Check line len for empty line or comment
	if (::wxStrlen(*pLine) == 0 || *pLine==wxT('#'))
		return NULL;

	while(true)
	{
		// Check for type of Element we're handling
		switch (pElement->getType())
		{
		case Element::SimplePath:
		//case Element::SimplePathAttribute:
			// SimplePath ends with / or [
			switch (*pLine)
			{
			case wxT('/'):
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::SimplePath));
				break;
			case wxT('['):
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::Type));
				break;
			case wxT(':'):
				pLine = parseLine(++pLine, pElement, new Element(Element::DocumentPath));
				break;
			/*case wxT('@'):
				// Attribute
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::SimplePathAttribute));
				break;*/
			case wxT('\0'):
				throw wxString(wxT("Unexpected end of line"));
			default:
				value += *pLine;
			}
			break;
		case Element::Type:
			// Type ends with ] , options are :
			switch (*pLine)
			{
			case wxT(']'):
				// End of options
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				return pLine;
			case wxT(':'):
				// Begin type options
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::OptionKey));
				// Also end of options
				return pLine;
			case wxT('\0'):
				throw wxString(wxT("Unexpected end of line"));
			default:
				value += *pLine;
			}
			break;
		case Element::OptionKey:
			// OptionsKey ends with = 
			if (*pLine == wxT('='))
			{
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::OptionValue));
				if (*pLine == wxT(','))
					pElement = new Element(Element::OptionKey);
				else if (*pLine == wxT(']'))
					return pLine;
			}
			else if (*pLine == wxT('\0'))
			{
				throw wxString(wxT("Unexpected end of line"));
			}
			else
				value += *pLine;
			break;
		case Element::OptionValue:
			// Optionvalue ends with , or ]
			switch (*pLine)
			{
			case wxT(','):
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				return pLine;
			case wxT(']'):
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				return pLine;
			case wxT('\0'):
				throw wxString(wxT("Unexpected end of line"));
			default:
				value += *pLine;
			}
			break;
		case Element::DocumentPath:
		case Element::DocumentPathAttribute:
			// DocumentPath ends at the end of the string or with =
			switch (*pLine)
			{
			case wxT('/'):
				// Next path element
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::DocumentPath));
				break;
			case wxT('\0'):
				// End of line
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				return NULL;
			case wxT('='):
				// Default value
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::DefaultValue));
				break;
			case wxT('@'):
				// Attribute
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				pLine = parseLine(++pLine, pElement, new Element(Element::DocumentPathAttribute));
				break;
			default:
				value += *pLine;
			}
			break;
		case Element::DefaultValue:
			// DefaultValue ends at the end of the string
			if (*pLine == wxT('\0'))
			{
				pElement->setValue(value);
				value.clear();
				pElement = pParent->addChild(pElement);
				return NULL;
			}
			else
				value += *pLine;
			break;
		default:
			throw wxString(wxT("Unknown element type"));
		}
		if (pLine)
			pLine++;
		else 
			break;
	}
	return pLine;
}

SimpleViewData::Element::Element(ElementType type)
{
	m_type = type;
}

SimpleViewData::Element::~Element()
{
	for (auto it = m_elements.begin(); it != m_elements.end(); it++)
		delete *it;
}

SimpleViewData::Element::ElementType SimpleViewData::Element::getType() const
{
	return m_type;
}

const wxString& SimpleViewData::Element::getValue() const
{
	return m_value;
}

void SimpleViewData::Element::setValue(const wxString &value)
{
	m_value = value;
}

SimpleViewData::Element* SimpleViewData::Element::addChild(Element *pElement)
{
	// Check if the element is already present
	for (auto it = m_elements.begin(); it != m_elements.end(); it++)
	{
		if ((*it)->m_value == pElement->getValue())
		{
			// If it's already present, delete the new Element and return the found element
			delete pElement;
			return *it;
		}
	}
	m_elements.push_back(pElement);
	return pElement;
}

const SimpleViewData::Element* SimpleViewData::Element::getChild(size_t index) const
{
	try
	{
		return m_elements[index];
	}
	catch (const std::out_of_range &)
	{
		return NULL;
	}
}

size_t SimpleViewData::Element::getChildCount() const
{
	return m_elements.size();
}

const SimpleViewData::Element* SimpleViewData::Element::getChildByType(SimpleViewData::Element::ElementType t) const
{
	for (auto it = m_elements.begin(); it != m_elements.end(); it++)
	{
		if ((*it)->getType() == t)
			return *it;
	}
	return NULL;
}

int SimpleViewData::Element::compare(const SimpleViewData::Element * pChild1, const SimpleViewData::Element * pChild2) const
{
	// Iterate over children and return first found
	for (auto it = m_elements.begin(); it != m_elements.end(); it++)
	{
		if (*it == pChild1)
			return -1;
		else if (*it == pChild2)
			return 1;
	}
	return 0;
}
