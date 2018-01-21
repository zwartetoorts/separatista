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

#include "ibantextctrl.h"

IBANTextCtrl::IBANTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size)
	:wxTextCtrl(
		parent, 
		id, 
		value, 
		pos, 
		size)
{

}

wxString IBANTextCtrl::GetValue() const
{
	wxString value, IBAN;

	// Get value and strip spaces
	value = wxTextCtrl::GetValue();
	for (auto it = value.begin(); it != value.end(); it++)
	{
		if (*it != wxT(' '))
			IBAN += *it;
	}
	return IBAN;
}

void IBANTextCtrl::OnText(wxCommandEvent &event)
{
	wxString IBAN, value;

	if (!IsModified())
		return;

	long i = GetInsertionPoint();
	value = GetValue().Upper();

	long c = 0;
	for (auto it = value.begin(); it != value.end(); it++)
	{
		// Ignore space
		if (*it == wxT(' '))
		{
			// Decrement insertion point if we didn't pass it yet
			if(c <= i)
				--i;
			continue;
		}

		// Insert space if neccesary
		if (c > 0 && c % 4 == 0)
		{
			IBAN += wxT(' ');
			// Increase insertion point if we didn't pass it yet
			if (c <= i)
				++i;
		}
		IBAN += *it;
		++c;
	}

	ChangeValue(IBAN);
	SetInsertionPoint(i);
}

wxBEGIN_EVENT_TABLE(IBANTextCtrl, wxTextCtrl)
	EVT_TEXT(wxID_ANY, IBANTextCtrl::OnText)
wxEND_EVENT_TABLE()

