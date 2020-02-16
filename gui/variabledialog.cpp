/***************************************************************************
*   Copyright (C) 2020 by Okkel Klaver                                    *
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

#include "variabledialog.h"
#include <wx/config.h>
#include <wx/bookctrl.h>
#include <wx/propgrid/editors.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

wxBEGIN_EVENT_TABLE(VariableDialog, wxPropertySheetDialog)
EVT_BUTTON(wxID_OK, VariableDialog::OnOk)
wxEND_EVENT_TABLE()

wxPGEditor* IBANPropertyEditor::m_pIBANEditor = NULL;
const wchar_t* IBANPropertyEditor::m_pClassname = wxT("IBANEditor");

wxString IBANPropertyEditor::GetName() const
{
	return m_pClassname;
}

wxPGWindowList IBANPropertyEditor::CreateControls(wxPropertyGrid* propgrid, wxPGProperty* property, const wxPoint& pos, const wxSize& size) const
{
	return wxPGWindowList(new IBANTextCtrl(propgrid, wxID_ANY, property->GetValue(), pos, size));
}

void IBANPropertyEditor::UpdateControl(wxPGProperty* property, wxWindow* ctrl) const
{
	((IBANTextCtrl*)ctrl)->SetValue(property->GetValue());
}

bool IBANPropertyEditor::OnEvent(wxPropertyGrid* propgrid, wxPGProperty* property, wxWindow* wnd_primary, wxEvent& event) const
{
	if (event.GetEventType() == wxEVT_TEXT_ENTER)
	{
		if (propgrid->IsEditorsValueModified())
			return true;
	}
	else if (event.GetEventType() == wxEVT_TEXT)
	{
		propgrid->EditorsValueWasModified();
	}

	return false;
}

bool IBANPropertyEditor::GetValueFromControl(wxVariant& variant, wxPGProperty* property, wxWindow* ctrl) const
{
	return property->StringToValue(variant, ((IBANTextCtrl*)ctrl)->GetValue());
}

void IBANPropertyEditor::registerClass()
{
	m_pIBANEditor = wxPropertyGrid::RegisterEditorClass(new IBANPropertyEditor);
}

wxPGEditor* IBANPropertyEditor::getIBANEditor()
{
	return m_pIBANEditor;
}


IBANProperty::IBANProperty(const wxString& label, const wxString& name, const wxString& defaultValue)
	:wxStringProperty(label, name, defaultValue)
{
	SetEditor(IBANPropertyEditor::getIBANEditor());
}

const wxPGEditor* IBANProperty::DoGetEditorClass() const
{
	return IBANPropertyEditor::getIBANEditor();
}

const wxPGEditor* IBANProperty::GetEditorClass() const
{
	return IBANPropertyEditor::getIBANEditor();
}

wxString IBANProperty::ValueToString(wxVariant& value, int argFlags) const
{
	wxString iban;
	wxString text = value.GetString();

	size_t i = 0;
	for (auto it = text.cbegin(); it != text.cend(); it++)
	{
		if (*it != wxT(' '))
		{
			if (i > 0 && i % 4 == 0)
			{
				iban += wxT(' ');
			}

			iban += *it;
			++i;
		}
	}
	return iban;
}

bool IBANProperty::StringToValue(wxVariant& value, const wxString& text, int argFlags) const
{
	wxString iban;

	for (auto it = text.cbegin(); it != text.cend(); it++)
	{
		if (*it != wxT(' '))
			iban += *it;
	}
	value = iban;
	return true;
}

VariableDialog::VariableDialog(SimpleViewData* pSimpleViewData, const wxString& nsspace)
	:m_namespace(nsspace)
{
	if (!wxPropertySheetDialog::Create(wxTheApp->GetTopWindow(), wxID_ANY, wxT("Variable editor")))
		return;

	CreateButtons(wxOK | wxCANCEL);

	wxBookCtrlBase* pNoteBook = GetBookCtrl();
	wxPanel* pPanel = new wxPanel(pNoteBook, wxID_ANY);
	GetBookCtrl()->AddPage(pPanel, m_namespace, true);

	m_pPropertyGrid = new wxPropertyGrid(pPanel, wxID_ANY, wxDefaultPosition, wxSize(600, 400), wxPG_AUTO_SORT | wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE);
	loadVariables(pSimpleViewData, m_pPropertyGrid);

	LayoutDialog();
}

void VariableDialog::loadVariables(SimpleViewData* pSimpleViewData, wxPropertyGrid* pPropertyGrid)
{
	wxConfig config("SeparatistaGUI");
	config.SetPath(m_namespace);

	loadVariables(pSimpleViewData->getRootElement(), wxEmptyString, pPropertyGrid, config);
}

void VariableDialog::loadVariables(const SimpleViewData::Element* pElement, const wxString &type, wxPropertyGrid* pPropertyGrid, wxConfig& config)
{
	// Enum over all children
	wxString t(type);

	for (size_t i = 0; i < pElement->getChildCount(); i++)
	{
		const SimpleViewData::Element* pChildElement = pElement->getChild(i);
		if (pChildElement->getType() == SimpleViewData::Element::DefaultValue)
		{
			// Check & Strip % signs
			wxString name = pChildElement->getValue();
			if (name[0] == wxT('%') && name[name.Len() - 1] == wxT('%'))
			{
				name = name.Mid(1, name.Len() - 2);
				
				// Lookup wxConfig value
				wxString value = config.Read(name);
				if (type == wxT("Date"))
				{
					wxDateTime dtime;
					dtime.ParseDateTime(value);
					pPropertyGrid->Append(new wxDateProperty(name, wxPG_LABEL, dtime));
				}
				else if (type == wxT("IBAN"))
				{
					pPropertyGrid->Append(new IBANProperty(name, wxPG_LABEL, value));
				}
				else
				{
					pPropertyGrid->Append(new wxStringProperty(name, wxPG_LABEL, value));
				}
			}
		}
		else if (pChildElement->getType() == SimpleViewData::Element::Type)
		{
			t = pChildElement->getValue();
		}
		else
		{
			loadVariables(pChildElement, t, pPropertyGrid, config);
		}
	}
}

void VariableDialog::OnOk(wxCommandEvent& evt)
{
	wxPropertyGridIterator it;
	wxConfig config("SeparatistaGUI");
	config.SetPath(m_namespace);

	for (it = m_pPropertyGrid->GetIterator(); !it.AtEnd(); it++)
	{
		config.Write((*it)->GetName(), (*it)->GetValue().GetString());
	}
	EndModal(wxOK);
}

