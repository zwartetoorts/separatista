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

void Separatista::Debug::MemDebug::trackMemory(void *ptr, const MemDebug &memDebug, const char *pTypeName)
{
	if (g_memMap)
	{
		g_memMap->emplace(ptr, memDebug);
		std::mbstowcs((*g_memMap)[ptr].m_TypeName, pTypeName, 100);
		(*g_memMap)[ptr].m_TypeName[99] = TEXT('\0');
	}
}

void Separatista::Debug::MemDebug::releaseMemory(void *ptr)
{
	std::wostringstream wos;

	if (!g_memMap)
		return;

	// Check if key exists
	if (g_memMap->find(ptr) != g_memMap->end())
		g_memMap->erase(ptr);
}

bool Separatista::Debug::MemDebug::init()
{
	DEBUG_METHOD
	g_memMap = new std::unordered_map < void*, MemDebug >;
	if (!g_memMap)
		return false;
	return true;
}

bool Separatista::Debug::MemDebug::exit()
{
	std::unordered_map<void *, MemDebug>* memMap;
	DEBUG_METHOD

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

