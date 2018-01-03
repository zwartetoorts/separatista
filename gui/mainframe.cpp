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

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/filename.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include "app.h"
#include "mainframe.h"
#include "documenteditor.h"
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

	// And statusbar
	CreateStatusBar();
}

MainFrame::~MainFrame()
{
	if (m_pDocumentEditor)
		delete m_pDocumentEditor;
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnOpen(wxCommandEvent& event)
{
	// Check for modifications
	if (m_pDocumentEditor && m_pDocumentEditor->hasChanged())
	{
		if (wxCANCEL == wxMessageBox(
			wxT("You have unsaved changes to the document. Do you want to loose current changes? "),
			wxT("Loose changes?"),
			wxOK | wxCANCEL | wxCENTER,
			this))
		{
			return;
		}
	}

	// Load new document
	wxFileDialog dlg(this, wxT("Select a SEPA file to open"));
	if (wxID_OK == dlg.ShowModal())
	{
		// Create filename and check it
		wxFileName fname(dlg.GetPath());
		if (fname.FileExists() && fname.IsFileReadable())
		{
			try
			{
				m_pDocumentEditor = new DocumentEditor(fname, true);
			}
			catch (const Separatista::UnsupportedNamespaceException &nse)
			{
				wxMessageBox(
					wxT("Unsupported document type"),
					wxT("Failed to load document"),
					wxOK | wxCENTER,
					this);
			}
			catch (const Separatista::ElementException &ee)
			{
				wxMessageBox(
					wxT("Error reading document"),
					wxT("Failed to load document"),
					wxOK | wxCENTER,
					this);
			}
			catch (const wxStringList &errorList)
			{
				for (auto it = errorList.begin(); it != errorList.end(); it++)
				{
					wxMessageBox(*it);
				}
			}
		}
		else
		{
			wxMessageBox(
				wxT("File not found or inaccessable"),
				wxT("Error reading file"),
				wxOK | wxCENTER,
				this);
		}
	}
}

