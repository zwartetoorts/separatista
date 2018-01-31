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

#include <wx/app.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

#include <separatista/debug/debug.h>
#include <separatista/validator.h>
#include <separatista/iban/iban.h>

#include "expertdataviewrenderer.h"
#include "expertdataviewmodel.h"
#include "ibantextctrl.h"

ExpertDataViewRenderer::ExpertDataViewRenderer()
	:wxDataViewCustomRenderer(wxT("void*"), wxDATAVIEW_CELL_EDITABLE, wxALIGN_LEFT)
{

}

bool ExpertDataViewRenderer::GetValue(wxVariant &value) const
{
	value = m_pModelNode;
	return true;
}

bool ExpertDataViewRenderer::SetValue(const wxVariant &value)
{
	m_pModelNode = (ElementDataViewModelNode*)value.GetVoidPtr();
	return true;
}

wxSize ExpertDataViewRenderer::GetSize() const
{
	wxString label = m_pModelNode->getLabel();
	if (label.Length() == 0)
	{
		// Format empty string
		label = wxT("(Empty)");
	}
	return GetTextExtent(label);
}

bool ExpertDataViewRenderer::Render(wxRect cell, wxDC * dc, int state)
{
	wxString label = m_pModelNode->getLabel();
	if (label.Length() == 0)
	{
		// Format empty string
		label = wxT("(Empty)");
		dc->SetFont(dc->GetFont().Italic());
	}
	else
	{
		dc->SetFont(dc->GetFont().GetBaseFont());
	}
	RenderText(label, 0, cell, dc, state);
	return true;
}

bool ExpertDataViewRenderer::HasEditorCtrl() const
{
	switch (m_pModelNode->getElementType())
	{
	case ElementDataViewModelNode::ValueElement:
		return true;
	default:
		return false;
	}
}

wxWindow * ExpertDataViewRenderer::CreateEditorCtrl(wxWindow * parent, wxRect labelRect, const wxVariant & value)
{
	m_pEditingNode = (ElementDataViewModelNode*)value.GetVoidPtr();

	return new wxTextCtrl(
		parent,
		wxID_ANY,
		m_pEditingNode->getLabel(),
		labelRect.GetLeftTop(),
		labelRect.GetSize());
}

bool ExpertDataViewRenderer::GetValueFromEditorCtrl(wxWindow * editor, wxVariant & value)
{
	wxString v = ((wxTextCtrl*)editor)->GetValue();

	try
	{
		m_pEditingNode->getSepaElement()->setValue(v);
	}
	catch (Separatista::InvalidValueException &ive)
	{
		wxLogError(ive.getMessage());
		return false;
	}
	return true;
}


