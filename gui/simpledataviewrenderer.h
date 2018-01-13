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

#ifndef SEPARATISTA_GUI_SIMPLEDATAVIEWRENDERER_H
#define SEPARATISTA_GUI_SIMPLEDATAVIEWRENDERER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>

#include <separatista/separatista.h>
#include <separatista/separatistadocument.h>

#include "simpleviewdata.h"

// Forward decl
class SimpleDataViewModelNode;

class SimpleDataViewRenderer : public wxDataViewCustomRenderer
{
public:
	SimpleDataViewRenderer();

	bool GetValue(wxVariant& value) const;
	bool SetValue(const wxVariant& value);
	wxSize GetSize() const;
	bool Render(wxRect cell, wxDC* dc, int state);
	bool HasEditorCtrl() const;
	wxWindow* CreateEditorCtrl(wxWindow *parent, wxRect labelRect, const wxVariant &value);
	bool GetValueFromEditorCtrl(wxWindow *editor, wxVariant &value);
protected:
	/// Returns the value of the element or the value of the element attribute
	const wxString getTextValue() const;

	const wxDateTime getDateValue() const;

	const wxDateTime getDateTimeValue() const;

	/// Returns the type of the element
	const SimpleViewData::Element* getValueTypeElement() const;

private:
	SimpleDataViewModelNode *m_pModelNode;
	Separatista::Element *m_pSepaElement;
	const SimpleViewData::Element *m_pValueElement;
	const SimpleViewData::Element *m_pAttribute;
};

#endif // !defined SEPARATISTA_GUI_SIMPLEDATAVIEWRENDERER_H
