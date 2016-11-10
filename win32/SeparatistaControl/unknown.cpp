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

#ifndef SEPAUNKNOWN_CPP
#define SEPAUNKNOWN_CPP

#include <windows.h>
#include "dll.h"
#include "unknown.h"

template <class T> SepaControlUnknown<T>::SepaControlUnknown()
{
	// Global
	g_uDllRefCount++;

	// Object
	m_uRefCount = 0;
}

template <class T> SepaControlUnknown<T>::~SepaControlUnknown()
{
	g_uDllRefCount--;
}

template <class T> ULONG SepaControlUnknown<T>::AddRef()
{
	return ++m_uRefCount;
}

template <class T> ULONG SepaControlUnknown<T>::Release()
{
	ULONG uRet;

	uRet = --m_uRefCount;
	if (0 == uRet)
		delete this;
	return uRet;
}

template <class T> HRESULT SepaControlUnknown<T>::QueryInterface(const IID &iid, void **pvvObject)
{
	*pvvObject = NULL;

	if (IsEqualIID(iid, IID_IUnknown) ||
		IsEqualIID(iid, __uuidof(T)))
	{
		*pvvObject = this;
		AddRef();
	}
	else
		return E_NOINTERFACE;

	return S_OK;
}

#endif // !defined SEPAUNKNOWN_CPP
