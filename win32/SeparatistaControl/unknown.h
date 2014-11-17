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

#ifndef SEPARATISTA_UNKNOWN_H
#define SEPARATISTA_UNKNOWN_H

#include <windows.h>
#include "separatista/debug/debug.h"

template <class T>
class SepaControlUnknown : public T
{
public:
	/**
		This constructor takes the parent COM object as an argument.
		It will call AddRef on the parent object and call Release on destruction. This
		will make sure the parent object isn't destroyed before this child.
	*/
	SepaControlUnknown(IUnknown *pParent = NULL);

	// IUnknown methods
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** pvvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

protected:
	/**
		Destructor.
		Calls Release on the parent COM object if set through the constructor.
		Destructor with protected access. This object has to be freed through Release method
		since it uses reference counting.
		@see Release()
	*/
	virtual ~SepaControlUnknown();

	ULONG m_uRefCount;
	IUnknown *m_pParent;
};

#endif // !definded SEPARATISTA_UNKNOWN_H
