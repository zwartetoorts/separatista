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

SvcLvl::SvcLvl(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("SvcLvl")),
m_Cd(pDocument, this, TEXT("Cd"))
{

}

LclInstrm::LclInstrm(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("LclInstrm")),
m_cd(pDocument, this, TEXT("Cd"))
{

}

PmtTpInf::PmtTpInf(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("PmtTpInf")),
m_SvcLvl(pDocument, this),
m_LclInstrm(pDocument, this),
m_SeqTp(pDocument, this, TEXT("SeqTp"))
{

}

CashAccount::CashAccount(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_Id(pDocument, this, TEXT("Id"))
{

}

FinancialInstitutionIdentification::FinancialInstitutionIdentification(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("FinInstnId")),
m_BIC(pDocument, this, TEXT("BIC"))
{

}

BranchAndFinancialInstitutionIdentification::BranchAndFinancialInstitutionIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_FinancialInstitutionIdentification(pDocument, this)
{

}

PersonIdentificationSchemeName::PersonIdentificationSchemeName(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_Prtry(pDocument, this, TEXT("Prtry"))
{

}

GenericPersonIdentification::GenericPersonIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_Id(pDocument, this, TEXT("Id")),
m_SchmeNm(pDocument, this, TEXT("SchmeNm"))
{

}

PersonIdentification::PersonIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_Othr(pDocument, pParent, TEXT("Othr"))
{

}

PartyIdentification::PartyIdentification(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pTag) :
Element(pDocument, pParent, pTag),
m_Nm(pDocument, this, TEXT("Nm")),
m_PrvtId(pDocument, this, TEXT("PrvtId"))
{

}

PmtInf::PmtInf(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("PmtInf")),
m_PmtInfId(pDocument, this, TEXT("PmtInfId")),
m_PmtMtd(pDocument, this, TEXT("PmtMtd")),
m_NbOfTxs(pDocument, this, TEXT("NbOfTxs")),
m_CtrlSum(pDocument, this, TEXT("CtrlSum")),
m_PmtTpInf(pDocument, this),
m_ReqdColltnDt(pDocument, this, TEXT("ReqdColltnDt")),
m_Cdtr(pDocument, this, TEXT("Cdtr")),
m_CdtrAcct(pDocument, this, TEXT("CdtrAcct")),
m_CdtrAgt(pDocument, this, TEXT("CdtrAft")),
m_ChrgBr(pDocument, this, TEXT("ChrgBr")),
m_CdtrSchmeId(pDocument, this, TEXT("CdtrSchmeId"))
{

}

PaymentInformation::PaymentInformation(CustomerDirectDebitInitiation *pParent, xercesc::DOMDocument *pDomDocument)
:SepaControlDispatch<IPaymentInformation>(pParent)
{
	m_pDomDocument = pDomDocument;
}
