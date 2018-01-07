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

#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/filename.h>
#include <wx/list.h>

#include <separatista/separatistadocument.h>
#include <separatista/documentreader.h>
#include <separatista/camt/camt.053.001.02.h>
#include <separatista/pain/pain.001.001.03.h>
#include <separatista/pain/pain.008.001.02.h>

#include <separatista/debug/debug.h>

#include "documenteditor.h"

DocumentEditor::DocumentEditor()
{
	m_pDocument = NULL;
	m_bChanged = false;
	m_pSimpleViewData = NULL;
}

DocumentEditor::DocumentEditor(const wxString &Namespace, bool bEnableAutomagic)
{
	m_pDocument = new Separatista::SeparatistaDocument(Namespace.c_str(), bEnableAutomagic);
	m_bChanged = true;
	m_pSimpleViewData = NULL;
	loadSimpleViewData();
}

DocumentEditor::DocumentEditor(const wxFileName &FileName, bool bEnableAutomagic)
{
	Separatista::DocumentReader reader;

	m_pDocument = NULL;
	m_bChanged = false;
	m_pSimpleViewData = NULL;

	reader.loadSchema(Separatista::camt_053_001_02::Namespace);
	reader.loadSchema(Separatista::pain_001_001_03::Namespace);
	reader.loadSchema(Separatista::pain_008_001_02::Namespace);

	if (reader.parseFile(FileName.GetFullPath()) == Separatista::IOErrorCode::Success)
	{
		m_pDocument = reader.getDocument();
		if (m_pDocument)
			loadSimpleViewData();
	}
	else
	{
		// Create error report
		wxStringList errorList;
		for (size_t c = 0; c < reader.getErrorCount(); c++)
			errorList.Add(reader.getErrorMessage(c));
		throw(errorList);
	}
	m_bChanged = true;
}

DocumentEditor::~DocumentEditor()
{
	if (m_pDocument)
		delete m_pDocument;
	if (m_pSimpleViewData)
		delete m_pSimpleViewData;
}

void DocumentEditor::loadSimpleViewData()
{
	if (!m_pDocument)
		return;

	// Construct a filname from the document's namespace
	wxString name = m_pDocument->getNamespaceURI();
	name.Replace(wxT(":"), wxT("_"));

	wxFileName fname(
		wxT("."),	// Path
		name, // Filename
		wxT("txt") // Ext	
	);
	if (fname.FileExists() && fname.IsFileReadable())
	{
		if (m_pSimpleViewData)
			delete m_pSimpleViewData;
		try
		{
			m_pSimpleViewData = new SimpleViewData(fname);
		}
		catch (const wxString& msg)
		{
			delete m_pSimpleViewData;
			m_pSimpleViewData = NULL;
			throw msg;
		}
	}
}

bool DocumentEditor::hasChanged() const
{
	return m_bChanged;
}

const SimpleViewData* DocumentEditor::getSimpleViewData() const
{
	return m_pSimpleViewData;
}

Separatista::SeparatistaDocument* DocumentEditor::getDocument() const
{
	return m_pDocument;
}

