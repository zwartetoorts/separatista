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
	ID_EXPERTVIEW_CTRL,
	ID_DATECTRL,
	ID_TIMECTRL,
	ID_COMMAND_EXPERT_REMOVE,
	ID_COMMAND_EXPERT_CREATE,  // Reserve room for child elements
};

enum
{
	IDM_
};

class MainFrame : public wxFrame
{
public:
	MainFrame();

	~MainFrame();

private:
	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	void OnExpertViewContextMenu(wxDataViewEvent &evt);
	void OnSimpleViewContextMenu(wxDataViewEvent &evt);

	wxDataViewCtrl *m_pSimpleViewCtrl;
	wxDataViewCtrl *m_pExpertViewCtrl;
	wxObjectDataPtr<SimpleDataViewModel> m_simpleDataViewModel;
	wxObjectDataPtr<ExpertDataViewModel> m_expertDataViewModel;

	wxDECLARE_EVENT_TABLE();

	DocumentEditor *m_pDocumentEditor;
};

#endif // !defined SEPARATISTA_GUI_MAINFRAME_H
