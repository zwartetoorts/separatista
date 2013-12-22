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

#ifndef SEPARATISTA_H
#define SEPARATISTA_H

#ifdef SEPARATISTA_BUILDINGDLL
#	define SEPARATISTA_EXTERN __declspec(dllexport)
#elif defined SEPARATISTA_USINGDLL
#		define SEPARATISTA_EXTERN __declspec(dllimport)
#else
#	define SEPARATISTA_EXTERN
#endif

/**
	Check for xerces headers being included, if not, were not building separatista.
	This means it's neccessary to include xerces headers BEFORE separatista headers.
	All this fuzz is needed because xerces aliases it's namespace so we can't forward declare it.
*/
#ifdef XERCES_HAS_CPP_NAMESPACE
XERCES_CPP_NAMESPACE_BEGIN
class DOMDocument;
XERCES_CPP_NAMESPACE_END;
#else
// Forward declare xerces classes
namespace xercesc
{
	class DOMDocument;
};
#endif

namespace Separatista
{

/**
	
*/
class DirectDebitDocument
{
public:
	SEPARATISTA_EXTERN DirectDebitDocument();

	SEPARATISTA_EXTERN virtual ~DirectDebitDocument();

	/**
		Code indicating success or failure reading a DirectDebitDocument
	*/
	enum OpenStatus
	{
		/// Success
		OK = 0,
		/// Error opening/reading file
		E_FILE,
		/// Error parsing file or not a valid XML file
		E_FORMAT,
		/// No memory available
		E_MEMORY
	};

	/**
		Read document
	*/
	SEPARATISTA_EXTERN OpenStatus Open(const char *path);
private:
	char *m_pErrorMessage;
	xercesc::DOMDocument *m_pDOMDocument;
};



};

#endif // !defined SEPARATISTA_H

