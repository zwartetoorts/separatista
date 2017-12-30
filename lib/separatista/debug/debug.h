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
#include <array>
#include <unordered_map>
#include <cstdlib>

#ifndef SEPARATISTA_DEBUG_H
#define SEPARATISTA_DEBUG_H

#ifdef SEPARATISTADEBUG_BUILDINGDLL
#	define SEPARATISTADEBUG_EXTERN __declspec(dllexport)
#elif defined SEPARATISTADEBUG_USINGDLL
#		define SEPARATISTADEBUG_EXTERN __declspec(dllimport)
#else
#	define SEPARATISTADEBUG_EXTERN
#endif

#ifdef SEPARATISTA_DEBUG

// First declare macro's
#define LOG(message) Separatista::Debug::DebugLogger::log(message, TEXT(__FILE__), __LINE__)
#define DEBUG_METHOD Separatista::Debug::DebugLogger __debugLogger(TEXT(__FUNCTION__), this)
#define DEBUG_STATIC_METHOD Separatista::Debug::DebugLogger __debugLogger(TEXT(__FUNCTION__))

namespace Separatista
{
	namespace Debug
	{
		/**
			Debug logger class. Handles all logging. 
		*/
		class SEPARATISTADEBUG_EXTERN DebugLogger
		{
		public:
			/**
				Constructor, used by the DEBUG_METHOD macro. Created as a local var and thus destroyed on function exit.
				Will print '->Methodname' with indent.
				@param pMethodname Name of the method to print.
				*/
			DebugLogger(const wchar_t *pMethodname, const void* pObject = NULL);

			/**
				D'tor, prints '<-Methodname' with indent.
				*/
			~DebugLogger();

			/**
				log method, outputs a formatted message to cout.
			*/
			static void log(const wchar_t *pMessage, const wchar_t *pFilename, const unsigned int line);

		private:
			static int g_indent;

			const wchar_t *m_pMessage;

			friend class MemDebug;
		};

#ifdef SEPARATISTA_DEBUG_NEW

		class SEPARATISTADEBUG_EXTERN MemDebug
		{
		public:
			MemDebug() 
			{ 
				std::wcscpy(m_TypeName, TEXT("Unknown"));
			};

			MemDebug(const wchar_t *pFilename, int nLine) :
				m_pFilename(pFilename),
				m_nLine(nLine)
			{ 
				std::wcscpy(m_TypeName, TEXT("Unknown"));
			};

			/**
				Sets filename, lineno and type name of a memory block in the internal list.
				@param ptr Pointer to the allocated block
				@param memDebug MemDebug object containing filename ans lineno
				@param pTypeName String contaning the class name of the allocated object
			*/
			static void trackMemory(void *ptr, const MemDebug &memDebug, const char *pTypeName);

			/**
				Removes the allocated memory from the internal list.
			*/
			static void releaseMemory(void *ptr);

			/**
				Init
			*/
			static bool init();

			/**
				Reports all memory leaks
			*/
			static bool exit();
		private:
			wchar_t m_TypeName[100];
			const wchar_t *m_pFilename;
			int m_nLine;

			static std::unordered_map<const void *, MemDebug>* g_memMap;

			friend class DebugLogger;
		};

		/// Template cast function for debug new
		template <class T> inline T* operator *(const MemDebug &memDebug, T *p)
		{
			Separatista::Debug::MemDebug::trackMemory(p, memDebug, typeid(T).name());
			return p;
		}

#endif //defined SEPARATISTA_DEBUG_NEW

	}
}

#ifdef SEPARATISTA_DEBUG_NEW

#ifdef _MSC_VER
#pragma warning (disable: 4595)
#endif

// Prevent internal use of new from being trapped
#ifndef SEPARATISTADEBUG_BUILDINGDLL

inline void* operator new(size_t size)
{
	void *p = std::malloc(size);
	if (p == NULL)
		throw std::bad_alloc();
	
	return p;
}

inline void* operator new[](size_t size)
{
	void *p = std::malloc(size);
	if (p == NULL)
		throw std::bad_alloc();

	return p;
}

inline void operator delete (void *ptr)
{
	Separatista::Debug::MemDebug::releaseMemory(ptr);
	std::free(ptr);
}

inline void operator delete [](void *ptr)
{
	Separatista::Debug::MemDebug::releaseMemory(ptr);
	std::free(ptr);
}

#define new Separatista::Debug::MemDebug(TEXT(__FILE__), __LINE__) * new

#endif // !defined SEPARATISTADEBUG_BUILDINGDLL
#endif // !defined SEPARATISTA_DEBUG_NEW

#else // !defined SEPARATISTA_DEBUG

#define LOG(message) 
#define DEBUG_METHOD
#define DEBUG_STATIC_METHOD

#endif // defined SEPARATISTA_DEBUG

#endif // !defined SEPARATISTA_DEBUG_H
