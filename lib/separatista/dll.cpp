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
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include <windows.h>
#include "separatista.h"
#include "iban/iban.h"

using namespace xercesc;
using namespace Separatista;

/**
	Modules handle
*/
HMODULE g_hinstDll = 0;

/**
	DllMain
*/

BOOL WINAPI DllMain(HINSTANCE hinstDll,
	DWORD fdwReason,
	LPVOID lpvReserved)
{
	// Get reason
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Store module handle
		g_hinstDll = hinstDll;

		// Init xerces
		try
		{
			XMLPlatformUtils::Initialize();
		}
		catch (const XMLException &e)
		{
			return FALSE;
		}
		break;
	case DLL_PROCESS_DETACH:
		XMLPlatformUtils::Terminate();
	}

	return TRUE;
}

bool loadSchema(xercesc::XercesDOMParser *parser, const wchar_t *name)
{
	HRSRC hResInfo;
	HGLOBAL hResource;
	LPVOID lpData;
	DWORD bytes;

	hResInfo = FindResource(g_hinstDll, name, TEXT("XSD"));
	if (!hResInfo)
		return false;

	bytes = SizeofResource(g_hinstDll, hResInfo);
	if (!bytes)
		return false;

	hResource = LoadResource(g_hinstDll, hResInfo);
	if (!hResource)
		return false;

	lpData = LockResource(hResource);
	if (!lpData)
		return false;

	xercesc::MemBufInputSource source((const XMLByte*)lpData, bytes, name);
	if (parser->loadGrammar(source, Grammar::SchemaGrammarType, true))
		return true;

	return false;
}

/**
	Win32 implementation of SeparatistaDocument::loadSchemas
*/
bool SeparatistaDocument::loadSchemas(xercesc::XercesDOMParser *parser)
{
	if (!parser)
		return false;

	if (!loadSchema(parser, TEXT("PAIN_008_001_02_XSD")))
		return false;
	if (!loadSchema(parser, TEXT("PAIN_001_001_03_XSD")))
		return false;

	return true;
}

