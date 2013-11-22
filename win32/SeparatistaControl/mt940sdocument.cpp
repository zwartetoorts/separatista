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

#include <comutil.h>

#include "mt940srecordset.h"
#include "mt940sdocument.h"
#include "dispatch.cpp"
#include "enumvariant.h"

using namespace Separatista;

STDMETHODIMP CMT940SDocument::Open(BSTR Path, Separatista::MT940SDocument::OpenStatus *pStatus)
{
	_bstr_t path(Path);

	*pStatus = m_MT940SDocument.Open(path);

	return S_OK;
}

STDMETHODIMP CMT940SDocument::Count(long *plCount)
{
	*plCount = m_MT940SDocument.getRecordsetCount();

	return S_OK;
}

STDMETHODIMP CMT940SDocument::Item(VARIANT vIndex, IMT940SRecordset **ppIMT940SRecordset)
{
	CMT940SRecordset *pCMT940SRecordset;
	_variant_t index(vIndex);

	if((size_t)index >= m_MT940SDocument.getRecordsetCount())
		return DISP_E_BADINDEX;

	pCMT940SRecordset  = new CMT940SRecordset(this);
	if(!pCMT940SRecordset)
		return E_OUTOFMEMORY;
	
	*pCMT940SRecordset = m_MT940SDocument.getRecordset(index);

	*ppIMT940SRecordset = pCMT940SRecordset;

	return S_OK;
}

STDMETHODIMP CMT940SDocument::_NewEnum(IUnknown **ppUnk)
{
	EnumVariant *pEnumVariant;
	std::size_t index;
	MT940SRecordset *pMT940SRecordset;
	CMT940SRecordset *pCMT940SRecordset;

	// Create new EnumVariant
	pEnumVariant = new EnumVariant();
	if(!pEnumVariant)
		return E_OUTOFMEMORY;
	pEnumVariant->AddRef();

	// Enum all recordsets in this document
	for(index = 0; index < m_MT940SDocument.getRecordsetCount(); index++)
	{
		pMT940SRecordset = m_MT940SDocument.getRecordset(index);

		// Create new CMT940SRecordset
		pCMT940SRecordset = new CMT940SRecordset(this);
		if(!pCMT940SRecordset)
		{
			pEnumVariant->Release();
			return E_OUTOFMEMORY;
		}
		*pCMT940SRecordset = pMT940SRecordset;
		
		// Add CMT940SRecordset object to EnumVariant
		pCMT940SRecordset->AddRef();
		pEnumVariant->Add(pCMT940SRecordset);
	}

	// Set out
	*ppUnk = pEnumVariant;

	return S_OK;
}


