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

#include "debug.h"

#ifdef SEPARATISTA_DEBUG

int Separatista::Debug::DebugLogger::g_indent = 0;

Separatista::Debug::DebugLogger::DebugLogger(const wchar_t *pMethodname)
{
	std::wstring fmt;

	m_pMessage = pMethodname;
	for (int c = 0; c < g_indent; c++)
		fmt += TEXT('\t');
	
	fmt += TEXT("->");
	fmt += pMethodname;
	fmt += TEXT("\r\n");

	OutputDebugString(fmt.data());
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

std::unordered_map<void*, Separatista::Debug::MemDebug> *Separatista::Debug::MemDebug::g_memMap = NULL;

void Separatista::Debug::MemDebug::addMemory(void *ptr)
{
	DEBUG_METHOD
	std::pair<void*, MemDebug> p(ptr, MemDebug(TEXT(__FILE__), __LINE__));
	g_memMap->insert(p);
}

void Separatista::Debug::MemDebug::trackMemory(void *ptr, const MemDebug &memDebug, const char *pTypeName)
{
	DEBUG_METHOD
	(*g_memMap)[ptr] = memDebug;
	(*g_memMap)[ptr].m_pTypeName = pTypeName;
}

void Separatista::Debug::MemDebug::releaseMemory(void *ptr)
{
	std::wostringstream wos;
	DEBUG_METHOD

	// Check if key exists
	if (g_memMap->find(ptr) == g_memMap->end())
	{
		wos.setf(std::ios::hex, std::ios::basefield);
		wos << TEXT("WARNING: Freeing unallocated object at: ") << ptr;
		OutputDebugString(wos.str().data());
		return;
	}
	g_memMap->erase(ptr);
}

BOOL Separatista::Debug::MemDebug::init()
{
	DEBUG_METHOD
	g_memMap = new std::unordered_map < void*, MemDebug >;
	if (!g_memMap)
		return FALSE;
	return TRUE;
}

BOOL Separatista::Debug::MemDebug::exit()
{
	std::wostringstream wos;
	DEBUG_METHOD

	if (!g_memMap->empty())
	{
		OutputDebugString(TEXT("WARNING: MEMORY LEAKS DETECTED !!!!!"));

		for (std::unordered_map<void*, Separatista::Debug::MemDebug>::iterator it = g_memMap->begin();
			it != g_memMap->end(); it++)
		{
			wos.clear();
			wos.setf(std::ios::hex, std::ios::basefield);
			wos << (*it).first;
			wos.setf(std::ios::dec);
			wos << TEXT(" object allocated in ") << (*it).second.m_pFilename << TEXT(" at line ") << (*it).second.m_nLine;
			OutputDebugString(wos.str().data());
		}
		g_memMap->clear();
	}
	delete g_memMap;
	return TRUE;
}

#endif // defined SEPARATISTA_DEBUG_NEW

#endif // defined SEPARATISTA_DEBUG

