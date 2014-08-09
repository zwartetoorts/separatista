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
#include <xercesc/dom/DOMDocument.hpp>

#include "dispatch.h"
#include "element.h"
#include "customerdirectdebitinitiation.h"

#ifndef SEPARATISTA_CONTROL_PAYMENTINFORMATION_H
#define SEPARATISTA_CONTROL_PAYMENTINFORMATION_H

class SvcLvl : public Element
{
public:
	SvcLvl(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_Cd;
};

class LclInstrm : public Element
{
public:
	LclInstrm(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_cd;
};

class PmtTpInf : public Element
{
public:
	PmtTpInf(xercesc::DOMDocument *pDocument, Element *pParent);

	SvcLvl m_SvcLvl;
	LclInstrm m_LclInstrm;
	Element m_SeqTp;
};

class CashAccount : public Element
{
public:
	CashAccount(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	Element m_Id;
};

class FinancialInstitutionIdentification : public Element
{
public:
	FinancialInstitutionIdentification(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_BIC;
};

class BranchAndFinancialInstitutionIdentification : public Element
{
public:
	BranchAndFinancialInstitutionIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	FinancialInstitutionIdentification m_FinancialInstitutionIdentification;
};

class PersonIdentificationSchemeName : public Element
{
public:
	PersonIdentificationSchemeName::PersonIdentificationSchemeName(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	Element m_Prtry;
};

class GenericPersonIdentification : public Element
{
public:
	GenericPersonIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	Element m_Id;
	PersonIdentificationSchemeName m_SchmeNm;
};

class PersonIdentification : public Element
{
public:
	PersonIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	GenericPersonIdentification m_Othr;
};

class PartyIdentification : public Element
{
public:
	PartyIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag);

	Element m_Nm;
	PersonIdentification m_PrvtId;
};


class PmtInf : public Element
{
public:
	PmtInf(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_PmtInfId;
	Element m_PmtMtd;
	Element m_NbOfTxs;
	Element m_CtrlSum;
	PmtTpInf m_PmtTpInf;
	Element m_ReqdColltnDt;
	PartyIdentification m_Cdtr;
	CashAccount m_CdtrAcct;
	BranchAndFinancialInstitutionIdentification m_CdtrAgt;
	Element m_ChrgBr;
	PartyIdentification m_CdtrSchmeId;
};

// {9D52C4C2-B5FF-43E0-9FAC-600AF2986686}
DEFINE_GUID(IID_IPaymentInformation ,
	0x9d52c4c2, 0xb5ff, 0x43e0, 0x9f, 0xac, 0x60, 0xa, 0xf2, 0x98, 0x66, 0x86);

// {CBDAC56C-5A90-443F-9511-D3F3B5AC3CF7}
DEFINE_GUID(CLSID_PAYMENTINFORMATION,
	0xcbdac56c, 0x5a90, 0x443f, 0x95, 0x11, 0xd3, 0xf3, 0xb5, 0xac, 0x3c, 0xf7);

struct IPaymentInformation : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IPaymentInformation
	STDMETHOD(GetPaymentInformationIdentification)(BSTR *pValue) PURE;
	STDMETHOD(SetPaymentInformationIdentification)(BSTR Value) PURE;
	
};

struct __declspec(uuid("{9D52C4C2-B5FF-43E0-9FAC-600AF2986686}")) IPaymentInformation;

/**
	COM representation of an IBAN class.
	Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released.
	Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child
	objects in the parent CMT940SDocument.
*/
class PaymentInformation : public SepaControlDispatch<IPaymentInformation>
{
public:
	/**
	@see SepaControllDispatch
	*/
	PaymentInformation(CustomerDirectDebitInitiation *pParent, xercesc::DOMDocument *pDomDocument);

private:
	xercesc::DOMDocument *m_pDomDocument;
};

class __declspec(uuid("{CBDAC56C-5A90-443F-9511-D3F3B5AC3CF7}")) PaymentInformation;

#endif // SEPARATISTA_CONTROL_PAYMENTINFORMATION_H
