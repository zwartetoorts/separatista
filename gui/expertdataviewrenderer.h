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

#ifndef SEPARATISTA_GUI_EXPERTDATAVIEWRENDERER_H
#define SEPARATISTA_GUI_EXPERTDATAVIEWRENDERER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>

#include <separatista/separatista.h>
#include <separatista/separatistadocument.h>

#include "simpleviewdata.h"

// Forward decl
class ElementDataViewModelNode;

class ExpertDataViewRenderer : public wxDataViewCustomRenderer
{
public:
	ExpertDataViewRenderer();

	bool GetValue(wxVariant& value) const;
	bool SetValue(const wxVariant& value);
	wxSize GetSize() const;
	bool Render(wxRect cell, wxDC* dc, int state);
	bool HasEditorCtrl() const;
	wxWindow* CreateEditorCtrl(wxWindow *parent, wxRect labelRect, const wxVariant &value);
	bool GetValueFromEditorCtrl(wxWindow *editor, wxVariant &value);
protected:
	
private:
	ElementDataViewModelNode *m_pModelNode;
	ElementDataViewModelNode *m_pEditingNode;

};

#endif // !defined SEPARATISTA_GUI_EXPERTDATAVIEWRENDERER_H
