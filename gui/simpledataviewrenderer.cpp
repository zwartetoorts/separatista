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

#include "simpledataviewrenderer.h"
#include "simpledataviewmodel.h"

SimpleDataViewRenderer::SimpleDataViewRenderer()
	:wxDataViewCustomRenderer(wxT("void*"), wxDATAVIEW_CELL_EDITABLE)
{
	m_pSepaElement = NULL;
	m_pValueElement = NULL;
}

bool SimpleDataViewRenderer::GetValue(wxVariant& value) const
{
	return true;
}

bool SimpleDataViewRenderer::SetValue(const wxVariant& value)
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode *)value.GetVoidPtr();

	m_pSepaElement = pNode->getSepaElement();
	m_pValueElement = pNode->getSimpleViewDataElement();

	return true;
}

wxSize SimpleDataViewRenderer::GetSize() const
{
	const wchar_t *pText;
	if (m_pSepaElement && (pText = m_pSepaElement->getTextValue()))
	{
		return GetTextExtent(pText);
	}
	else
		return GetTextExtent(wxT(" "));
}

bool SimpleDataViewRenderer::Render(wxRect cell, wxDC* dc, int state)
{
	if (!m_pSepaElement)
		return false;

	const wchar_t *pText = m_pSepaElement->getTextValue();
	if (pText)
	{
		RenderText(pText, 0, cell, dc, state);
		return true;
	}
	return true;
}

bool SimpleDataViewRenderer::HasEditorCtrl() const
{
	return true;
}

wxWindow * SimpleDataViewRenderer::CreateEditorCtrl(wxWindow * parent, wxRect labelRect, const wxVariant & value)
{
	return NULL;
}

bool SimpleDataViewRenderer::GetValueFromEditorCtrl(wxWindow * editor, wxVariant & value)
{
	return false;
}

