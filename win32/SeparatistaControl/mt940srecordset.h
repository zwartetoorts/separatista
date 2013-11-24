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

#ifndef SEPARATISTA_MT940SRECORDSET_H
#define SEPARATISTA_MT940SRECORDSET_H

#include <windows.h>
#include <oleauto.h>

#include "mt940s/mt940s.h"
#include "dispatch.h"
#include "mt940sdocument.h"
#include "ciban.h"

// {B61526D3-1B0E-42c0-A276-C0F1DAA94CC8}
DEFINE_GUID(IID_IMT940SRecordset, 
0xb61526d3, 0x1b0e, 0x42c0, 0xa2, 0x76, 0xc0, 0xf1, 0xda, 0xa9, 0x4c, 0xc8);

// {343F637E-DA0B-43a4-A802-8F9EF2DCC5DF}
DEFINE_GUID(CLSID_CMT940SRecordset, 
0x343f637e, 0xda0b, 0x43a4, 0xa8, 0x2, 0x8f, 0x9e, 0xf2, 0xdc, 0xc5, 0xdf);

struct IMT940SRecordset : public IDispatch
{
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;
	
	// Methods
	STDMETHOD(CurrencyClient)(BSTR *pCurrencyClient) PURE;
	STDMETHOD(TransactionReference)(BSTR *pTransactionReference) PURE;
	STDMETHOD(SerialNumber)(BSTR *pSerialNumber) PURE;
	STDMETHOD(IBANClient)(CIBAN **ppIBANClient) PURE;
	STDMETHOD(PreviousBalance)(VARIANT *pPreviousBalance) PURE;
	STDMETHOD(PreviousBalanceDate)(DATE *pPreviousBalanceDate) PURE;
	STDMETHOD(CurrentBalance)(VARIANT *pCurrentBalance) PURE;
	STDMETHOD(CurrentBalanceDate)(DATE *pCurrentBalanceDate) PURE;
	STDMETHOD(MoveFirst)() PURE;
	STDMETHOD(MoveNext)() PURE;
	STDMETHOD(FEOF)(int *pEOF) PURE;
};

struct __declspec(uuid("{B61526D3-1B0E-42c0-A276-C0F1DAA94CC8}")) IMT940SRecordset;

/**
	COM representation of a MT940SRecordset. 
	Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released. 
	Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child 
	objects in the parent CMT940SDocument. 
*/
class CMT940SRecordset : public SepaControlDispatch<IMT940SRecordset>
{
public:
	/**
		@see SepaControllDispatch
	*/
	CMT940SRecordset(IDispatch *pParent);

	/**
		Assignment operator, will set the internal pointer to the recordset
	*/
	CMT940SRecordset& operator = (Separatista::MT940SRecordset *pMT940SRecordset);

  	// COM Methods
	STDMETHOD(CurrencyClient)(BSTR *pCurrencyClient);
	STDMETHOD(TransactionReference)(BSTR *pTransactionReference);
	STDMETHOD(SerialNumber)(BSTR *pSerialNumber);
	STDMETHOD(IBANClient)(CIBAN **ppIBANClient);
	STDMETHOD(PreviousBalance)(VARIANT *pPreviousBalance);
	STDMETHOD(PreviousBalanceDate)(DATE *pPreviousBalanceDate);
	STDMETHOD(CurrentBalance)(VARIANT *pCurrentBalance);
	STDMETHOD(CurrentBalanceDate)(DATE *pCurrentBalanceDate);
	STDMETHOD(MoveFirst)();
	STDMETHOD(MoveNext)();
	STDMETHOD(FEOF)(int *pEOF);

protected:
	/**
		Converts a string to a currency variant.
	*/
	static HRESULT VariantTypeFromCurrency(const char *pCurrency, VARIANT *pvCurrency);

	/**
		Converts a time_t to a DATE.
	*/
	static HRESULT DateTypeFromStdTime(time_t t, DATE *pDate);

private:
	/// Pointer to the MT940SRecordset it represents
	Separatista::MT940SRecordset *m_pMT940SRecordset;

	Separatista::MT940SRecordset::TransactionIterator m_transactionIterator;


};

class __declspec(uuid("{343F637E-DA0B-43a4-A802-8F9EF2DCC5DF}")) CMT940SRecordset;

#endif // ifndef SEPARATISTA_MT940SRECORDSET_H