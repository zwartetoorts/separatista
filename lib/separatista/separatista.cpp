/***************************************************************************
*   Copyright (C) 2013 by Okkel Klaver   *
*   info@vanhetland.nl   *
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

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLString.hpp>

#include "debug/debug.h"
#include "separatista.h"

using namespace Separatista;

static const wchar_t* g_pDebugMessage = NULL;

IOErrorCode Separatista::Init()
{
	DEBUG_METHOD;
	try
	{
		xercesc::XMLPlatformUtils::Initialize();
	}
	catch (const xercesc::XMLException &e)
	{
		g_pDebugMessage = e.getMessage();
		return IOErrorCode::Xerces;
	}
	return IOErrorCode::Success;
}

void Separatista::Terminate()
{
	DEBUG_METHOD;
	xercesc::XMLPlatformUtils::Terminate();
}

