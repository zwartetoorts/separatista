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
#include "dispatch.cpp"

CMT940SRecordset::CMT940SRecordset(IDispatch *pParent)
:SepaControlDispatch<IMT940SRecordset>(pParent)
{
	m_pMT940SRecordset = NULL;
}

CMT940SRecordset& CMT940SRecordset::operator = (Separatista::MT940SRecordset *pMT940SRecordset)
{
	m_pMT940SRecordset = pMT940SRecordset;

	return *this;
}

STDMETHODIMP CMT940SRecordset::CurrencyClient(BSTR *pCurrencyClient)
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	*pCurrencyClient = _bstr_t(m_pMT940SRecordset->getCurrencyClient());

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::TransactionReference(BSTR *pTransactionReference)
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	*pTransactionReference = _bstr_t(m_pMT940SRecordset->getTransactionReference());

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::SerialNumber(BSTR *pSerialNumber)
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	*pSerialNumber = _bstr_t(m_pMT940SRecordset->getSerialNumber());

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::IBANClient(CIBAN **ppIBANClient)
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	*ppIBANClient = new CIBAN();
	if(!*ppIBANClient)
		return E_OUTOFMEMORY;

	(*ppIBANClient)->AddRef();

	(**ppIBANClient) = (Separatista::IBAN*)m_pMT940SRecordset->getIBANClient();

	return S_OK;
}


