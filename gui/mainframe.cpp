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
#include <wx/scrolwin.h>

#include <separatista/pain/pain.001.001.03.h>
#include <separatista/pain/pain.008.001.02.h>
#include <separatista/camt/camt.053.001.02.h>

#include "app.h"
#include "mainframe.h"
#include "documenteditor.h"
#include "separatista/debug/debug.h"

#include "simpledataviewrenderer.h"
#include "expertdataviewrenderer.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_COMMAND_NEW_PAIN_001_001_03, OnNewPain_001_001_03)
	EVT_MENU(ID_COMMAND_NEW_PAIN_008_001_02, OnNewPain_008_001_02)
	EVT_MENU(ID_COMMAND_NEW_CAMT_053_001_02, OnNewCamt_053_001_02)
	EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
	EVT_MENU(wxID_SAVE, MainFrame::OnSave)
	EVT_MENU(wxID_SAVEAS, MainFrame::OnSaveAs)
	EVT_DATAVIEW_ITEM_CONTEXT_MENU(ID_EXPERTVIEW_CTRL, OnExpertViewContextMenu)
	EVT_DATAVIEW_ITEM_CONTEXT_MENU(ID_SIMPLEVIEW_CTRL, OnSimpleViewContextMenu)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Separatista editor"))
{
	Maximize();

	// Create menus
	wxMenu *menuFile = new wxMenu;
	
	wxMenu *menuNew = new wxMenu;
	
	wxMenu *menuPain = new wxMenu;
	menuPain->Append(ID_COMMAND_NEW_PAIN_001_001_03, Separatista::pain_001_001_03::Namespace);
	menuPain->Append(ID_COMMAND_NEW_PAIN_008_001_02, Separatista::pain_008_001_02::Namespace);

	wxMenu *menuCamt = new wxMenu;
	menuCamt->Append(ID_COMMAND_NEW_CAMT_053_001_02, Separatista::camt_053_001_02::Namespace);

	menuNew->AppendSubMenu(menuPain, wxT("Pain"));
	menuNew->AppendSubMenu(menuCamt, wxT("Camt"));

	menuFile->AppendSubMenu(menuNew, wxT("New"));

	menuFile->Append(wxID_OPEN, wxT("&Open File\tCtrl-O"),
		wxT("Open a SEPA document"));
	menuFile->Append(wxID_SAVE, wxT("&Save File\tCtrl-S"),
		wxT("Save the current document"));
	menuFile->Append(wxID_SAVEAS, wxT("Save File as"),
		wxT("Save the current document to a different location"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menuBar);

	// Create splitter window
	wxSplitterWindow *pSplitterWindow = new wxSplitterWindow(this);
	wxSize clientSize = GetClientSize();

	// Create views
	m_pSimpleViewCtrl = new wxDataViewCtrl(
		pSplitterWindow,
		ID_SIMPLEVIEW_CTRL,
		wxDefaultPosition,
		wxDefaultSize,
		wxDV_SINGLE | wxDV_ROW_LINES);

	wxDataViewTextRenderer *pTextRenderer = new wxDataViewTextRenderer(wxT("string"), wxDATAVIEW_CELL_INERT, wxALIGN_LEFT);
	wxDataViewCustomRenderer *pSimpleRenderer = new SimpleDataViewRenderer();
	
	wxDataViewColumn *pColumn0 =
		new wxDataViewColumn(wxT("Path"), pTextRenderer, 0, 200, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
	wxDataViewColumn *pColumn1 =
		new wxDataViewColumn(wxT("Value"), pSimpleRenderer, 1, 200, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
	m_pSimpleViewCtrl->AppendColumn(pColumn0);
	m_pSimpleViewCtrl->AppendColumn(pColumn1);

	m_pExpertViewCtrl = new wxDataViewCtrl(
		pSplitterWindow,
		ID_EXPERTVIEW_CTRL,
		wxDefaultPosition,
		wxDefaultSize,
		wxDV_SINGLE | wxDV_NO_HEADER | wxDV_ROW_LINES);

	ExpertDataViewRenderer *pExpertRenderer = new ExpertDataViewRenderer();
	wxDataViewColumn *pExpertColumn0 =
		new wxDataViewColumn(wxT("Document"), pExpertRenderer, 0, 200, wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);
	m_pExpertViewCtrl->AppendColumn(pExpertColumn0);

	pSplitterWindow->SetMinimumPaneSize(50);
	pSplitterWindow->SplitVertically(m_pSimpleViewCtrl, m_pExpertViewCtrl, clientSize.GetWidth() / 2);

	// And statusbar
	CreateStatusBar();
}

MainFrame::~MainFrame()
{
	if (m_pDocumentEditor)
		delete m_pDocumentEditor;
}

void MainFrame::updateTitle()
{
	wxString title = wxT("Separatista");
	if (m_pDocumentEditor)
	{
		title += wxT(" - ") + m_pDocumentEditor->getFileName().GetFullPath();
		if (m_pDocumentEditor->hasChanged())
			title += wxT(" *");
	}
	SetTitle(title);
}

void MainFrame::OnNewPain_001_001_03(wxCommandEvent & event)
{
	OnNewDocument(Separatista::pain_001_001_03::Namespace);
}

void MainFrame::OnNewPain_008_001_02(wxCommandEvent & event)
{
	OnNewDocument(Separatista::pain_008_001_02::Namespace);
}

void MainFrame::OnNewCamt_053_001_02(wxCommandEvent & event)
{
	OnNewDocument(Separatista::camt_053_001_02::Namespace);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnNewDocument(const wxString & nameSpace)
{
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

	// Remove former document
	if (m_pDocumentEditor)
	{
		delete m_pDocumentEditor;
		m_pDocumentEditor = NULL;
	}

	try
	{
		m_pDocumentEditor = new DocumentEditor(nameSpace, true);

		if (m_pDocumentEditor->getSimpleViewData())
		{
			m_pSimpleViewCtrl->Enable(true);
			m_pSimpleViewCtrl->AssociateModel(m_pDocumentEditor->getSimpleDataViewModel());
		}
		else
			m_pSimpleViewCtrl->Enable(false);
		m_pExpertViewCtrl->AssociateModel(m_pDocumentEditor->getExpertDataViewModel());
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
	updateTitle();
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

	// Remove former document
	if (m_pDocumentEditor)
	{
		delete m_pDocumentEditor;
		m_pDocumentEditor = NULL;
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

				// Assoc models
				if (m_pDocumentEditor->getSimpleViewData() != NULL)
				{
					m_pSimpleViewCtrl->Enable(true);
					m_pSimpleViewCtrl->AssociateModel(m_pDocumentEditor->getSimpleDataViewModel());
				}
				else
					m_pSimpleViewCtrl->Enable(false);
				m_pExpertViewCtrl->AssociateModel(m_pDocumentEditor->getExpertDataViewModel());

				updateTitle();
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

void MainFrame::OnSave(wxCommandEvent & event)
{
	if (!m_pDocumentEditor->save())
		OnSaveAs(event);
	updateTitle();
}

void MainFrame::OnSaveAs(wxCommandEvent & event)
{
	wxFileDialog dlg(
		this,
		wxT("Save SEPA document to"),
		m_pDocumentEditor->getFileName().GetPath(true),
		m_pDocumentEditor->getFileName().GetName(),
		wxFileSelectorDefaultWildcardStr,
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;

	wxFileName fileName = wxFileName(dlg.GetPath());
	if (!m_pDocumentEditor->saveAs(fileName))
	{
		wxLogError(wxT("Error saving document"));
	}
	updateTitle();
}

void MainFrame::OnExpertViewContextMenu(wxDataViewEvent &evt)
{
	ExpertDataViewModel *pModel = (ExpertDataViewModel*)m_pExpertViewCtrl->GetModel();
	if (pModel)
		pModel->OnContextMenu(m_pExpertViewCtrl, evt);
	updateTitle();
}

void MainFrame::OnSimpleViewContextMenu(wxDataViewEvent &evt)
{
	SimpleDataViewModel *pModel = (SimpleDataViewModel*)m_pSimpleViewCtrl->GetModel();
	if (pModel)
		pModel->OnContextMenu(m_pSimpleViewCtrl, evt);
	updateTitle();
}
