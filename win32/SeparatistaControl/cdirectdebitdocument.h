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

// {D5E53F81-A97F-4303-9353-1EB1A5BB9EC3}
DEFINE_GUID(IID_ICashAccount,
	0xd5e53f81, 0xa97f, 0x4303, 0x93, 0x53, 0x1e, 0xb1, 0xa5, 0xbb, 0x9e, 0xc3);

// {C05C2FD2-6A95-4843-B2C8-31A375DFA282}
DEFINE_GUID(CLSID_CASHACCOUNT,
	0xc05c2fd2, 0x6a95, 0x4843, 0xb2, 0xc8, 0x31, 0xa3, 0x75, 0xdf, 0xa2, 0x82);

struct ICashAccount : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	SEPARATISTA_COM_PROPERTY(BSTR, Identification, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Type, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Currency, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Name, PURE)
};

struct __declspec(uuid("{D5E53F81-A97F-4303-9353-1EB1A5BB9EC3}")) ICashAccount;

class CCashAccount : public SepaControlDispatch<ICashAccount>
{
public:
	CCashAccount(Separatista::CashAccount *pCashAccount, IUnknown *pParent = NULL);

	SEPARATISTA_COM_PROPERTY(BSTR, Identification, )
	SEPARATISTA_COM_PROPERTY(BSTR, Type, )
	SEPARATISTA_COM_PROPERTY(BSTR, Currency, )
	SEPARATISTA_COM_PROPERTY(BSTR, Name, )
private:
	Separatista::CashAccount *m_pCashAccount;
};

class __declspec(uuid("{C05C2FD2-6A95-4843-B2C8-31A375DFA282}")) CCashAccount;

// {8E012AAA-F131-4554-9161-568FF888BD7D}
DEFINE_GUID(IID_ICodeOrProprietary,
	0x8e012aaa, 0xf131, 0x4554, 0x91, 0x61, 0x56, 0x8f, 0xf8, 0x88, 0xbd, 0x7d);

// {AD7CA45E-E648-4A6C-B86F-DEF5CD56A318}
DEFINE_GUID(CLSID_CodeOrProprietary,
	0xad7ca45e, 0xe648, 0x4a6c, 0xb8, 0x6f, 0xde, 0xf5, 0xcd, 0x56, 0xa3, 0x18);

struct ICodeOrProprietary : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	SEPARATISTA_COM_PROPERTY(BSTR, Code, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, Proprietary, PURE)
};

struct __declspec(uuid("{8E012AAA-F131-4554-9161-568FF888BD7D}")) ICodeOrProprietary;

class CCodeOrProprietary : public SepaControlDispatch<ICodeOrProprietary>
{
public:
	CCodeOrProprietary(Separatista::CodeOrProprietary *pCodeOrProprietary, IUnknown *pParent = NULL);

	SEPARATISTA_COM_PROPERTY(BSTR, Code, )
	SEPARATISTA_COM_PROPERTY(BSTR, Proprietary, )
private:
	Separatista::CodeOrProprietary *m_pCodeOrProprietary;
};

class __declspec(uuid("{AD7CA45E-E648-4A6C-B86F-DEF5CD56A318}")) CCodeOrProprietary;

// {204ED0EB-F610-44A0-8709-B43212A409E6}
DEFINE_GUID(IID_PAYMENTTYPEINFORMATION,
	0x204ed0eb, 0xf610, 0x44a0, 0x87, 0x9, 0xb4, 0x32, 0x12, 0xa4, 0x9, 0xe6);

// {7AE01D5B-32E2-481E-8A23-06E18F23F556}
DEFINE_GUID(CLSID_PAYMENTTYPEINFORMATION,
	0x7ae01d5b, 0x32e2, 0x481e, 0x8a, 0x23, 0x6, 0xe1, 0x8f, 0x23, 0xf5, 0x56);

struct IPaymentTypeInformation : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// Methods
	SEPARATISTA_COM_PROPERTY(BSTR, InstructionPriority, PURE)
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, ServiceLevel, PURE)
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, LocalInstrument, PURE)
	SEPARATISTA_COM_PROPERTY(BSTR, SequenceType, PURE)
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, CategoryPurpose, PURE)
};

struct __declspec(uuid("{204ED0EB-F610-44A0-8709-B43212A409E6}")) IPaymentTypeInformation;

class CPaymentTypeInformation : public SepaControlDispatch<IPaymentTypeInformation>
{
public:
	CPaymentTypeInformation(Separatista::PaymentTypeInformation *pPaymentTypeInformation, IUnknown *pParent = NULL);

	SEPARATISTA_COM_PROPERTY(BSTR, InstructionPriority, )
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, ServiceLevel, )
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, LocalInstrument, )
	SEPARATISTA_COM_PROPERTY(BSTR, SequenceType, )
	SEPARATISTA_COM_PROPERTY_GET(ICodeOrProprietary*, CategoryPurpose, )
private:
	Separatista::PaymentTypeInformation* m_pPaymentTypeInformation;
};

class __declspec(uuid("{7AE01D5B-32E2-481E-8A23-06E18F23F556}")) CPaymentTypeInformation;

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
