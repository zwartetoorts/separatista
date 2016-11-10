/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
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

#include <windows.h>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "separatista.h"
#include "documentreader.h"
#include "debug/debug.h"

using namespace Separatista;

/**
	Module handle
*/
HMODULE g_hinstDll = 0;

/**
	DllMain
*/

BOOL WINAPI DllMain(
	HINSTANCE hinstDll,
	DWORD fdwReason,
	LPVOID lpvReserved)
{
	DEBUG_METHOD

	// Get reason
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Store module handle
		g_hinstDll = hinstDll;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

// Load schema from dll resource

IOErrorCode DocumentReader::loadSchema(const wchar_t *name)
{
	DEBUG_METHOD;

	HRSRC hResInfo;
	HGLOBAL hResource;
	LPVOID lpData;
	DWORD bytes;

	if (!m_pParser)
		return Xerces;

	hResInfo = FindResource(g_hinstDll, name, TEXT("XSD"));
	if (!hResInfo)
		return Platform;

	bytes = SizeofResource(g_hinstDll, hResInfo);
	if (!bytes)
		return Platform;

	hResource = LoadResource(g_hinstDll, hResInfo);
	if (!hResource)
		return Platform;

	lpData = LockResource(hResource);
	if (!lpData)
		return Platform;

	try
	{
		xercesc::MemBufInputSource source((const XMLByte*)lpData, bytes, name);
		if (m_pParser->loadGrammar(source, xercesc::Grammar::SchemaGrammarType, true))
		{
			m_pParser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
			m_pParser->useCachedGrammarInParse(true);
			m_pParser->setLoadSchema(false);
			m_pParser->setDoSchema(true);
			m_pParser->setValidationConstraintFatal(true);
			return Success;
		}
	}
	catch (const xercesc::XMLException &e)
	{
		LOG(e.getMessage());
	}

	return Xerces;
}
