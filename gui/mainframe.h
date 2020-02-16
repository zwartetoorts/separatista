/***************************************************************************
*   Copyright (C) 2017 by Okkel Klaver                                    *
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

#ifndef SEPARATISTA_GUI_MAINFRAME_H
#define SEPARATISTA_GUI_MAINFRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/dataview.h>
#include <wx/object.h>

#include "documenteditor.h"
#include "simpledataviewmodel.h"
#include "expertdataviewmodel.h"

enum
{
	ID_SIMPLEVIEW_CTRL = 1,
	ID_EXPERTVIEW_CTRL = 2,
	ID_DATECTRL = 3,
	ID_TIMECTRL = 4,

	// Expert Context Menu commands
	ID_COMMAND_EXPERT_REMOVE = 5,
	ID_COMMAND_EXPERT_CREATE = 6,  // Reserve room for child elements
	
	// New Document menu items
	// PAIN
	ID_COMMAND_NEW_PAIN_001_001_03 = 100,
	ID_COMMAND_NEW_PAIN_008_001_02 = 101,
	
	// CAMT
	ID_COMMAND_NEW_CAMT_053_001_02 = 200,

	// Simple Context Menu commands
	ID_COMMAND_SIMPLE_REMOVE = 1000,
	ID_COMMAND_SIMPLE_CREATE = 1001,
	ID_COMMAND_SIMPLE_CREATE_DEFAULTS = 1002,
	ID_COMMAND_SIMPLE_SET_DEFAULTVALUE = 1003,


};

class MainFrame : public wxFrame
{
public:
	MainFrame();

	~MainFrame();

	void updateTitle();

private:
	void OnNewPain_001_001_03(wxCommandEvent& event);
	void OnNewPain_008_001_02(wxCommandEvent& event);

	void OnNewCamt_053_001_02(wxCommandEvent& event);

	void OnNewDocument(const wxString& nameSpace);

	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	void OnExpertViewContextMenu(wxDataViewEvent &evt);
	void OnSimpleViewContextMenu(wxDataViewEvent &evt);

	wxDataViewCtrl *m_pSimpleViewCtrl;
	wxDataViewCtrl *m_pExpertViewCtrl;
	
	wxDECLARE_EVENT_TABLE();

	DocumentEditor *m_pDocumentEditor;
};

#endif // !defined SEPARATISTA_GUI_MAINFRAME_H
