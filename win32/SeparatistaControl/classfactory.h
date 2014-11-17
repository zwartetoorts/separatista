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

#ifndef SEPARATISTA_CLASSFACTORY_H
#define SEPARATISTA_CLASSFACTORY_H

#include <windows.h>
#include "unknown.cpp"
#include "separatista/debug/debug.h"

/**
	Component creation function, used as an easy way to create an instance
	from SepaControlClassFactory
*/
typedef HRESULT (*FPCREATECOMP)(REFCLSID, void**);

/**
	Creates all instances of needed classes
*/
class SepaControlClassFactory : public SepaControlUnknown<IClassFactory>
{
public:
	/// @param fpCreate Pointer to the Class creation function
	SepaControlClassFactory(FPCREATECOMP fpCreate);
	virtual ~SepaControlClassFactory();

	// IClassFactory methods
	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** pvvObject);
	HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
protected:
	ULONG m_uRefCount;
	FPCREATECOMP m_fpCreateComp;
};

#endif // SEPARATISTA_CLASSFACTORY_H