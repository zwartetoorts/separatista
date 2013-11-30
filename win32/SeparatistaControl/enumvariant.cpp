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

#include <windows.h>
#include <oleauto.h>
#include <comutil.h>
#include <array>

#include "enumvariant.h"

EnumVariant::EnumVariant()
{
	m_uRefCount = 0;
	m_pos = 0;
}

EnumVariant::~EnumVariant()
{
	std::vector<VARIANT>::iterator it;

	for(it = m_objects.begin(); it != m_objects.end(); it++)
		VariantClear(&(*it));
}

ULONG EnumVariant::AddRef()
{
	return ++m_uRefCount;
}

ULONG EnumVariant::Release()
{
	ULONG uRet;

	uRet = --m_uRefCount;
	if(0 == uRet)
		delete this;
	return uRet;
}

HRESULT EnumVariant::QueryInterface(REFIID iid, void** pvvObject)
{
	*pvvObject = NULL;

 	if(IsEqualIID(iid, IID_IUnknown) ||
		IsEqualIID(iid, IID_IEnumVARIANT))
	{
		*pvvObject = this;
		AddRef();
	}
	else
		return E_NOINTERFACE;

	return S_OK;
}

STDMETHODIMP EnumVariant::Next(unsigned long celt, VARIANT FAR* rgvar, unsigned long FAR* pceltFetched)
{
	std::size_t pos;

	if(pceltFetched != NULL)
		*pceltFetched = 0;

	if(rgvar == NULL)
		return E_INVALIDARG;

	pos = m_pos;
	for(ULONG l = 0; l < celt && pos < m_objects.size(); l++, pos++)
	{
		// Copy reference
		VariantCopy(&rgvar[l], &m_objects[pos]);
	}

	m_pos = pos;

	return S_OK;
}

STDMETHODIMP EnumVariant::Skip(unsigned long celt)
{
	m_pos += celt;

	if(m_pos > m_objects.size())
		m_pos = m_objects.size() - 1;

	return S_OK;
}

STDMETHODIMP EnumVariant::Reset()
{
	m_pos = 0;

	return S_OK;
}

STDMETHODIMP EnumVariant::Clone(IEnumVARIANT FAR* FAR* ppenum)
{
	std::vector<VARIANT>::iterator it;
	
	if(!ppenum)
		return E_INVALIDARG;

	EnumVariant *pEnumVariant = new EnumVariant();
	if(!pEnumVariant)
		return E_OUTOFMEMORY;

	// Copy and AddRef objects
	for(it = m_objects.begin(); it != m_objects.end(); it++)
		pEnumVariant->m_objects.push_back(_variant_t(*it));

	*ppenum = pEnumVariant;
	pEnumVariant->AddRef();

	return S_OK;
}

void EnumVariant::Add(VARIANT &vt)
{
	m_objects.push_back(vt);
}


