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
#include "separatista/documentiterator.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

PmtInf::PmtInf() :
BranchElement(TEXT("PmtInf"), Element::Mandatory),
m_PmtInfId(TEXT("PmtInfId"), Validators.Max35TextValidator, Element::Mandatory),
m_PmtMtd(TEXT("PmtMtd"), Validators.PaymentMethod2CodeValidator, Element::Mandatory),
m_NbOfTxs(TEXT("NbOfTxs"), Validators.Max15NumericTextValidator, Element::Optional),
m_CtrlSum(TEXT("CtrlSum"), Validators.DecimalNumberValidator, Element::Optional),
m_PmtTpInf(Element::Optional),
m_ReqdColltnDt(TEXT("ReqdColltnDt"), Validators.ISODateValidator, Element::Mandatory),
m_Cdtr(TEXT("Cdtr"), Element::Mandatory),
m_CdtrAcct(TEXT("CdtrAcct"), Element::Mandatory),
m_CdtrAgt(TEXT("CdtrAgt"), Element::Mandatory),
m_ChrgBr(TEXT("ChrgBr"), Validators.ChargeBearerType1CodeValidator, Element::Optional),
m_CdtrSchmeId(TEXT("CdtrSchmeId"), Element::Optional)
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

void PmtInf::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	DrctDbtTxInf *pTxInf;
	
	elementIterator.fromDOMDocument(m_PmtInfId, errorOptions);
	elementIterator.fromDOMDocument(m_PmtMtd, errorOptions);
	elementIterator.fromDOMDocument(m_NbOfTxs, errorOptions);
	elementIterator.fromDOMDocument(m_CtrlSum, errorOptions);
	elementIterator.fromDOMDocument(m_PmtTpInf, errorOptions);
	elementIterator.fromDOMDocument(m_ReqdColltnDt, errorOptions);
	elementIterator.fromDOMDocument(m_Cdtr, errorOptions);
	elementIterator.fromDOMDocument(m_CdtrAcct, errorOptions);
	elementIterator.fromDOMDocument(m_CdtrAgt, errorOptions);
	elementIterator.fromDOMDocument(m_ChrgBr, errorOptions);
	elementIterator.fromDOMDocument(m_CdtrSchmeId, errorOptions);

	while (!elementIterator.isDone())
	{
		pTxInf = new DrctDbtTxInf();
		if (pTxInf)
		{
			try
			{
				elementIterator.fromDOMDocument(*pTxInf, errorOptions);
				AddDrctDbtTxInf(pTxInf);
			}
			// Should be, MissingElementException. PmtInf should be mandatory.
			catch (const Exception &e)
			{
				delete pTxInf;
				throw(e);
			}
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
