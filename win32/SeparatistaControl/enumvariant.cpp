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

#include "enumvariant.h"

EnumVariant::EnumVariant()
:SepaControlUnknown<IEnumVARIANT>()
{
	m_uRefCount = 0;
	m_pos = 0;
	m_wpos = 0;
	m_size = 0;
}

EnumVariant::~EnumVariant()
{
	VariantBlockList::iterator it;
	VariantBlockType *a;

	// Enum al pointers
	for (it = m_objects.begin(); it != m_objects.end(); it++)
	{
		// Clear all VARIANTS
		a = *it;
		for (size_t c = 0; c < VariantBlockSize; c++)
			VariantClear(&a->at(c));
		delete a;
	}
}

STDMETHODIMP EnumVariant::Next(unsigned long celt, VARIANT FAR* rgvar, unsigned long FAR* pceltFetched)
{
	HRESULT hr;

	if(pceltFetched != NULL)
		*pceltFetched = 0;

	if(rgvar == NULL)
		return E_INVALIDARG;

	if ((m_pos + celt) > m_wpos && pceltFetched == NULL)
		return S_FALSE;

	for (ULONG l = 0; l < celt && m_pos < m_wpos; l++, m_pos++)
	{
		// Init dest VARIANT and copy
		VariantInit(&rgvar[l]);
		hr = VariantCopy(&rgvar[l], &Get(m_pos));
		if (FAILED(hr))
			return hr;
		if (pceltFetched)
			*pceltFetched = l;
	}

	return S_OK;
}

STDMETHODIMP EnumVariant::Skip(unsigned long celt)
{
	m_pos += celt;

	if(m_pos > m_size)
		m_pos = m_size - 1;

	return S_OK;
}

STDMETHODIMP EnumVariant::Reset()
{
	m_pos = 0;

	return S_OK;
}

STDMETHODIMP EnumVariant::Clone(IEnumVARIANT FAR* FAR* ppenum)
{
	HRESULT hr;

	if(!ppenum)
		return E_INVALIDARG;

	EnumVariant *pEnumVariant = new EnumVariant();
	if(!pEnumVariant)
		return E_OUTOFMEMORY;

	// Copy objects
	for (size_t c = 0; c < m_size; c++)
	{
		hr = pEnumVariant->Add(Get(c));
		if (FAILED(hr))
		{
			delete pEnumVariant;
			return hr;
		}
	}

	*ppenum = pEnumVariant;
	pEnumVariant->AddRef();

	return S_OK;
}

HRESULT EnumVariant::Add(const VARIANT &vt)
{
	HRESULT hr;

	// Check index
	if (m_wpos >= m_size)
	{
		hr = Grow();
		if (FAILED(hr))
			return hr;
	}

	VariantBlockType *a;

	a = m_objects[m_wpos / VariantBlockSize];
	hr = VariantCopy(&a->at(m_wpos % VariantBlockSize), &vt);
	if (FAILED(hr))
		return hr;

	m_wpos++;

	return S_OK;
}

HRESULT EnumVariant::Grow()
{
	std::array<VARIANT, VariantBlockSize> *a;

	// Allocate new block
	a = new std::array<VARIANT, VariantBlockSize>;
	if (!a)
		return E_OUTOFMEMORY;

	// Init new block
	for (size_t c = 0; c < VariantBlockSize; c++)
		VariantInit(&a->at(c));

	// Store block and grow
	m_objects.push_back(a);
	m_size += VariantBlockSize;

	return S_OK;
}

VARIANT& EnumVariant::Get(size_t index)
{
	VariantBlockType *a;

	a = m_objects.at(index / VariantBlockSize);

	return a->at(index % VariantBlockSize);
}




