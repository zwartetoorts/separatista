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

#include "classfactory.h"
#include "dll.h"

SepaControlClassFactory::SepaControlClassFactory(FPCREATECOMP fpCreate)
{
	m_fpCreateComp = fpCreate;
	m_uRefCount = 0;
	g_uDllRefCount++;
}

SepaControlClassFactory::~SepaControlClassFactory()
{
	g_uDllRefCount--;
}

ULONG SepaControlClassFactory::AddRef()
{
	return ++m_uRefCount;
}

ULONG SepaControlClassFactory::Release()
{
	ULONG uRet = --m_uRefCount;
	if(0 == uRet)
		delete this;
	return uRet;
}

HRESULT SepaControlClassFactory::QueryInterface(const IID &iid,
												void **pvvObject)
{
	*pvvObject = NULL;
	if(IsEqualIID(iid, IID_IUnknown) ||
		IsEqualIID(iid, IID_IClassFactory))
	{
		*pvvObject = this;
		AddRef();
	}
	else
		return E_NOINTERFACE;

	return S_OK;
}

HRESULT SepaControlClassFactory::CreateInstance(IUnknown *pUnkOuter,
												const IID &riid,
												void **pvvObject)
{
	HRESULT hRet;
	
	if(NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	hRet = m_fpCreateComp(riid, pvvObject);
	
	return hRet;
}

HRESULT SepaControlClassFactory::LockServer(BOOL fLock)
{
	if(fLock)
		g_uLockCount++;
	else
		g_uLockCount--;
	return S_OK;
}
