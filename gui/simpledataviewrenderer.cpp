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

#include <wx/app.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

#include <separatista/debug/debug.h>
#include <separatista/validator.h>
#include <separatista/iban/iban.h>

#include "simpledataviewrenderer.h"
#include "simpledataviewmodel.h"
#include "ibantextctrl.h"
#include "mainframe.h"

SimpleDataViewRenderer::SimpleDataViewRenderer()
	:wxDataViewCustomRenderer(wxT("void*"), wxDATAVIEW_CELL_EDITABLE)
{
	m_pModelNode = NULL;
	m_pEditingNode = NULL;
}

bool SimpleDataViewRenderer::GetValue(wxVariant& value) const
{
	value = m_pModelNode;
	return true;
}

const wxString SimpleDataViewRenderer::getTextValue(SimpleDataViewModelNode *pNode) const
{
	wxString value;
	wxDateTime dateTime;
	const SimpleViewData::Element *pSimpleElement, *pTypeElement; 
	Separatista::Element *pSepaElement;

	if ((pSimpleElement = pNode->getSimpleViewDataElement()) == NULL)
		return wxEmptyString;

	if ((pSepaElement = pNode->getSepaElement()) == NULL)
		return getDefaultValue(pNode);
	
	// Read the text of the element or it's attribute value
	if (pNode->getSimpleViewDataAttributeElement())
	{
		value = pSepaElement->getAttributeValue(pNode->getSimpleViewDataAttributeElement()->getValue());
	}
	else
	{
		value = pSepaElement->getTextValue();
	}

	pTypeElement = getValueTypeElement(pNode);

	if (pTypeElement)
	{
		if (pTypeElement->getValue() == wxT("DateTime"))
		{
			dateTime = getDateTimeValue(pNode);
			return dateTime.Format(wxLocale::GetInfo(wxLocaleInfo::wxLOCALE_DATE_TIME_FMT));
		}
		else if (pTypeElement->getValue() == wxT("Date"))
		{
			dateTime = getDateValue(pNode);
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
		else if (pTypeElement->getValue() == wxT("IBAN"))
		{
			// Format iban
			wxString IBAN;

			size_t n = 0;
			for (auto it = value.begin(); it != value.end(); it++, n++)
			{
				if (n > 0 && n % 4 == 0)
					IBAN += wxT(' ');
				IBAN += *it;
					
			}
			return IBAN;
		}
		else
		{
			return value;
		}
	}
	return wxEmptyString;
}

const SimpleViewData::Element* SimpleDataViewRenderer::getValueTypeElement(SimpleDataViewModelNode *pNode) const
{
	if (pNode->getSimpleViewDataElement())
	{
		const SimpleViewData::Element *pTypeElement = pNode->getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::Type);
		if (pTypeElement)
		{
			return pTypeElement;
		}
	}
	return NULL;
}

const wxDateTime SimpleDataViewRenderer::getDateValue(SimpleDataViewModelNode *pNode) const
{
	if (!pNode->getSepaElement())
	{
		const wxString value = getDefaultValue(pNode);
		if (value == wxT("Now"))
		{
			return wxDateTime::Today();
		}
		else
		{
			wxDateTime dt;
			dt.ParseDate(value);
			return dt;
		}
	}

	return wxDateTime(pNode->getSepaElement()->getDateValue());
}

const wxDateTime SimpleDataViewRenderer::getDateTimeValue(SimpleDataViewModelNode *pNode) const
{
	if (!pNode->getSepaElement())
	{
		const wxString value = getDefaultValue(pNode);
		if (value == wxT("Now"))
		{
			return wxDateTime::Now();
		}
		else
		{
			wxDateTime dt;
			dt.ParseDateTime(value);
			return dt;
		}
	}

	return wxDateTime(pNode->getSepaElement()->getDateValue());
}

bool SimpleDataViewRenderer::SetValue(const wxVariant& value)
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode *)value.GetVoidPtr();

	m_pModelNode = pNode;
	
	return true;
}

wxSize SimpleDataViewRenderer::GetSize() const
{
	if (!m_pModelNode->getSepaElement())
		return GetTextExtent(wxT("Empty"));

	return GetTextExtent(getTextValue(m_pModelNode));
}

bool SimpleDataViewRenderer::Render(wxRect cell, wxDC* dc, int state)
{
	if (!m_pModelNode->getSepaElement())
	{
		dc->SetFont(dc->GetFont().Italic());
		RenderText(wxT("Empty"), 0, cell, dc, state);
	}
	else
	{
		dc->SetFont(dc->GetFont().GetBaseFont());
	}

	RenderText(getTextValue(m_pModelNode), 0, cell, dc, state);
	
	return true;
}

bool SimpleDataViewRenderer::HasEditorCtrl() const
{
	// Check for Readonly type
	if (!m_pModelNode->getSepaElement() || !m_pModelNode->getSimpleViewDataElement())
		return false;

	const SimpleViewData::Element *pTypeElement = getValueTypeElement(m_pModelNode);
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
	m_pEditingNode = (SimpleDataViewModelNode*)value.GetVoidPtr();

	if (!m_pEditingNode)
		return NULL;

	const SimpleViewData::Element *pTypeElement = getValueTypeElement(m_pEditingNode);
	if (pTypeElement)
	{
		if (pTypeElement->getValue() == wxT("Date"))
		{
			return new wxDatePickerCtrl(
				parent,
				wxID_ANY,
				wxDateTime(getDateValue(m_pEditingNode)),
				labelRect.GetTopLeft(),
				labelRect.GetSize(),
				wxDP_DROPDOWN);
		}
		else if (pTypeElement->getValue() == wxT("DateTime"))
		{
			wxPanel *pPanel;
			wxDateTime dateTime;
			wxBoxSizer *pSizer;

			dateTime = getDateTimeValue(m_pEditingNode);
			pSizer = new wxBoxSizer(wxHORIZONTAL);

			pPanel = new wxPanel(
				parent,
				wxID_ANY,
				labelRect.GetTopLeft(),
				labelRect.GetSize());
			
			pSizer->Add(
				new wxDatePickerCtrl(
					pPanel,
					ID_DATECTRL,
					dateTime,
					wxDefaultPosition,
					wxDefaultSize,
					wxDP_DROPDOWN),
				1,
				wxEXPAND,
				2);
			pSizer->Add(
				new wxTimePickerCtrl(
					pPanel,
					ID_TIMECTRL,
					dateTime,
					wxDefaultPosition,
					wxDefaultSize,
					wxTP_DEFAULT),
				1,
				wxEXPAND,
				2);

			pPanel->SetSizerAndFit(pSizer);
			return pPanel;
		}
		else if (pTypeElement->getValue() == wxT("Text"))
		{
			return new wxTextCtrl(
				parent,
				wxID_ANY,
				getTextValue(m_pEditingNode),
				labelRect.GetTopLeft(),
				labelRect.GetSize());
		}
		else if (pTypeElement->getValue() == wxT("Options"))
		{
			wxArrayString list;
			size_t selected = wxNOT_FOUND;;
			wxChoice *pChoice;

			wxString value = getTextValue(m_pEditingNode);

			const SimpleViewData::Element *pChildElement;
			for (size_t i = 0; i < pTypeElement->getChildCount(); i++)
			{
				pChildElement = pTypeElement->getChild(i);

				if (pChildElement->getType() == SimpleViewData::Element::OptionKey)
				{
					// Add the option key to the list
					list.Add(pChildElement->getValue());

					// Get selected value
					if (pChildElement->getValue() == value)
						selected = i;
				}
			}

			pChoice = new wxChoice(
				parent,
				wxID_ANY,
				labelRect.GetTopLeft(),
				labelRect.GetSize(),
				list);
			pChoice->SetSelection(selected);
			return pChoice;
		}
		else if (pTypeElement->getValue() == wxT("IBAN"))
		{
			return new IBANTextCtrl(
				parent,
				wxID_ANY,
				getTextValue(m_pEditingNode),
				labelRect.GetTopLeft(),
				labelRect.GetSize());
		}
		else if (pTypeElement->getValue() == wxT("BIC"))
		{
			wxTextCtrl *pTextCtrl = new wxTextCtrl(
				parent,
				wxID_ANY,
				getTextValue(m_pEditingNode),
				labelRect.GetTopLeft(),
				labelRect.GetSize());
			pTextCtrl->SetMaxLength(11);
			return pTextCtrl;
		}
	}

	return NULL;
}

bool SimpleDataViewRenderer::GetValueFromEditorCtrl(wxWindow * editor, wxVariant & value)
{
	if(!m_pEditingNode)
		return false;

	const SimpleViewData::Element *pTypeElement = getValueTypeElement(m_pEditingNode);
	if (pTypeElement)
	{
		try
		{
			if (pTypeElement->getValue() == wxT("DateTime"))
			{
				wxDatePickerCtrl *pDateCtrl = (wxDatePickerCtrl*)editor->FindWindow(ID_DATECTRL);
				wxTimePickerCtrl *pTimeCtrl = (wxTimePickerCtrl*)editor->FindWindow(ID_TIMECTRL);

				if (pDateCtrl && pTimeCtrl)
				{
					wxDateTime dateTime = pDateCtrl->GetValue();
					wxDateTime time = pTimeCtrl->GetValue();
					dateTime.SetHour(time.GetHour());
					dateTime.SetMinute(time.GetMinute());
					dateTime.SetSecond(time.GetSecond());

					m_pEditingNode->setElementValue(dateTime, true);

					m_pEditingNode = NULL;
					return true;
				}
			}
			else if (pTypeElement->getValue() == wxT("Date"))
			{
				wxDatePickerCtrl *pDatePicker = (wxDatePickerCtrl*)editor;

				wxDateTime dateTime = pDatePicker->GetValue();
				m_pEditingNode->setElementValue(dateTime, false);

				m_pEditingNode = NULL;
				return true;
			}
			else if (pTypeElement->getValue() == wxT("Text") || pTypeElement->getValue() == wxT("BIC"))
			{
				wxTextCtrl *pTextCtrl = (wxTextCtrl*)editor;

				m_pEditingNode->setElementValue(pTextCtrl->GetValue());
				m_pEditingNode = NULL;
				return true;
			}
			else if (pTypeElement->getValue() == wxT("Options"))
			{
				wxChoice *pChoice = (wxChoice*)editor;

				size_t index = pChoice->GetSelection();

				if (index != wxNOT_FOUND && index < pTypeElement->getChildCount())
				{
					const SimpleViewData::Element *pChildElement, *pOptionValueElement;
					
					pChildElement = pTypeElement->getChild(index);
					if (pChildElement &&
						(pOptionValueElement = pChildElement->getChildByType(SimpleViewData::Element::OptionValue)) != NULL)
					{
						m_pEditingNode->setElementValue(pOptionValueElement->getValue());
						m_pEditingNode = NULL;
						return true;
					}
				}
			}
			else if (pTypeElement->getValue() == wxT("IBAN"))
			{
				IBANTextCtrl *pTextCtrl = (IBANTextCtrl*)editor;

				// Check iban
				Separatista::IBAN iban;

				iban = (const wchar_t*)pTextCtrl->GetValue();
				if (!iban.Check())
					wxLogError(wxT("Invalid IBAN"));
				else
					m_pEditingNode->setElementValue(pTextCtrl->GetValue());
				m_pEditingNode = NULL;
			}
		}
		catch (const Separatista::InvalidValueException &ive)
		{
			wxLogError(ive.getMessage());
		}
	}
	m_pEditingNode = NULL;
	return false;
}

const wxString SimpleDataViewRenderer::getDefaultValue(SimpleDataViewModelNode * pNode) const
{
	const SimpleViewData::Element *pDefaultElement = pNode->getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::DefaultValue);
	if (pDefaultElement)
		return pDefaultElement->getValue();
	else
		return wxEmptyString;
}

