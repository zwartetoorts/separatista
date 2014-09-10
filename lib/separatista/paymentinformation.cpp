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

#include "separatista.h"
#include "paymentinformation.h"

using namespace Separatista;

SvcLvl::SvcLvl() :
BranchElement(TEXT("SvcLvl")),
m_Cd(TEXT("Cd"))
{

}

xercesc::DOMElement* SvcLvl::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

LclInstrm::LclInstrm() :
BranchElement(TEXT("LclInstrm")),
m_Cd(TEXT("Cd"))
{

}

xercesc::DOMElement* LclInstrm::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

PmtTpInf::PmtTpInf() :
BranchElement(TEXT("PmtTpInf")),
m_SvcLvl(),
m_LclInstrm(),
m_SeqTp(TEXT("SeqTp"))
{

}

xercesc::DOMElement* PmtTpInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_SvcLvl.toDOMDocument(pDocument, pElement);
		m_LclInstrm.toDOMDocument(pDocument, pElement);
		m_SeqTp.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

AccountIdentification::AccountIdentification() :
BranchElement(TEXT("Id")),
m_IBAN(TEXT("IBAN"))
{

}

xercesc::DOMElement* AccountIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_IBAN.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

CashAccount::CashAccount(const wchar_t *pTag) :
BranchElement(pTag),
m_Id()
{

}

xercesc::DOMElement* CashAccount::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

FinancialInstitutionIdentification::FinancialInstitutionIdentification() :
BranchElement(TEXT("FinInstnId")),
m_BIC(TEXT("BIC"))
{

}

xercesc::DOMElement* FinancialInstitutionIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_BIC.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

BranchAndFinancialInstitutionIdentification::BranchAndFinancialInstitutionIdentification(const wchar_t *pTag) :
BranchElement(pTag),
m_FinancialInstitutionIdentification()
{

}

xercesc::DOMElement* BranchAndFinancialInstitutionIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_FinancialInstitutionIdentification.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PersonIdentificationSchemeName::PersonIdentificationSchemeName(const wchar_t *pTag) :
BranchElement(pTag),
m_Prtry(TEXT("Prtry"))
{

}

xercesc::DOMElement* PersonIdentificationSchemeName::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Prtry.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

GenericPersonIdentification::GenericPersonIdentification(const wchar_t *pTag) :
BranchElement(pTag),
m_Id(TEXT("Id")),
m_SchmeNm(TEXT("SchmeNm"))
{

}

xercesc::DOMElement* GenericPersonIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement);
		m_SchmeNm.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PersonIdentification::PersonIdentification(const wchar_t *pTag) :
BranchElement(pTag),
m_Othr(TEXT("Othr"))
{

}

xercesc::DOMElement* PersonIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Othr.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PartyChoice::PartyChoice() :
BranchElement(TEXT("Id")),
m_PrvtId(TEXT("PrvtId"))
{

}

xercesc::DOMElement* PartyChoice::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_PrvtId.toDOMDocument(pDocument, pElement);

	return pElement;
}

PartyIdentification::PartyIdentification(const wchar_t *pTag) :
BranchElement(pTag),
m_Nm(TEXT("Nm")),
m_Id()
{

}

xercesc::DOMElement* PartyIdentification::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		if (!m_Nm.isEmpty())
			m_Nm.toDOMDocument(pDocument, pElement);
		else
			m_Id.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

PmtInf::PmtInf() :
BranchElement(TEXT("PmtInf")),
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
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

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
