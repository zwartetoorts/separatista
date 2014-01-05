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

#include "windows.h"

#include "separatista.h"
#include "dispatch.h"

#ifndef SEPARATISTA_CDIRECTDEBITDOCUMENT_H
#define SEPARATISTA_CDIRECTDEBITDOCUMENT_H

// {79F9F451-460D-445C-B176-A0F64C347D1D}
DEFINE_GUID(IID_DIRECTDEBITDOCUMENT ,
	0x79f9f451, 0x460d, 0x445c, 0xb1, 0x76, 0xa0, 0xf6, 0x4c, 0x34, 0x7d, 0x1d);

// {0274813F-6EF4-44DF-8A1C-38262379519F}
DEFINE_GUID(CLSID_DIRECTDEBITDOCUMENT,
	0x274813f, 0x6ef4, 0x44df, 0x8a, 0x1c, 0x38, 0x26, 0x23, 0x79, 0x51, 0x9f);

struct IDirectDebitDocument : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// COM methods
	STDMETHOD(getMessageIdentification)(BSTR *pMessageIdentification) PURE;
	STDMETHOD(setMessageIdentification)(BSTR messageIdentification) PURE;
	STDMETHOD(getCreationDateTime)(DATE *pCreationDateTime) PURE;
	STDMETHOD(setCreationDateTime)(DATE creationDate) PURE;
	STDMETHOD(getNumberOfTransactions)(VARIANT *pNumberOfTransactions) PURE;
	STDMETHOD(getControlSum)(VARIANT *pControlSum) PURE;
};

struct __declspec(uuid("{79F9F451-460D-445C-B176-A0F64C347D1D}")) IDirectDebitDocument;

/**
COM representation of an DirectDebitDocument class.
Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released.
Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child
objects in the parent CMT940SDocument.
*/
class CDirectDebitDocument : public SepaControlDispatch<IDirectDebitDocument>
{
public:
	/**
	@see SepaControllDispatch
	*/
	CDirectDebitDocument(IUnknown *pParent = NULL);

	CDirectDebitDocument(Separatista::DirectDebitDocument *pDocument, IUnknown *pParent = NULL);

	CDirectDebitDocument& operator =(Separatista::DirectDebitDocument *pDocument);

	// COM methods
	STDMETHOD(getMessageIdentification)(BSTR *pMessageIdentification);
	STDMETHOD(setMessageIdentification)(BSTR messageIdentification);
	STDMETHOD(getCreationDateTime)(DATE *pCreationDateTime);
	STDMETHOD(setCreationDateTime)(DATE creationDate);
	STDMETHOD(getNumberOfTransactions)(VARIANT *pNumberOfTransactions);
	STDMETHOD(getControlSum)(VARIANT *pControlSum);
private:
	Separatista::DirectDebitDocument *m_pDocument;
};

class __declspec(uuid("{0274813F-6EF4-44DF-8A1C-38262379519F}")) CDirectDebitDocument;



#endif // SEPARATISTA_CDIRECTDEBITDOCUMENT_H
