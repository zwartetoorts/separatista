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

#include <wx/datectrl.h>

#include <separatista/debug/debug.h>

#include "simpledataviewrenderer.h"
#include "simpledataviewmodel.h"

SimpleDataViewRenderer::SimpleDataViewRenderer()
	:wxDataViewCustomRenderer(wxT("void*"), wxDATAVIEW_CELL_EDITABLE)
{
	m_pSepaElement = NULL;
	m_pValueElement = NULL;
}

bool SimpleDataViewRenderer::GetValue(wxVariant& value) const
{
	value = m_pModelNode;
	return true;
}

const wxString SimpleDataViewRenderer::getTextValue() const
{
	wxString value;
	wxDateTime dateTime;
	const SimpleViewData::Element *pTypeElement; 

	if (!m_pValueElement || !m_pSepaElement)
		return wxEmptyString;

	// Read the text of the element or it's attribute value
	if (m_pAttribute)
	{
		value = m_pSepaElement->getAttributeValue(m_pAttribute->getValue());
	}
	else
	{
		value = m_pSepaElement->getTextValue();
	}

	pTypeElement = getValueTypeElement();

	if (pTypeElement)
	{
		if (pTypeElement->getValue() == wxT("DateTime"))
		{
			dateTime = getDateTimeValue();
			return dateTime.Format(wxLocale::GetInfo(wxLocaleInfo::wxLOCALE_DATE_TIME_FMT));
		}
		else if (pTypeElement->getValue() == wxT("Date"))
		{
			dateTime = getDateValue();
			return dateTime.FormatDate();
		}
		else if (pTypeElement->getValue() == wxT("Options"))
		{
			// Get all children with key type
			const SimpleViewData::Element *pChildElement, *pOptionValueElement;
			for (size_t i = 0; i < pTypeElement->getChildCount(); i++)
			{
				pChildElement = pTypeElement->getChild(i);

				if (pChildElement->getType() == SimpleViewData::Element::OptionKey &&
					(pOptionValueElement = pChildElement->getChildByType(SimpleViewData::Element::OptionValue)) != NULL)
				{
					if (pOptionValueElement->getValue() == value)
						return pChildElement->getValue();
				}
			}
		}
		else
		{
			return value;
		}
	}
}

const SimpleViewData::Element* SimpleDataViewRenderer::getValueTypeElement() const
{
	if (m_pValueElement)
	{
		const SimpleViewData::Element *pTypeElement = m_pValueElement->getChildByType(SimpleViewData::Element::Type);
		if (pTypeElement)
		{
			return pTypeElement;
		}
	}
	return NULL;
}

const wxDateTime SimpleDataViewRenderer::getDateValue() const
{
	if (!m_pSepaElement)
		return wxInvalidDateTime;

	return wxDateTime(m_pSepaElement->getDateValue());
}

const wxDateTime SimpleDataViewRenderer::getDateTimeValue() const
{
	if (!m_pSepaElement)
		return wxInvalidDateTime;

	return wxDateTime(m_pSepaElement->getDateValue());
}

bool SimpleDataViewRenderer::SetValue(const wxVariant& value)
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode *)value.GetVoidPtr();

	m_pModelNode = pNode;
	m_pSepaElement = pNode->getSepaElement();
	m_pValueElement = pNode->getSimpleViewDataElement();
	m_pAttribute = pNode->getSimpleViewDataAttributeElement();

	return true;
}

wxSize SimpleDataViewRenderer::GetSize() const
{
	if (!m_pSepaElement)
		return wxSize(0, 0);

	return GetTextExtent(getTextValue());
}

bool SimpleDataViewRenderer::Render(wxRect cell, wxDC* dc, int state)
{
	if (!m_pSepaElement)
		return false;

	RenderText(getTextValue(), 0, cell, dc, state);
	
	return true;
}

bool SimpleDataViewRenderer::HasEditorCtrl() const
{
	// Check for Readonly type
	if (!m_pSepaElement || !m_pValueElement)
		return false;

	const SimpleViewData::Element *pTypeElement = getValueTypeElement();
	if (pTypeElement)
	{
		if (pTypeElement->getValue() == wxT("Readonly"))
			return false;
		return true;
	}

	return false;
}

wxWindow * SimpleDataViewRenderer::CreateEditorCtrl(wxWindow * parent, wxRect labelRect, const wxVariant & value)
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)value.GetVoidPtr();

	if (!pNode)
		return NULL;

	Separatista::Element *pSepaElement = pNode->getSepaElement();
	const SimpleViewData::Element *pElement = pNode->getSimpleViewDataElement();
	const SimpleViewData::Element *pAttr = pNode->getSimpleViewDataAttributeElement();

	const SimpleViewData::Element *pTypeElement = pElement->getChildByType(SimpleViewData::Element::Type);
	if (pTypeElement)
	{
		if (pTypeElement->getValue() == wxT("Date"))
		{
			return new wxDatePickerCtrl(
				parent,
				wxID_ANY,
				wxDateTime(pSepaElement->getDateValue()),
				labelRect.GetTopLeft(),
				labelRect.GetSize(),
				wxDP_DROPDOWN);
		}
		else if (pTypeElement->getValue() == wxT("Text"))
		{
			return new wxTextCtrl(
				parent,
				wxID_ANY,
				pSepaElement->getTextValue(),
				labelRect.GetTopLeft(),
				labelRect.GetSize());
		}
	}

	return NULL;
}

bool SimpleDataViewRenderer::GetValueFromEditorCtrl(wxWindow * editor, wxVariant & value)
{
	return false;
}

