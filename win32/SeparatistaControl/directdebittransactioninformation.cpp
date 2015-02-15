/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
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
#include <comdef.h>

#include "directdebittransactioninformation.h"
#include "dispatch.cpp"
#include "util.h"
#include "supporterrorinfo.h"

DirectDebitTransactionInformation::DirectDebitTransactionInformation(IUnknown *pParent) :
SepaControlDispatch<IDirectDebitTransactionInformation>(pParent)
{
	m_pDrctDbtTxInf = new Separatista::pain_008_001::DrctDbtTxInf();
	m_bOwnDrctDbtTxInf = true;
}

DirectDebitTransactionInformation::~DirectDebitTransactionInformation()
{
	if (m_bOwnDrctDbtTxInf)
		delete m_pDrctDbtTxInf;
}

STDMETHODIMP DirectDebitTransactionInformation::QueryInterface(REFIID riid, void** ppvObject)
{
	SepaControlSupportErrorInfo *pSupportErrorInfo;

	if (IsEqualIID(riid, IID_ISupportErrorInfo))
	{
		pSupportErrorInfo = new SepaControlSupportErrorInfo();
		if (!pSupportErrorInfo)
			return E_OUTOFMEMORY;
		pSupportErrorInfo->AddRef();
		*ppvObject = pSupportErrorInfo;
		return S_OK;
	}
	return SepaControlDispatch<IDirectDebitTransactionInformation>::QueryInterface(riid, ppvObject);
}

void DirectDebitTransactionInformation::Detach()
{
	m_bOwnDrctDbtTxInf = false;
}

Separatista::pain_008_001::DrctDbtTxInf* DirectDebitTransactionInformation::getDrctDbtTxInf() const
{
	return m_pDrctDbtTxInf;
}

STDMETHODIMP DirectDebitTransactionInformation::GetPaymentIdentificationEndToEndId(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pDrctDbtTxInf->m_PmtId.m_EndToEndId.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetPaymentIdentificationEndToEndId(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_PmtId.m_EndToEndId.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetInstructedAmount(VARIANT *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _variant_t(m_pDrctDbtTxInf->m_InstdAmt.getDoubleValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetInstructedAmount(VARIANT Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_InstdAmt.setValue((double)_variant_t(Value));
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetMandateIdentification(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pDrctDbtTxInf->m_DrctDbtTx.m_MndtRltdInf.m_MndtId.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetMandateIdentification(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_DrctDbtTx.m_MndtRltdInf.m_MndtId.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetDateOfSignature(DATE *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	return DateTypeFromStdTime(m_pDrctDbtTxInf->m_DrctDbtTx.m_MndtRltdInf.m_DtOfSgntr.getDateValue(), pValue);
}

STDMETHODIMP DirectDebitTransactionInformation::SetDateOfSignature(DATE Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_DrctDbtTx.m_MndtRltdInf.m_DtOfSgntr.setValue(StdTimeFromDateType(Value));
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetDebtorAgentFinancialInstitutionIdentificationBIC(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pDrctDbtTxInf->m_DbtrAgt.m_FinancialInstitutionIdentification.m_BIC.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetDebtorAgentFinancialInstitutionIdentificationBIC(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_DbtrAgt.m_FinancialInstitutionIdentification.m_BIC.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetDebtorName(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pDrctDbtTxInf->m_Dbtr.m_Nm.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetDebtorName(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_Dbtr.m_Nm.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetDebtorAccountIBAN(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;
	
	*pValue = _bstr_t(m_pDrctDbtTxInf->m_DbtrAcct.m_Id.m_IBAN.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetDebtorAccountIBAN(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_DbtrAcct.m_Id.choose(&m_pDrctDbtTxInf->m_DbtrAcct.m_Id.m_IBAN);
		m_pDrctDbtTxInf->m_DbtrAcct.m_Id.m_IBAN.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &ive)
	{
		return SetErrorInfo(ive);
	}
	catch (const Separatista::InvalidChoiceException &e)
	{
		return SetErrorInfo(e);
	}


	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::GetRemittanceInformationUnstructured(BSTR *pValue)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pDrctDbtTxInf->m_RmtInf.m_Ustrd.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP DirectDebitTransactionInformation::SetRemittanceInformationUnstructured(BSTR Value)
{
	if (!m_pDrctDbtTxInf)
		return E_UNEXPECTED;

	try
	{
		m_pDrctDbtTxInf->m_RmtInf.m_Ustrd.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}
