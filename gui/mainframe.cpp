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

#include <wx/wxprec.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>

#include <separatista/separatistadocument.h>
#include <separatista/documentreader.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "app.h"
#include "mainframe.h"
#include "separatista/debug/debug.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Separatista editor"))
{
	// Create menus
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_OPEN, wxT("&Open File\tCtrl-O"),
		wxT("Open a SEPA document"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menuBar);

	// Create splitter window
	wxSplitterWindow *splitterWindow = new wxSplitterWindow(this);

	// Create TreeView
	wxTreeCtrl *pTreeCtrlSimple = new wxTreeCtrl(splitterWindow);
	wxTreeCtrl *pTreeCtrlAdvanced = new wxTreeCtrl(splitterWindow);
	splitterWindow->SplitVertically(pTreeCtrlSimple, pTreeCtrlAdvanced, -200);

	CreateStatusBar();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("Select a SEPA file to open"));
	if (wxID_OK == dlg.ShowModal())
	{
		Separatista::DocumentReader reader;
		if (reader.parseFile(dlg.GetPath()) == Separatista::IOErrorCode::Success)
		{
			Separatista::SeparatistaDocument *doc = reader.getDocument();
		}

	}



}