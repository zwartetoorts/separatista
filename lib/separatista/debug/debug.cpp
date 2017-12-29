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

#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "debug.h"

#ifdef SEPARATISTA_DEBUG

#	ifdef SEPARATISTA_DEBUG_NEW

		std::unordered_map<const void*, Separatista::Debug::MemDebug> *Separatista::Debug::MemDebug::g_memMap = NULL;

#	endif // !defined SEPARATISTA_DEBUG_NEW 

int Separatista::Debug::DebugLogger::g_indent = 0;

Separatista::Debug::DebugLogger::DebugLogger(const wchar_t *pMethodname, const void *pObject)
{
	std::wostringstream fmt;

	m_pMessage = pMethodname;
	for (int c = 0; c < g_indent; c++)
		fmt << TEXT('\t');
	
	fmt << TEXT("->");
#ifdef SEPARATISTA_DEBUG_NEW
	// Add Object information
	if (pObject)
	{
		std::unordered_map<const void *, MemDebug>::iterator &it = Separatista::Debug::MemDebug::g_memMap->find(pObject);
		if (it != Separatista::Debug::MemDebug::g_memMap->end())
		{
			MemDebug &m = it->second;
			fmt << m.m_TypeName << TEXT("::");
			fmt << pMethodname << TEXT(" address ");

			fmt.setf(std::ios::hex, std::ios::basefield);
			fmt << it->first;
			fmt.setf(std::ios::dec);
			fmt << TEXT(" object allocated in ") << m.m_pFilename << TEXT(" at line ") << m.m_nLine << TEXT("\r\n");
		}
		else
			fmt << pMethodname << TEXT(" ");
	}
	else
		fmt << pMethodname << TEXT(" ");
#else 
	fmt << pMethodname << TEXT(" ");
#endif

	fmt << TEXT("\r\n");

	OutputDebugString(fmt.str().data());
	g_indent++;
}

Separatista::Debug::DebugLogger::~DebugLogger()
{
	std::wstring fmt;

	g_indent--;
	for (int c = 0; c < g_indent; c++)
		fmt += TEXT('\t');
	
	fmt += TEXT("<-");
	fmt += m_pMessage;
	fmt += TEXT("\r\n");

	OutputDebugString(fmt.data());
}

void Separatista::Debug::DebugLogger::log(const wchar_t *pMessage, const wchar_t *pFilename, const unsigned int line)
{
	std::wstring fmt;

	for (int c = 0; c < g_indent; c++)
		fmt += TEXT('\t');
	
	fmt += pMessage;
	fmt += TEXT(" (");
	fmt += pFilename;
	fmt += TEXT(" @ #");
	fmt += line;
	fmt += TEXT(")\r\n");

	OutputDebugString(fmt.data());
}

#ifdef SEPARATISTA_DEBUG_NEW

void Separatista::Debug::MemDebug::trackMemory(void *ptr, const MemDebug &memDebug, const char *pTypeName)
{
	if (g_memMap)
	{
		g_memMap->emplace(ptr, memDebug);
		std::mbstowcs((*g_memMap)[ptr].m_TypeName, pTypeName, 100);
		(*g_memMap)[ptr].m_TypeName[99] = TEXT('\0');

		// Report allocating object
		std::wostringstream wos;
		wos.setf(std::ios::hex, std::ios::basefield);

		for (int c = 0; c < DebugLogger::g_indent; c++)
			wos << TEXT('\t');

		wos << TEXT("  ");
		wos << TEXT("Allocated object of type ");
		wos << (*g_memMap)[ptr].m_TypeName;
		wos << TEXT(" at ");
		wos << ptr << TEXT("\r\n");

		OutputDebugString(wos.str().data());
	}
}

void Separatista::Debug::MemDebug::releaseMemory(void *ptr)
{
	if (!g_memMap)
		return;

	// Check if key exists
	if (g_memMap->find(ptr) != g_memMap->end())
	{
		// Report freeing object
		std::wostringstream wos;
		wos.setf(std::ios::hex, std::ios::basefield);

		for (int c = 0; c < DebugLogger::g_indent; c++)
			wos << TEXT('\t');

		wos << TEXT("  ");
		wos << TEXT("Freed object of type ");
		wos << (*g_memMap)[ptr].m_TypeName;
		wos << TEXT(" at ");
		wos << ptr << TEXT("\r\n")	;

		g_memMap->erase(ptr);

		OutputDebugString(wos.str().data());
	}
	/*else
	{
		std::wostringstream wos;
		wos.setf(std::ios::hex, std::ios::basefield);
		wos << TEXT("WARNING: Deleting unallocated object: ");
		wos << ptr;
		wos << TEXT("\r\n");
		OutputDebugString(wos.str().data());
	}*/
}

bool Separatista::Debug::MemDebug::init()
{
	DEBUG_STATIC_METHOD;
	
	g_memMap = new std::unordered_map < const void*, MemDebug >;
	if (!g_memMap)
		return false;
	return true;
}

bool Separatista::Debug::MemDebug::exit()
{
	DEBUG_STATIC_METHOD;
	std::unordered_map<const void *, MemDebug>* memMap;

	memMap = g_memMap;
	g_memMap = NULL;
	if (!memMap->empty())
	{
		OutputDebugString(TEXT("WARNING: MEMORY LEAKS DETECTED !!!!!\r\n"));

		for (auto& x : *memMap)
		{
			std::wostringstream wos;
			wos.setf(std::ios::hex, std::ios::basefield);
			wos << x.first;
			wos.setf(std::ios::dec);
			wos << TEXT(" ") << x.second.m_TypeName;
			wos << TEXT(" object allocated in ") << x.second.m_pFilename << TEXT(" at line ") << x.second.m_nLine << TEXT("\r\n");
			OutputDebugString(wos.str().data());
		}
		memMap->clear();
	}
	delete memMap;
	
	return true;
}

#endif // defined SEPARATISTA_DEBUG_NEW

#endif // defined SEPARATISTA_DEBUG

