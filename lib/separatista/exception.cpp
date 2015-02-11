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
#include "exception.h"
#include "debug/debug.h"

using namespace Separatista;

Exception::Exception(const wchar_t *pMessage)
{
	m_msg = pMessage;
}

#ifdef SEPARATISTA_DEBUG

Exception::Exception(const wchar_t *pMessage, const wchar_t *pPath, int line)
{
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
	return m_msg.data();
}

