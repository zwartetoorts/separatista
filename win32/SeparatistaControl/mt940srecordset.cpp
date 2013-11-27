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

STDMETHODIMP CMT940SRecordset::PreviousBalance(VARIANT *pPreviousBalance)
{
	_variant_t v;

	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	v.Attach(*pPreviousBalance);
	v = _bstr_t((const char*)m_pMT940SRecordset->getPreviousBalance());
	v.ChangeType(VT_CY);

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::PreviousBalanceDate(DATE *pPreviousBalanceDate)
{
	SYSTEMTIME stime;
	tm *pti;
	const Separatista::MT940SDate *pDate;
	time_t t;

	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	// Check for time set in recordset
	pDate = m_pMT940SRecordset->getPreviousBalanceDate();
	if(!pDate)
		t = time(NULL);
	else
		t = pDate->getTime();

	// Convert time_t to tm
	pti = localtime(&t);

	// Set SYSTEMTIME
	stime.wYear = pti->tm_year + 1900;
	stime.wMonth = pti->tm_mon + 1;
	stime.wDay = pti->tm_mday;
	stime.wHour = pti->tm_hour;
	stime.wMinute = pti->tm_min;
	stime.wSecond = pti->tm_sec;
	if(SystemTimeToVariantTime(&stime, pPreviousBalanceDate))
		return S_OK;

	return E_UNEXPECTED;
}

STDMETHODIMP CMT940SRecordset::CurrentBalance(VARIANT *pCurrentBalance)
{
	_variant_t v;

	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	v.Attach(*pCurrentBalance);
	v = _bstr_t((const char*)m_pMT940SRecordset->getCurrentBalance());
	v.ChangeType(VT_CY);

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::CurrentBalanceDate(DATE *pCurrentBalanceDate)
{
	SYSTEMTIME stime;
	tm *pti;
	const Separatista::MT940SDate *pDate;
	time_t t;

	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	// Check for time set in recordset
	pDate = m_pMT940SRecordset->getCurrentBalanceDate();
	if(!pDate)
		t = time(NULL);
	else
		t = pDate->getTime();

	// Convert time_t to tm
	pti = localtime(&t);

	// Set SYSTEMTIME
	stime.wYear = pti->tm_year + 1900;
	stime.wMonth = pti->tm_mon + 1;
	stime.wDay = pti->tm_mday;
	stime.wHour = pti->tm_hour;
	stime.wMinute = pti->tm_min;
	stime.wSecond = pti->tm_sec;
	if(SystemTimeToVariantTime(&stime, pCurrentBalanceDate))
		return S_OK;

	return E_UNEXPECTED;
}

STDMETHODIMP CMT940SRecordset::MoveFirst()
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	m_transactionIterator = m_pMT940SRecordset->getTransactionBegin();

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::MoveNext()
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	if(m_transactionIterator != m_pMT940SRecordset->getTransactionEnd())
		++m_transactionIterator;
	else
		return S_FALSE;

	return S_OK;
}

STDMETHODIMP CMT940SRecordset::FEOF(BOOL *pEOF)
{
	if(!m_pMT940SRecordset)
		return E_UNEXPECTED;

	if(m_transactionIterator == m_pMT940SRecordset->getTransactionEnd())
		*pEOF = true;
	else
		*pEOF = false;

	return S_OK;
}

/*
HRESULT CMT940SRecordset::VariantTypeFromCurrency(const char *pCurrency, VARIANT *pvCurrency)
{

}

HRESULT CMT940SRecordset::DateTypeFromStdTime(time_t t, DATE *pDate)
{
}
*/
