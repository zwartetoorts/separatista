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
#include <separatista/separatista.h>
#include <separatista/pain/directdebittransactioninformation.h>
#include "separatista/debug/debug.h"

#include "dispatch.h"

#ifndef SEPARATISTA_CONTROL_DIRECTDEBITTRANSACTIONINFORMATION_H
#define SEPARATISTA_CONTROL_DIRECTDEBITTRANSACTIONINFORMATION_H

// {C660CA93-13FB-40B5-B66A-818616D1BD55}
DEFINE_GUID(IID_IDirectDebitTransactionInformation ,
	0xc660ca93, 0x13fb, 0x40b5, 0xb6, 0x6a, 0x81, 0x86, 0x16, 0xd1, 0xbd, 0x55);

// {34F53824-3D5A-49A2-8F94-A721ED35E01D}
DEFINE_GUID(CLSID_DirectDebitTransactionInformation,
	0x34f53824, 0x3d5a, 0x49a2, 0x8f, 0x94, 0xa7, 0x21, 0xed, 0x35, 0xe0, 0x1d);

struct IDirectDebitTransactionInformation : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IDirectDebitTransactionInformation
	STDMETHOD(GetPaymentIdentificationEndToEndId)(BSTR *pValue) PURE;
	STDMETHOD(SetPaymentIdentificationEndToEndId)(BSTR Value) PURE;
	STDMETHOD(GetInstructedAmount)(VARIANT *pValue) PURE;
	STDMETHOD(SetInstructedAmount)(VARIANT Value) PURE;
	STDMETHOD(GetMandateIdentification)(BSTR *pValue) PURE;
	STDMETHOD(SetMandateIdentification)(BSTR Value) PURE;
	STDMETHOD(GetDateOfSignature)(DATE *pValue) PURE;
	STDMETHOD(SetDateOfSignature)(DATE Value) PURE;
	STDMETHOD(GetDebtorAgentFinancialInstitutionIdentificationBIC)(BSTR *pValue) PURE;
	STDMETHOD(SetDebtorAgentFinancialInstitutionIdentificationBIC)(BSTR Value) PURE;
	STDMETHOD(GetDebtorName)(BSTR *pValue) PURE;
	STDMETHOD(SetDebtorName)(BSTR Value) PURE;
	STDMETHOD(GetDebtorAccountIBAN)(BSTR *pValue) PURE;
	STDMETHOD(SetDebtorAccountIBAN)(BSTR Value) PURE;
	STDMETHOD(GetRemittanceInformationUnstructured)(BSTR *pValue) PURE;
	STDMETHOD(SetRemittanceInformationUnstructured)(BSTR Value) PURE;
};

struct __declspec(uuid("{C660CA93-13FB-40B5-B66A-818616D1BD55}")) IDirectDebitTransactionInformation;

class DirectDebitTransactionInformation : public SepaControlDispatch<IDirectDebitTransactionInformation>
{
public:
	/**
	@see SepaControllDispatch
	*/
	DirectDebitTransactionInformation(IUnknown *pParent = NULL);

	/**
	If this object owns the underlaying Separatista object, it will be detached from the object. If this
	com class is destroyed, the underlaying Separatista object won't be destroyed.
	*/
	void Detach();

	Separatista::pain_008_001::DrctDbtTxInf* getDrctDbtTxInf() const;

	// COM Methods
	// Subclass for ISupportErrorInfo
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject);

	STDMETHOD(GetPaymentIdentificationEndToEndId)(BSTR *pValue);
	STDMETHOD(SetPaymentIdentificationEndToEndId)(BSTR Value);
	STDMETHOD(GetInstructedAmount)(VARIANT *pValue);
	STDMETHOD(SetInstructedAmount)(VARIANT Value);
	STDMETHOD(GetMandateIdentification)(BSTR *pValue);
	STDMETHOD(SetMandateIdentification)(BSTR Value);
	STDMETHOD(GetDateOfSignature)(DATE *pValue);
	STDMETHOD(SetDateOfSignature)(DATE Value);
	STDMETHOD(GetDebtorAgentFinancialInstitutionIdentificationBIC)(BSTR *pValue);
	STDMETHOD(SetDebtorAgentFinancialInstitutionIdentificationBIC)(BSTR Value);
	STDMETHOD(GetDebtorName)(BSTR *pValue);
	STDMETHOD(SetDebtorName)(BSTR Value);
	STDMETHOD(GetDebtorAccountIBAN)(BSTR *pValue);
	STDMETHOD(SetDebtorAccountIBAN)(BSTR Value);
	STDMETHOD(GetRemittanceInformationUnstructured)(BSTR *pValue);
	STDMETHOD(SetRemittanceInformationUnstructured)(BSTR Value);
protected:
	~DirectDebitTransactionInformation();

private:
	Separatista::pain_008_001::DrctDbtTxInf *m_pDrctDbtTxInf;
	bool m_bOwnDrctDbtTxInf;

};

class __declspec(uuid("{34F53824-3D5A-49A2-8F94-A721ED35E01D}")) DirectDebitTransactionInformation;


#endif // SEPARATISTA_CONTROL_DIRECTDEBITTRANSACTIONINFORMATION_H