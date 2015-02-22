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

#include <vector>
#include <string>

#include "separatista.h"
#include "xerces_types.h"

#ifndef SEPARATISTA_DOCUMENTREADER_H
#define SEPARATISTA_DOCUMENTREADER_H

namespace Separatista
{
	/**
		Error with code and xerces message.
	*/
	typedef struct
	{
		typedef enum
		{
			ETC_WARNING,
			ETC_ERROR,
			ETC_FATALERROR
		} ErrorCode;
		ErrorCode errorCode;
		std::wstring msg;
	} ErrorType;

	class SEPARATISTA_EXTERN DocumentReader
	{
	public:
		DocumentReader();

		/**
			Destroys all messages in the error list.
		*/
		~DocumentReader();

		/// Get the count of Errors from xerces
		int getErrorCount() const;

		/// Get the code for error a index
		const ErrorType::ErrorCode getErrorCode(int index) const;

		/// Get the message for error at index
		const wchar_t* getErrorMessage(int index) const;

		/// @see SAXParseException
		void warning(const SAXParseException &e);

		/// @see SAXParseException
		void error(const SAXParseException &e);

		/// @see SAXParseException
		void fatalError(const SAXParseException &e);

		/// @see SAXParseException
		void resetErrors();

		/**
			Platform specific implementation. Loads the schema for the namespace to the parser.
			@param pNameSpace The namespace URI to load the schema for.
			@remarks The windows implementation is found in dll.cpp
			@return Error code
		*/
		IOErrorCode loadSchema(const wchar_t *pNameSpace);

		/**
			Parse the document at path.
		*/
		IOErrorCode parseFile(const wchar_t *pPath);

		/**
			Returns the document as SeparatistaDocument. This is a new instance that will be owned by the caller. The caller should free the object.
			@throws InvalidValueException 
			@throws InvalidChoiceException
		*/
		SeparatistaDocument* getDocument();

	protected:
		void appendError(ErrorType::ErrorCode etc, const SAXParseException &e);

	private:
		XercesDOMParser *m_pParser;
		DOMDocument *m_pDocument;
		std::vector<ErrorType*> m_ErrorList;
	};
}

#endif // SEPARATISTA_DOCUMENTREADER_H