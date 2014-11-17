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
m_Cd(TEXT("Cd"))
{
	DEBUG_METHOD
}

xercesc::DOMElement* SvcLvl::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

void SvcLvl::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Cd.fromDOMDocument(pElementIterator);
	}
}

LclInstrm::LclInstrm() :
BranchElement(TEXT("LclInstrm")),
m_Cd(TEXT("Cd"))
{
	DEBUG_METHOD
}

xercesc::DOMElement* LclInstrm::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Cd.toDOMDocument(pDocument, pElement);

	return pElement;
}

void LclInstrm::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Cd.fromDOMDocument(pElementIterator);
	}
}

PmtTpInf::PmtTpInf() :
BranchElement(TEXT("PmtTpInf")),
m_SvcLvl(),
m_LclInstrm(),
m_SeqTp(TEXT("SeqTp"))
{
	DEBUG_METHOD
}

xercesc::DOMElement* PmtTpInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_SvcLvl.toDOMDocument(pDocument, pElement);
		m_LclInstrm.toDOMDocument(pDocument, pElement);
		m_SeqTp.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void PmtTpInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_SvcLvl.fromDOMDocument(pElementIterator);
		m_LclInstrm.fromDOMDocument(pElementIterator);
		m_SeqTp.fromDOMDocument(pElementIterator);
	}
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

xercesc::DOMElement* PmtInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
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

void PmtInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	unsigned int pos;
	DrctDbtTxInf *pTxInf;
	
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_PmtInfId.fromDOMDocument(pElementIterator);
		m_PmtMtd.fromDOMDocument(pElementIterator);
		m_NbOfTxs.fromDOMDocument(pElementIterator);
		m_CtrlSum.fromDOMDocument(pElementIterator);
		m_PmtTpInf.fromDOMDocument(pElementIterator);
		m_ReqdColltnDt.fromDOMDocument(pElementIterator);
		m_Cdtr.fromDOMDocument(pElementIterator);
		m_CdtrAcct.fromDOMDocument(pElementIterator);
		m_CdtrAgt.fromDOMDocument(pElementIterator);
		m_ChrgBr.fromDOMDocument(pElementIterator);
		m_CdtrSchmeId.fromDOMDocument(pElementIterator);

		while (pElementIterator->getCurrentElement() != NULL &&
			xercesc::XMLString::compareString(pElementIterator->getCurrentElement()->getNodeName(), TEXT("DrctDbtTxInf")) == 0)
		{
			pos = pElementIterator->getPosition();
			pTxInf = new DrctDbtTxInf();
			if (pTxInf)
			{
				pTxInf->fromDOMDocument(pElementIterator);
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
