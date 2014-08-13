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

SvcLvl::SvcLvl() :
Element(TEXT("SvcLvl")),
m_Cd(TEXT("Cd"))
{

}

xercesc::DOMElement* SvcLvl::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pParent);

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
		m_Cd.toDOMDocument(pDocument, pParent);

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

CashAccount::CashAccount(const wchar_t *pTag) :
Element(pTag),
m_Id(TEXT("Id"))
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
		m_BIC.toDOMDocument(pDocument, pParent);
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

PartyIdentification::PartyIdentification(const wchar_t *pTag) :
Element(pTag),
m_Nm(TEXT("Nm")),
m_PrvtId(TEXT("PrvtId"))
{

}

xercesc::DOMElement* PartyIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_Nm.toDOMDocument(pDocument, pElement);
		m_PrvtId.toDOMDocument(pDocument, pElement);
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
m_CdtrAgt(TEXT("CdtrAft")),
m_ChrgBr(TEXT("ChrgBr")),
m_CdtrSchmeId(TEXT("CdtrSchmeId"))
{
	
}

xercesc::DOMElement* PmtInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
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
	}

	return pElement;
}

void PmtInf::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{

}

PaymentInformation::PaymentInformation()
{
	m_pPmtInf = new PmtInf();
	if (m_pPmtInf)
	{
		// Set some default values
		m_pPmtInf->m_NbOfTxs.setValue(0);
		m_pPmtInf->m_CtrlSum.setValue(0.0);
		m_pPmtInf->m_PmtTpInf.m_SvcLvl.m_Cd.setValue(TEXT("SEPA"));
		m_pPmtInf->m_CdtrSchmeId.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.setValue(TEXT("SEPA"));
		m_pPmtInf->m_ChrgBr.setValue(TEXT("SLEV"));
	}
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

	m_pPmtInf->setValue(Value);

	return S_OK;
}

