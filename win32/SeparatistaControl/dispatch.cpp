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

#ifndef SEPADISPATCH_CPP
#define SEPADISPATCH_CPP

#include <windows.h>
#include "dll.h"
#include "dispatch.h"

template <class T> SepaControlDispatch<T>::SepaControlDispatch(IDispatch *pParent)
{
	g_uDllRefCount++;
	m_uRefCount = 0;

	m_pTypeLib = NULL;
	m_pTypeInfo = NULL;

	if(LoadTypeLib(g_lpszDllPath, &m_pTypeLib) == S_OK)
	{
		if(m_pTypeLib->GetTypeInfoOfGuid(__uuidof(T), &m_pTypeInfo) != S_OK)
		{
			m_pTypeLib->Release();
			m_pTypeLib = NULL;
		}
	}

	// Set parent
	m_pParent = pParent;
	if(pParent)
		pParent->AddRef();
}

template <class T> SepaControlDispatch<T>::~SepaControlDispatch()
{
	if(m_pTypeInfo)
		m_pTypeInfo->Release();
	if(m_pTypeLib)
		m_pTypeLib->Release();
	g_uDllRefCount--;

	// Check parent and release if necessary
	if(m_pParent)
		m_pParent->Release();
}

template <class T> template <class C> HRESULT SepaControlDispatch<T>::Create(REFCLSID rclid, void** pvvObject)
{
	HRESULT hr;
	SepaControlDispatch<T>* pDispatch;

	pDispatch = new C();
	if(!pDispatch)
		return E_OUTOFMEMORY;

	if((hr = pDispatch->QueryInterface(rclid, pvvObject)) != S_OK)
		delete pDispatch;

	return hr;
}

template <class T> ULONG SepaControlDispatch<T>::AddRef()
{
	return ++m_uRefCount;
}

template <class T> ULONG SepaControlDispatch<T>::Release()
{
	ULONG uRet;

	uRet = --m_uRefCount;
	if(0 == uRet)
		delete this;
	return uRet;
}

template <class T> HRESULT SepaControlDispatch<T>::QueryInterface(const IID &iid, void **pvvObject)
{
	*pvvObject = NULL;

 	if(IsEqualIID(iid, IID_IUnknown) ||
		IsEqualIID(iid, IID_IDispatch) ||
		IsEqualIID(iid, __uuidof(T)))
	{
		*pvvObject = this;
		AddRef();
	}
	else
		return E_NOINTERFACE;

	return S_OK;
}

template <class T> HRESULT SepaControlDispatch<T>::GetTypeInfoCount(unsigned int *pctInfo)
{
	*pctInfo = 1;
	return S_OK;
}

template <class T> HRESULT SepaControlDispatch<T>::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	*ppTInfo = NULL;
	if(iTInfo != 0)
		return DISP_E_BADINDEX;
	if(!m_pTypeInfo)
		return S_FALSE;

	*ppTInfo = m_pTypeInfo;
	m_pTypeInfo->AddRef();
	return S_OK;
}

template <class T> HRESULT SepaControlDispatch<T>::GetIDsOfNames(const IID &riid, OLECHAR **rgszNames, unsigned int cNames, LCID lcid, DISPID *rgDispId)
{
	if(!m_pTypeInfo)
		return S_FALSE;

	return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
}

template <class T> HRESULT SepaControlDispatch<T>::Invoke(DISPID dispIdMember, const IID &riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, unsigned int *puArgErr)
{
	if(!m_pTypeInfo)
		return S_FALSE;

	return m_pTypeInfo->Invoke(this, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}

#endif // !defined DISPATCH_CPP
