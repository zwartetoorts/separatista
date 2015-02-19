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

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>

#include "separatista/separatista.h"
#include "separatista/pain/directdebittransactioninformation.h"
#include "separatista/debug/debug.h"
#include "separatista/documentiterator.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

PmtId::PmtId() :
BranchElement(TEXT("PmtId")),
m_EndToEndId(TEXT("EndToEndId"), Validators.Max35TextValidator)
{
	DEBUG_METHOD
}

DOMElement* PmtId::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_EndToEndId.toDOMDocument(pDocument, pElement, errorOptions);

	return pElement;
}

void PmtId::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	
	elementIterator.fromDOMDocument(m_EndToEndId, errorOptions);
}

DrctDbtTxInf::DrctDbtTxInf() :
BranchElement(TEXT("DrctDbtTxInf")),
m_PmtId(),
m_InstdAmt(TEXT("InstdAmt"), Validators.ActiveOrHistoricCurrencyAndAmountValidator),
m_DrctDbtTx(),
m_DbtrAgt(TEXT("DbtrAgt")),
m_Dbtr(TEXT("Dbtr")),
m_DbtrAcct(TEXT("DbtrAcct")),
m_RmtInf()
{
	DEBUG_METHOD
}

DOMElement* DrctDbtTxInf::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	DOMElement *pInstdAmt;
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_PmtId.toDOMDocument(pDocument, pElement, errorOptions);
		pInstdAmt = m_InstdAmt.toDOMDocument(pDocument, pElement, errorOptions);
		if (pInstdAmt)
			pInstdAmt->setAttribute(TEXT("Ccy"), TEXT("EUR"));
		m_DrctDbtTx.toDOMDocument(pDocument, pElement, errorOptions);
		m_DbtrAgt.toDOMDocument(pDocument, pElement, errorOptions);
		m_Dbtr.toDOMDocument(pDocument, pElement, errorOptions);
		m_DbtrAcct.toDOMDocument(pDocument, pElement, errorOptions);
		m_RmtInf.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void DrctDbtTxInf::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	
	elementIterator.fromDOMDocument(m_PmtId, errorOptions);
	elementIterator.fromDOMDocument(m_InstdAmt, errorOptions);
	elementIterator.fromDOMDocument(m_DrctDbtTx, errorOptions);
	elementIterator.fromDOMDocument(m_DbtrAgt, errorOptions);
	elementIterator.fromDOMDocument(m_Dbtr, errorOptions);
	elementIterator.fromDOMDocument(m_DbtrAcct, errorOptions);
	elementIterator.fromDOMDocument(m_RmtInf, errorOptions);
}
