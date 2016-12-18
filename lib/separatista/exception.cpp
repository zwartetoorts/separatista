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

#include <sstream>

#include "separatista.h"
#include "separatista/element.h"
#include "separatista/exception.h"
#include "debug/debug.h"

using namespace Separatista;

Exception::Exception(const wchar_t *pMessage)
{
	DEBUG_METHOD;

	m_msg = pMessage;
}

#ifdef SEPARATISTA_DEBUG

Exception::Exception(const wchar_t *pMessage, const wchar_t *pPath, int line)
{
	DEBUG_METHOD;
	std::wostringstream wos;

	wos << TEXT("Exception thrown from ");
	wos << pPath;
	wos << TEXT(" @ line ");
	wos.setf(std::ios::dec);
	wos << line;
	wos << TEXT(": ");
	wos << pMessage;

	m_msg = wos.str();
}

#endif // !defined SEPARATISTA_DEBUG

const wchar_t* Exception::getMessage() const
{
	DEBUG_METHOD;
	return m_msg.data();
}

void Exception::setMessage(const wchar_t *pMessage)
{
	DEBUG_METHOD;
	m_msg = pMessage;
}

ElementException::ElementException(const wchar_t *pMessage, const Element *pSource) :
	Exception(pMessage),
	m_pSource(pSource)
{
	DEBUG_METHOD;
	std::wostringstream wos;

	wos << pSource->getTag()
		<< TEXT(": ")
		<< getMessage();
	setMessage(wos.str().c_str());
}

#ifdef SEPARATISTA_DEBUG
ElementException::ElementException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, const Element *pSource) :
	Exception(pMessage, pPath, nLine),
	m_pSource(pSource)
{
	DEBUG_METHOD;
	std::wostringstream wos;

	wos << pSource->getTag()
		<< TEXT(": ")
		<< getMessage();
	setMessage(wos.str().c_str());
};
#endif

const Element* ElementException::getSourceElement() const
{
	return m_pSource;
};

UnsupportedTagException::UnsupportedTagException(const wchar_t *pMessage, const Element *pSource, const wchar_t *pTag) :
	ElementException(pMessage, pSource),
	m_Tag(pTag)
{
	DEBUG_METHOD;
	std::wostringstream wos;

	wos << pTag
		<< TEXT("@")
		<< getMessage();
	setMessage(wos.str().c_str());
}

#ifdef SEPARATISTA_DEBUG
UnsupportedTagException::UnsupportedTagException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, const Element *pSource, const wchar_t *pTag) :
	ElementException(pMessage, pPath, nLine, pSource),
	m_Tag(pTag)
{
	DEBUG_METHOD;
	std::wostringstream wos;

	wos << pTag
		<< TEXT("@")
		<< getMessage();
	setMessage(wos.str().c_str());

}
#endif

const wchar_t* UnsupportedTagException::getTag() const
{
	return m_Tag.c_str();
}
