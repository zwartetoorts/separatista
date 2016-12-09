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

#ifndef SEPARATISTA_H
#define SEPARATISTA_H

// Disable Visual c++ warning C4251
#ifdef _MSC_VER 
#pragma warning(disable: 4251)
#endif

#ifdef SEPARATISTA_BUILDINGDLL
#	define SEPARATISTA_EXTERN __declspec(dllexport)
#elif defined SEPARATISTA_USINGDLL
#		define SEPARATISTA_EXTERN __declspec(dllimport)
#else
#	define SEPARATISTA_EXTERN
#endif

namespace Separatista
{
	/**
		Return values of IO operations
	*/
	typedef enum
	{
		/// Ok
		Success = 0,
		/// Unknown error
		Unknown,
		/// Error was caused by the platform (os)
		Platform,
		/// Xerces caused the error, thus xml related
		Xerces,
		/// The error was caused by Separatista, internally
		Separatista,
		/// Error was caused by the document
		Document_Invalid,
		/// Path not found
		Path_Invalid,
		/// User interrupted something
		User
	} IOErrorCode;

	/// Initialization, initializes xerces
	SEPARATISTA_EXTERN IOErrorCode Init();

	/// Termination
	SEPARATISTA_EXTERN void Terminate();
}

#endif // SEPARATISTA_H
