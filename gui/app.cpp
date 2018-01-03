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


#include <separatista/separatista.h>
#include <separatista/debug/debug.h>


#include "app.h"
#include "mainframe.h"

wxIMPLEMENT_APP(SeparatistaApp);

bool SeparatistaApp::OnInit()
{
	// Initialize Separatista
	if (Separatista::Init() != Separatista::IOErrorCode::Success)
		return false;

	MainFrame *frame = new MainFrame();
	frame->Show(true);
	return true;
}
