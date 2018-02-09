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

#ifndef SEPARATISTA_GUI_DOCUMENTEDITOR_H
#define SEPARATISTA_GUI_DOCUMENTEDITOR_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filename.h>

#include <separatista/separatista.h>
#include <separatista/separatistadocument.h>

#include "simpleviewdata.h"

/**
	This class is responsible for all modifications to the SeparatistaDocument.
*/
class DocumentEditor
{
public:
	/// Empty c'tor, leaves DocumentEditor unintialized
	DocumentEditor();

	/**
		Creates a DocumentEditor with an empty document with the chosen namespace.
		@see Separatista::SeparatistaDocument(const wchar_t *pNamespace, bool bEnableAutomagic)
		@throws Separatista::UnsupportedNamespaceException
	*/
	DocumentEditor(const wxString &Namespace, bool bEnableAutomagic);

	/**
		Creates a DocumentEditor from a wxFileName object.
		@throws Separatista::UnsupportedNamespaceException
		@throws wxStringList Containing all errors as wxString
	*/
	DocumentEditor(const wxFileName &FileName, bool bEnableAutomagic);

	~DocumentEditor();

	/**
		Checks it the document has changed after editing.
	*/
	bool hasChanged() const;

	void changed();

	/**
		Returns the Simple View Data.
	*/
	const SimpleViewData* getSimpleViewData() const;

	/**
		Returns the Separatista Document
	*/
	Separatista::SeparatistaDocument* getDocument() const;

	/**
		Saves the separatista document.
	*/
	bool save();

	/**
		Saves the separatista document to path and changes the current document to path
	*/
	bool saveAs(const wxFileName &fileName);

	/**
		Returns the filename
	*/
	const wxFileName getFileName() const;

protected:
	/**
		Loads the Simple View Data file based on the document's namespace.
		Nothing bad will happen if it fails, it just means we don't have a Simple View.
		@throws wxString containing an error message. This is a bug in the program or a corrupted map file.
	*/
	void loadSimpleViewData();

private:
	Separatista::SeparatistaDocument *m_pDocument;
	bool m_bChanged;
	SimpleViewData *m_pSimpleViewData;
	wxFileName m_fileName;
};

#endif // !defined SEPARATISTA_GUI_DOCUMENTEDITOR_H
