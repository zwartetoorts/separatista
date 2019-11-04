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

#include "currencytextctrl.h"

CurrencyTextCtrl::CurrencyTextCtrl(wxWindow * parent, wxWindowID id, const wxString & value, const wxPoint & pos, const wxSize & size)
	:wxTextCtrl(parent, id, value, pos, size)
{
}

void CurrencyTextCtrl::OnChar(wxKeyEvent & event)
{
	event.Skip();

	wxChar keyCode = event.GetUnicodeKey();

	// we don't filter special keys and delete
	if (keyCode < WXK_SPACE || keyCode == WXK_DELETE || keyCode > WXK_START)
		return;

	const wxString s = wxT("0123456789.");
	if (s.Find(keyCode) == wxNOT_FOUND)
		event.Skip(false);
}

wxBEGIN_EVENT_TABLE(CurrencyTextCtrl, wxTextCtrl)
	EVT_CHAR(CurrencyTextCtrl::OnChar)
wxEND_EVENT_TABLE()

