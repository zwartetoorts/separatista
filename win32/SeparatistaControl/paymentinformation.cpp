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

SvcLvl::SvcLvl() :
Element(TEXT("SvcLvl")),
m_Cd(TEXT("Cd"))
{

}

xercesc::DOMElement* SvcLvl::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

LclInstrm::LclInstrm() :
Element(TEXT("LclInstrm")),
m_Cd(TEXT("Cd"))
{

}

xercesc::DOMElement* LclInstrm::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

PmtTpInf::PmtTpInf() :
Element(TEXT("PmtTpInf")),
m_SvcLvl(),
m_LclInstrm(),
m_SeqTp(TEXT("SeqTp"))
{

}

xercesc::DOMElement* PmtTpInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_SvcLvl.toDOMDocument(pDocument, pElement);
		m_LclInstrm.toDOMDocument(pDocument, pElement);
		m_SeqTp.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

AccountIdentification::AccountIdentification() :
Element(TEXT("Id")),
m_IBAN(TEXT("IBAN"))
{

}

xercesc::DOMElement* AccountIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_IBAN.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

CashAccount::CashAccount(const wchar_t *pTag) :
Element(pTag),
m_Id()
{

}

xercesc::DOMElement* CashAccount::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

FinancialInstitutionIdentification::FinancialInstitutionIdentification() :
Element(TEXT("FinInstnId")),
m_BIC(TEXT("BIC"))
{

}

xercesc::DOMElement* FinancialInstitutionIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_BIC.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

BranchAndFinancialInstitutionIdentification::BranchAndFinancialInstitutionIdentification(const wchar_t *pTag) :
Element(pTag),
m_FinancialInstitutionIdentification()
{

}

xercesc::DOMElement* BranchAndFinancialInstitutionIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_FinancialInstitutionIdentification.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PersonIdentificationSchemeName::PersonIdentificationSchemeName(const wchar_t *pTag) :
Element(pTag),
m_Prtry(TEXT("Prtry"))
{

}

xercesc::DOMElement* PersonIdentificationSchemeName::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_Prtry.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

GenericPersonIdentification::GenericPersonIdentification(const wchar_t *pTag) :
Element(pTag),
m_Id(TEXT("Id")),
m_SchmeNm(TEXT("SchmeNm"))
{

}

xercesc::DOMElement* GenericPersonIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement);
		m_SchmeNm.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PersonIdentification::PersonIdentification(const wchar_t *pTag) :
Element(pTag),
m_Othr(TEXT("Othr"))
{

}

xercesc::DOMElement* PersonIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_Othr.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PartyChoice::PartyChoice() :
Element(TEXT("Id")),
m_PrvtId(TEXT("PrvtId"))
{

}

xercesc::DOMElement* PartyChoice::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_PrvtId.toDOMDocument(pDocument, pElement);

	return pElement;
}

PartyIdentification::PartyIdentification(const wchar_t *pTag) :
Element(pTag),
m_Nm(TEXT("Nm")),
m_Id()
{

}

xercesc::DOMElement* PartyIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		if(!m_Nm.empty())
			m_Nm.toDOMDocument(pDocument, pElement);
		else
			m_Id.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PmtInf::PmtInf() :
Element(TEXT("PmtInf")),
m_PmtInfId(TEXT("PmtInfId")),
m_PmtMtd(TEXT("PmtMtd")),
m_NbOfTxs(TEXT("NbOfTxs")),
m_CtrlSum(TEXT("CtrlSum")),
m_PmtTpInf(),
m_ReqdColltnDt(TEXT("ReqdColltnDt")),
m_Cdtr(TEXT("Cdtr")),
m_CdtrAcct(TEXT("CdtrAcct")),
m_CdtrAgt(TEXT("CdtrAgt")),
m_ChrgBr(TEXT("ChrgBr")),
m_CdtrSchmeId(TEXT("CdtrSchmeId"))
{
	// Set some default values
	m_NbOfTxs.setValue(0);
	m_CtrlSum.setValue(0.0);
	m_PmtTpInf.m_SvcLvl.m_Cd.setValue(TEXT("SEPA"));
	m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.setValue(TEXT("SEPA"));
	m_ChrgBr.setValue(TEXT("SLEV"));
}

PmtInf::~PmtInf()
{
	std::vector<DrctDbtTxInf*>::iterator it;

	for (it = m_DrctDbtTxInfs.begin(); it != m_DrctDbtTxInfs.end(); it++)
		delete (*it);
}

xercesc::DOMElement* PmtInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	std::vector<DrctDbtTxInf*>::iterator it;
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_PmtInfId.toDOMDocument(pDocument, pElement);
		m_PmtMtd.toDOMDocument(pDocument, pElement);
		m_NbOfTxs.toDOMDocument(pDocument, pElement);
		m_CtrlSum.toDOMDocument(pDocument, pElement);
		m_PmtTpInf.toDOMDocument(pDocument, pElement);
		m_ReqdColltnDt.toDOMDocument(pDocument, pElement);
		m_Cdtr.toDOMDocument(pDocument, pElement);
		m_CdtrAcct.toDOMDocument(pDocument, pElement);
		m_CdtrAgt.toDOMDocument(pDocument, pElement);
		m_ChrgBr.toDOMDocument(pDocument, pElement);
		m_CdtrSchmeId.toDOMDocument(pDocument, pElement);

		for (it = m_DrctDbtTxInfs.begin(); it != m_DrctDbtTxInfs.end(); it++)
			(*it)->toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void PmtInf::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	calcSums();
}

void PmtInf::elementDeleted(Element *pElement)
{
	calcSums();
}

void PmtInf::AddDrctDbtTxInf(DrctDbtTxInf *pDrctDbtTxInf)
{
	// Set listeners
	pDrctDbtTxInf->m_InstdAmt.setElementListener(this);
	
	m_DrctDbtTxInfs.push_back(pDrctDbtTxInf);
	calcSums();
}

void PmtInf::calcSums()
{
	std::vector<DrctDbtTxInf*>::iterator it;
	int ntx = 0;
	double sum = 0.0;

	for (it = m_DrctDbtTxInfs.begin(); it != m_DrctDbtTxInfs.end(); it++)
	{
		ntx++;
		sum += (*it)->m_InstdAmt.getDoubleValue();
	}

	m_NbOfTxs.setValue(ntx);
	m_CtrlSum.setValue(sum);
}

PaymentInformation::PaymentInformation(IUnknown *pParent) :
SepaControlDispatch<IPaymentInformation>(pParent)
{
	m_pPmtInf = new PmtInf();
	m_bOwnPmtInf = true;
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

PmtInf* PaymentInformation::GetPmtInf() const
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

	m_pPmtInf->m_PmtInfId.setValue(Value);
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

	m_pPmtInf->m_PmtMtd.setValue(Value);

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

	m_pPmtInf->m_PmtTpInf.m_SvcLvl.m_Cd.setValue(Value);

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
		m_pPmtInf->Delete();
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
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	m_pPmtInf->m_ReqdColltnDt.setValue(StdTimeFromDateType(Value));

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

	m_pPmtInf->m_Cdtr.m_Nm.setValue(Value);

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

	m_pPmtInf->m_CdtrAcct.m_Id.m_IBAN.setValue(Value);

	return S_OK;
}

STDMETHODIMP PaymentInformation::GetCreditorAgentFinancialInstitutionIdentificationBIC(BSTR *pValue)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	*pValue = _bstr_t(m_pPmtInf->m_CdtrAgt.m_FinancialInstitutionIdentification.m_BIC.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP PaymentInformation::SetCreditorAgentFinancialInstitutionIdentificationBIC(BSTR Value)
{
	if (!m_pPmtInf)
		return E_UNEXPECTED;

	m_pPmtInf->m_CdtrAgt.m_FinancialInstitutionIdentification.m_BIC.setValue(Value);

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

	m_pPmtInf->m_ChrgBr.setValue(Value);

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

	m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_Id.setValue(Value);

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

	m_pPmtInf->m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.setValue(Value);

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
