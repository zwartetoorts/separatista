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
#include "macros.h"

#ifndef SEPARATISTA_CDIRECTDEBITDOCUMENT_H
#define SEPARATISTA_CDIRECTDEBITDOCUMENT_H

// {6A5542FA-C264-4AC0-B82B-7B54AB2FB3CF}
DEFINE_GUID(IID_PARTYIDENTIFICATION ,
	0x6a5542fa, 0xc264, 0x4ac0, 0xb8, 0x2b, 0x7b, 0x54, 0xab, 0x2f, 0xb3, 0xcf);

// {2E1BDA09-1073-4C08-92E2-1ABD88DBD432}
DEFINE_GUID(CLSID_PARTYIDENTIFICATION,
	0x2e1bda09, 0x1073, 0x4c08, 0x92, 0xe2, 0x1a, 0xbd, 0x88, 0xdb, 0xd4, 0x32);

struct IPartyIdentification : public IDispatch
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
	SEPARATISTA_COM_PROPERTY(BSTR, Name, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, PostalAddress, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Identification, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, CountryOfResidence, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, ContactDetails, PURE)
};

struct __declspec(uuid("{6A5542FA-C264-4AC0-B82B-7B54AB2FB3CF}")) IPartyIdentification;

class CPartyIdentification : public SepaControlDispatch<IPartyIdentification>
{
public:
	CPartyIdentification(Separatista::PartyIdentification* pPartyIdentification, IUnknown *pParent = NULL);

	SEPARATISTA_COM_PROPERTY(BSTR, Name, )
	SEPARATISTA_COM_PROPERTY(BSTR, PostalAddress, )
	SEPARATISTA_COM_PROPERTY(BSTR, Identification, )
	SEPARATISTA_COM_PROPERTY(BSTR, CountryOfResidence, )
	SEPARATISTA_COM_PROPERTY(BSTR, ContactDetails, )
private:
	Separatista::PartyIdentification* m_pPartyIdentification;
};

class __declspec(uuid("{2E1BDA09-1073-4C08-92E2-1ABD88DBD432}")) CPartyIdentification;

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
	SEPARATISTA_COM_PROPERTY(BSTR, MessageIdentification, PURE)
	SEPARATISTA_COM_PROPERTY(DATE, CreationDateTime, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Authorisation1, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Authorisation2, PURE)
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, NumberOfTransactions, PURE)
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, ControlSum, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, ForwardingAgent, PURE)
	STDMETHOD(getInitiatingParty)(IPartyIdentification **ppPartyIdentification) PURE;
	STDMETHOD(FEOF)(VARIANT_BOOL *pFEOF) PURE;
	STDMETHOD(moveFirst)() PURE;
	STDMETHOD(moveNext)() PURE;
	STDMETHOD(getCount)(int *pCount) PURE;
	SEPARATISTA_COM_PROPERTY(BSTR, PaymentInformationIdentification, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, PaymentMethod, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, BatchBooking, PURE)
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, PaymentInformationNumberOfTransactions, PURE)
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, PaymentInformationControlSum, PURE)
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
	SEPARATISTA_COM_PROPERTY(BSTR, MessageIdentification, )
	SEPARATISTA_COM_PROPERTY(DATE, CreationDateTime, )
	SEPARATISTA_COM_PROPERTY(BSTR, Authorisation1, )
	SEPARATISTA_COM_PROPERTY(BSTR, Authorisation2, )
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, NumberOfTransactions, )
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, ControlSum, )
	SEPARATISTA_COM_PROPERTY(BSTR, ForwardingAgent, )
	STDMETHOD(getInitiatingParty)(IPartyIdentification **ppPartyIdentification);
	STDMETHOD(FEOF)(VARIANT_BOOL *pFEOF);
	STDMETHOD(moveFirst)();
	STDMETHOD(moveNext)();
	STDMETHOD(getCount)(int *pCount);
	SEPARATISTA_COM_PROPERTY(BSTR, PaymentInformationIdentification, )
	SEPARATISTA_COM_PROPERTY(BSTR, PaymentMethod, )
	SEPARATISTA_COM_PROPERTY(BSTR, BatchBooking, )
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, PaymentInformationNumberOfTransactions, )
	SEPARATISTA_COM_PROPERTY_GET(VARIANT, PaymentInformationControlSum, )

private:
	Separatista::DirectDebitDocument *m_pDocument;
};

class __declspec(uuid("{0274813F-6EF4-44DF-8A1C-38262379519F}")) CDirectDebitDocument;



#endif // SEPARATISTA_CDIRECTDEBITDOCUMENT_H
