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

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>

#include "separatista/separatista.h"
#include "separatista/pain/paymentinformation.h"
#include "separatista/debug/debug.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

SvcLvl::SvcLvl() :
BranchElement(TEXT("SvcLvl")),
m_Cd(TEXT("Cd"), Validators.ExternalServiceLevel1CodeValidator)
{
	DEBUG_METHOD
}

xercesc::DOMElement* SvcLvl::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement, errorOptions);

	return pElement;
}

void SvcLvl::fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Cd.fromDOMDocument(pElementIterator, errorOptions);
	}
}

LclInstrm::LclInstrm() :
BranchElement(TEXT("LclInstrm")),
m_Cd(TEXT("Cd"), Validators.ExternalLocalInstrumentCodeValidator)
{
	DEBUG_METHOD
}

xercesc::DOMElement* LclInstrm::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement, errorOptions);

	return pElement;
}

void LclInstrm::fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Cd.fromDOMDocument(pElementIterator, errorOptions);
	}
}

PmtTpInf::PmtTpInf() :
BranchElement(TEXT("PmtTpInf")),
m_SvcLvl(),
m_LclInstrm(),
m_SeqTp(TEXT("SeqTp"), Validators.SequenceType3CodeValidator)
{
	DEBUG_METHOD
}

xercesc::DOMElement* PmtTpInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_SvcLvl.toDOMDocument(pDocument, pElement, errorOptions);
		m_LclInstrm.toDOMDocument(pDocument, pElement, errorOptions);
		m_SeqTp.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void PmtTpInf::fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_SvcLvl.fromDOMDocument(pElementIterator, errorOptions);
		m_LclInstrm.fromDOMDocument(pElementIterator, errorOptions);
		m_SeqTp.fromDOMDocument(pElementIterator, errorOptions);
	}
}

PmtInf::PmtInf() :
BranchElement(TEXT("PmtInf")),
m_PmtInfId(TEXT("PmtInfId"), Validators.Max35TextValidator),
m_PmtMtd(TEXT("PmtMtd"), Validators.PaymentMethod2CodeValidator),
m_NbOfTxs(TEXT("NbOfTxs"), Validators.Max15NumericTextValidator),
m_CtrlSum(TEXT("CtrlSum"), Validators.DecimalNumberValidator),
m_PmtTpInf(),
m_ReqdColltnDt(TEXT("ReqdColltnDt"), Validators.ISODateValidator),
m_Cdtr(TEXT("Cdtr")),
m_CdtrAcct(TEXT("CdtrAcct")),
m_CdtrAgt(TEXT("CdtrAgt")),
m_ChrgBr(TEXT("ChrgBr"), Validators.ChargeBearerType1CodeValidator),
m_CdtrSchmeId(TEXT("CdtrSchmeId"))
{
	DEBUG_METHOD
	// Set some default values
	m_NbOfTxs.setValue(0);
	m_CtrlSum.setValue(0.0);
	m_PmtTpInf.m_SvcLvl.m_Cd.setValue(TEXT("SEPA"));
	m_CdtrSchmeId.m_Id.m_PrvtId.m_Othr.m_SchmeNm.m_Prtry.setValue(TEXT("SEPA"));
	m_ChrgBr.setValue(TEXT("SLEV"));
}

PmtInf::~PmtInf()
{
	DEBUG_METHOD
	std::vector<DrctDbtTxInf*>::iterator it;

	for (it = m_DrctDbtTxInfs.begin(); it != m_DrctDbtTxInfs.end(); it++)
		delete (*it);
}

xercesc::DOMElement* PmtInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	std::vector<DrctDbtTxInf*>::iterator it;
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_PmtInfId.toDOMDocument(pDocument, pElement, errorOptions);
		m_PmtMtd.toDOMDocument(pDocument, pElement, errorOptions);
		m_NbOfTxs.toDOMDocument(pDocument, pElement, errorOptions);
		m_CtrlSum.toDOMDocument(pDocument, pElement, errorOptions);
		m_PmtTpInf.toDOMDocument(pDocument, pElement, errorOptions);
		m_ReqdColltnDt.toDOMDocument(pDocument, pElement, errorOptions);
		m_Cdtr.toDOMDocument(pDocument, pElement, errorOptions);
		m_CdtrAcct.toDOMDocument(pDocument, pElement, errorOptions);
		m_CdtrAgt.toDOMDocument(pDocument, pElement, errorOptions);
		m_ChrgBr.toDOMDocument(pDocument, pElement, errorOptions);
		m_CdtrSchmeId.toDOMDocument(pDocument, pElement, errorOptions);

		for (it = m_DrctDbtTxInfs.begin(); it != m_DrctDbtTxInfs.end(); it++)
			(*it)->toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void PmtInf::fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	unsigned int pos;
	DrctDbtTxInf *pTxInf;
	
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_PmtInfId.fromDOMDocument(pElementIterator, errorOptions);
		m_PmtMtd.fromDOMDocument(pElementIterator, errorOptions);
		m_NbOfTxs.fromDOMDocument(pElementIterator, errorOptions);
		m_CtrlSum.fromDOMDocument(pElementIterator, errorOptions);
		m_PmtTpInf.fromDOMDocument(pElementIterator, errorOptions);
		m_ReqdColltnDt.fromDOMDocument(pElementIterator, errorOptions);
		m_Cdtr.fromDOMDocument(pElementIterator, errorOptions);
		m_CdtrAcct.fromDOMDocument(pElementIterator, errorOptions);
		m_CdtrAgt.fromDOMDocument(pElementIterator, errorOptions);
		m_ChrgBr.fromDOMDocument(pElementIterator, errorOptions);
		m_CdtrSchmeId.fromDOMDocument(pElementIterator, errorOptions);

		while (pElementIterator->getCurrentElement() != NULL &&
			xercesc::XMLString::compareString(pElementIterator->getCurrentElement()->getNodeName(), TEXT("DrctDbtTxInf")) == 0)
		{
			pos = pElementIterator->getPosition();
			pTxInf = new DrctDbtTxInf();
			if (pTxInf)
			{
				pTxInf->fromDOMDocument(pElementIterator, errorOptions);
				AddDrctDbtTxInf(pTxInf);
			}
			if (pos == pElementIterator->getPosition())
				break;
		}
	}
}

void PmtInf::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD
	calcSums();
}

void PmtInf::elementDeleted(Element *pElement)
{
	DEBUG_METHOD
	calcSums();
}

void PmtInf::AddDrctDbtTxInf(DrctDbtTxInf *pDrctDbtTxInf)
{
	DEBUG_METHOD
	// Set listeners
	pDrctDbtTxInf->m_InstdAmt.setElementListener(this);

	m_DrctDbtTxInfs.push_back(pDrctDbtTxInf);
	calcSums();
}

void PmtInf::calcSums()
{
	DEBUG_METHOD
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
