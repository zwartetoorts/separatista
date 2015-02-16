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

#include "paymentinformation.h"
#include "dispatch.cpp"
#include "util.h"
#include "supporterrorinfo.h"

PaymentInformation::PaymentInformation(IUnknown *pParent) :
SepaControlDispatch<IPaymentInformation>(pParent)
{
	m_pPmtInf = new Separatista::pain_008_001::PmtInf();
	m_bOwnPmtInf = true;
}

PaymentInformation::PaymentInformation(Separatista::pain_008_001::PmtInf *pPmtInf, IUnknown *pParent) :
SepaControlDispatch<IPaymentInformation>(pParent)
{
	m_pPmtInf = pPmtInf;
	m_bOwnPmtInf = false;
}

PaymentInformation::~PaymentInformation()
{
	if (m_bOwnPmtInf)
		delete m_pPmtInf;
}

void PaymentInformation::Detach()
{
	m_bOwnPmtInf = false;
}

STDMETHODIMP PaymentInformation::QueryInterface(REFIID riid, void** ppvObject)
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
	return SepaControlDispatch<IPaymentInformation>::QueryInterface(riid, ppvObject);
}

Separatista::pain_008_001::PmtInf* PaymentInformation::GetPmtInf() const
{
	return m_pPmtInf;
}

STDMETHODIMP PaymentInformation::GetPaymentInformationIdentification(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_PmtInfId.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP PaymentInformation::SetPaymentInformationIdentification(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_PmtInfId.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}
	
	return S_OK;
}

STDMETHODIMP PaymentInformation::GetPaymentMethod(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_PmtMtd.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetPaymentMethod(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_PmtMtd.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetNumberOfTransactions(INT *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = m_pPmtInf->m_NbOfTxs.getIntValue();

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetControlSum(VARIANT *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _variant_t(m_pPmtInf->m_CtrlSum.getDoubleValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetPaymentTypeInformationServiceLevelCode(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_PmtTpInf.m_SvcLvl.m_Cd.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetPaymentTypeInformationServiceLevelCode(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_PmtTpInf.m_SvcLvl.m_Cd.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetPaymentTypeInformationLocalIntrumentCode(IPaymentInformation::ExternalLocalInstrumentCode *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	const wchar_t *pCode = m_pPmtInf->m_PmtTpInf.m_LclInstrm.m_Cd.getTextValue();
	if (std::wcscmp(pCode, TEXT("CORE")) == 0)
		*pValue = IPaymentInformation::LC_CORE;
	else if (std::wcscmp(pCode, TEXT("COR1")) == 0)
		*pValue = IPaymentInformation::LC_COR1;
	else if (std::wcscmp(pCode, TEXT("B2B")) == 0)
		*pValue = IPaymentInformation::LC_B2B;
	else
		*pValue = IPaymentInformation::LC_UNKNOWN;

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetPaymentTypeInformationLocalIntrumentCode(IPaymentInformation::ExternalLocalInstrumentCode Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		switch (Value)
		{
		case IPaymentInformation::LC_CORE:
			m_pPmtInf->m_PmtTpInf.m_LclInstrm.m_Cd.setValue(TEXT("CORE"));
			break;
		case IPaymentInformation::LC_COR1:
			m_pPmtInf->m_PmtTpInf.m_LclInstrm.m_Cd.setValue(TEXT("COR1"));
			break;
		case IPaymentInformation::LC_B2B:
			m_pPmtInf->m_PmtTpInf.m_LclInstrm.m_Cd.setValue(TEXT("B2B"));
			break;
		default:
			m_pPmtInf->m_PmtTpInf.m_LclInstrm.m_Cd.clear();
		}
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetPaymentTypeInformationSequenceType(IPaymentInformation::SequenceTypeCode* pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	const wchar_t *pCode = m_pPmtInf->m_PmtTpInf.m_SeqTp.getTextValue();
	if (std::wcscmp(pCode, TEXT("FNAL")) == 0)
		*pValue = IPaymentInformation::ST_FNAL;
	else if (std::wcscmp(pCode, TEXT("FRST")) == 0)
		*pValue = IPaymentInformation::ST_FRST;
	else if (std::wcscmp(pCode, TEXT("OOFF")) == 0)
		*pValue = IPaymentInformation::ST_OOFF;
	else if (std::wcscmp(pCode, TEXT("RCUR")) == 0)
		*pValue = IPaymentInformation::ST_RCUR;
	else
		*pValue = IPaymentInformation::ST_UNKNOWN;

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetPaymentTypeInformationSequenceType(IPaymentInformation::SequenceTypeCode Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		switch (Value)
		{
		case IPaymentInformation::ST_FNAL:
			m_pPmtInf->m_PmtTpInf.m_SeqTp.setValue(TEXT("FNAL"));
			break;
		case IPaymentInformation::ST_FRST:
			m_pPmtInf->m_PmtTpInf.m_SeqTp.setValue(TEXT("FRST"));
			break;
		case IPaymentInformation::ST_OOFF:
			m_pPmtInf->m_PmtTpInf.m_SeqTp.setValue(TEXT("OOFF"));
			break;
		case IPaymentInformation::ST_RCUR:
			m_pPmtInf->m_PmtTpInf.m_SeqTp.setValue(TEXT("RCUR"));
			break;
		default:
			return E_UNEXPECTED;
		}
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetRequestedCollectionDate(DATE *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	return DateTypeFromStdTime(m_pPmtInf->m_ReqdColltnDt.getDateValue(), pValue);
}

STDMETHODIMP PaymentInformation::SetRequestedCollectionDate(DATE Value)
{
	std::time_t t;

	if (!m_pPmtInf)
		return E_UNEXPECTED;

	t = StdTimeFromDateType(Value);
	if (t == -1)
		return E_FAIL;

	try
	{
		m_pPmtInf->m_ReqdColltnDt.setValue(t);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorName(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_Cdtr.m_Nm.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorName(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_Cdtr.m_Nm.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorAccountIdentificationIBAN(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_CdtrAcct.m_Id.m_IBAN.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorAccountIdentificationIBAN(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_CdtrAcct.m_Id.choose(&m_pPmtInf->m_CdtrAcct.m_Id.m_IBAN);
		m_pPmtInf->m_CdtrAcct.m_Id.m_IBAN.setValue(Value);
	}
	catch (const Separatista::InvalidChoiceException &ce)
	{
		return SetErrorInfo(ce);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorAgentFinancialInstitutionIdentificationBIC(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_CdtrAgt.m_FinancialInstitutionIdentification.m_BICFI.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorAgentFinancialInstitutionIdentificationBIC(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_CdtrAgt.m_FinancialInstitutionIdentification.m_BICFI.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetChargeBearer(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_ChrgBr.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetChargeBearer(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_ChrgBr.setValue(Value);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorSchemeIdentification(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_Id.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorSchemeIdentification(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_CdtrSchmeId.m_Id.choose(&m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId);
		m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_Id.setValue(Value);
	}
	catch (const Separatista::InvalidChoiceException &ce)
	{
		return SetErrorInfo(ce);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorSchemeIdentificationSchemeName(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorSchemeIdentificationSchemeName(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	try
	{
		m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.choose(&m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry);
		m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.setValue(Value);
	}
	catch (const Separatista::InvalidChoiceException &ce)
	{
		return SetErrorInfo(ce);
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}

	return S_OK;
}

STDMETHODIMP PaymentInformation::AddDirectDebitTransactionInformation(DirectDebitTransactionInformation *pDirectDebitTransactionInformation)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	m_pPmtInf->AddDrctDbtTxInf(pDirectDebitTransactionInformation->getDrctDbtTxInf());
	pDirectDebitTransactionInformation->Detach();

	return S_OK;
}
