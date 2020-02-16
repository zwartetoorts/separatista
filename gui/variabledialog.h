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

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/propdlg.h>
#include <wx/propgrid/propgrid.h>
#include <wx/config.h>

#include "simpleviewdata.h"
#include "ibantextctrl.h"

class IBANPropertyEditor : public wxPGEditor
{
public:
	wxString GetName() const;

	wxPGWindowList CreateControls(wxPropertyGrid* propgrid, wxPGProperty* property, const wxPoint& pos, const wxSize& size) const;

	void UpdateControl(wxPGProperty* property, wxWindow* ctrl) const;

	bool OnEvent(wxPropertyGrid* propgrid, wxPGProperty* property, wxWindow* wnd_primary, wxEvent& event) const;

	bool GetValueFromControl(wxVariant& variant, wxPGProperty* property, wxWindow* ctrl) const;

	static void registerClass();

	static wxPGEditor* getIBANEditor();

	static const wchar_t* m_pClassname;

private:
	static wxPGEditor* m_pIBANEditor;
	
};

class IBANProperty : public wxStringProperty
{
public:
	IBANProperty(const wxString& label, const wxString& name, const wxString& defaultValue);

	const wxPGEditor* DoGetEditorClass() const;

	const wxPGEditor* GetEditorClass() const;

	wxString ValueToString(wxVariant& value, int argFlags = 0) const;

	bool StringToValue(wxVariant& value, const wxString& text, int argFlags = 0) const;
};

class VariableDialog : public wxPropertySheetDialog
{
public:
	VariableDialog(SimpleViewData *pSimpleViewData, const wxString& nsspace);

	void OnOk(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

private:
	void loadVariables(SimpleViewData* pSimpleViewData, wxPropertyGrid* pPropertyGrid);
	void loadVariables(const SimpleViewData::Element* pElement, const wxString &type, wxPropertyGrid* pPropertyGrid, wxConfig& config);

	wxString m_namespace;
	wxPropertyGrid* m_pPropertyGrid;

};
