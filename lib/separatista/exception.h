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

#ifndef SEPARATISTA_EXCEPTION_H
#define SEPARATISTA_EXCEPTION_H

#include <string>

#include "separatista.h"

#ifdef SEPARATISTA_DEBUG
#	define SEPARATISTA_EXCEPTION(msg) msg, TEXT(__FILE__), __LINE__
#else
#	define SEPARATISTA_EXCEPTION(msg) TEXT(msg)
#endif // defined SEPARATISTA_DEBUG

#define SEPARATISTA_REPORT(e) LOG(e.getMessage())

namespace Separatista
{
	class Element;

	class SEPARATISTA_EXTERN Exception
	{
	public:
		Exception(const wchar_t *pMessage);
#ifdef SEPARATISTA_DEBUG
		Exception(const wchar_t *pMessage, const wchar_t *pPath, int line);

#endif
		const wchar_t* getMessage() const;

	protected:
		void setMessage(const wchar_t *pMessage);
	private:
		std::wstring m_msg;
	};


	/// Element exception, thrown when an element method called doesn't belong to the element type.
	class SEPARATISTA_EXTERN ElementException : public Exception
	{
	public:
		ElementException(const wchar_t *pMessage, const Element *pSource);

#ifdef SEPARATISTA_DEBUG
		ElementException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, const Element *pSource);
#endif

		/// Returns the target element 
		const Element* getSourceElement() const;

	private:
		const Element *m_pSource;
	};

	/// Unsupported tag exception, thrown when CreateElementByTag doesn't support the tag
	class SEPARATISTA_EXTERN UnsupportedTagException : public ElementException
	{
	public:
		UnsupportedTagException(const wchar_t *pMessage, const Element *pSource, const wchar_t *pTag);

#ifdef SEPARATISTA_DEBUG
		UnsupportedTagException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, const Element *pSource, const wchar_t *pTag);
#endif
		/// Returns the unsupported tag
		const wchar_t* getTag() const;

	private:
		std::wstring m_Tag;
	};

}
#endif // !defined SEPARATISTA_EXCEPTION_H
