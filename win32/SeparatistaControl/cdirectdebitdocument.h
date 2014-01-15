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
	STDMETHOD(getName)(BSTR *pName) PURE;
	STDMETHOD(setName)(BSTR Name) PURE;
	STDMETHOD(getPostalAddress)(BSTR *pPostalAddress) PURE;
	STDMETHOD(setPostalAddress)(BSTR PostalAddress) PURE;
	STDMETHOD(getIdentification)(BSTR *pIdentification) PURE;
	STDMETHOD(setIdentification)(BSTR Identification) PURE;
	STDMETHOD(getCountryOfResidence)(BSTR *pCountryOfResidence) PURE;
	STDMETHOD(setCountryOfResidence)(BSTR CountryOfResidence) PURE;
	STDMETHOD(getContactDetails)(BSTR *pContactDetails) PURE;
	STDMETHOD(setContactDetails)(BSTR ContactDetails) PURE;
};

struct __declspec(uuid("{6A5542FA-C264-4AC0-B82B-7B54AB2FB3CF}")) IPartyIdentification;

class CPartyIdentification : public SepaControlDispatch<IPartyIdentification>
{
public:
	CPartyIdentification(Separatista::PartyIdentification* pPartyIdentification, IUnknown *pParent = NULL);

	STDMETHOD(getName)(BSTR *pName);
	STDMETHOD(setName)(BSTR Name);
	STDMETHOD(getPostalAddress)(BSTR *pPostalAddress);
	STDMETHOD(setPostalAddress)(BSTR PostalAddress);
	STDMETHOD(getIdentification)(BSTR *pIdentification);
	STDMETHOD(setIdentification)(BSTR Identification);
	STDMETHOD(getCountryOfResidence)(BSTR *pCountryOfResidence);
	STDMETHOD(setCountryOfResidence)(BSTR CountryOfResidence);
	STDMETHOD(getContactDetails)(BSTR *pContactDetails);
	STDMETHOD(setContactDetails)(BSTR ContactDetails);
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
	STDMETHOD(getMessageIdentification)(BSTR *pMessageIdentification) PURE;
	STDMETHOD(setMessageIdentification)(BSTR messageIdentification) PURE;
	STDMETHOD(getCreationDateTime)(DATE *pCreationDateTime) PURE;
	STDMETHOD(setCreationDateTime)(DATE creationDate) PURE;
	STDMETHOD(getAuthorisation1)(BSTR *pAuthorisation1) PURE;
	STDMETHOD(setAuthorisation1)(BSTR Authorisation1) PURE;
	STDMETHOD(getAuthorisation2)(BSTR *pAuthorisation2) PURE;
	STDMETHOD(setAuthorisation2)(BSTR Authorisation2) PURE;
	STDMETHOD(getNumberOfTransactions)(VARIANT *pNumberOfTransactions) PURE;
	STDMETHOD(getControlSum)(VARIANT *pControlSum) PURE;
	STDMETHOD(getForwardingAgent)(BSTR *pForwardingAgent) PURE;
	STDMETHOD(setForwardingAgent)(BSTR ForwardingAgent) PURE;
	STDMETHOD(getInitiatingParty)(IPartyIdentification **ppPartyIdentification) PURE;
	STDMETHOD(FEOF)(VARIANT_BOOL *pFEOF) PURE;
	STDMETHOD(moveFirst)() PURE;
	STDMETHOD(moveNext)() PURE;

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
	STDMETHOD(getAuthorisation1)(BSTR *pAuthorisation1);
	STDMETHOD(setAuthorisation1)(BSTR Authorisation1);
	STDMETHOD(getAuthorisation2)(BSTR *pAuthorisation2);
	STDMETHOD(setAuthorisation2)(BSTR Authorisation2);
	STDMETHOD(getNumberOfTransactions)(VARIANT *pNumberOfTransactions);
	STDMETHOD(getControlSum)(VARIANT *pControlSum);
	STDMETHOD(getForwardingAgent)(BSTR *pForwardingAgent);
	STDMETHOD(setForwardingAgent)(BSTR ForwardingAgent);
	STDMETHOD(getInitiatingParty)(IPartyIdentification **ppPartyIdentification);
	STDMETHOD(FEOF)(VARIANT_BOOL *pFEOF);
	STDMETHOD(moveFirst)();
	STDMETHOD(moveNext)();
private:
	Separatista::DirectDebitDocument *m_pDocument;
};

class __declspec(uuid("{0274813F-6EF4-44DF-8A1C-38262379519F}")) CDirectDebitDocument;



#endif // SEPARATISTA_CDIRECTDEBITDOCUMENT_H
