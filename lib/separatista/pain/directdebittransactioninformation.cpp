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

using namespace Separatista;
using namespace Separatista::pain_008_001;

PmtId::PmtId() :
BranchElement(TEXT("PmtId")),
m_EndToEndId(TEXT("EndToEndId"), Max35TextValidator())
{
	DEBUG_METHOD
}

DOMElement* PmtId::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_EndToEndId.toDOMDocument(pDocument, pElement);

	return pElement;
}

void PmtId::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_EndToEndId.fromDOMDocument(pElementIterator);
	}
}

MndtRltdInf::MndtRltdInf() :
BranchElement(TEXT("MndtRltdInf")),
m_MndtId(TEXT("MndtId"), Max35TextValidator()),
m_DtOfSgntr(TEXT("DtOfSgntr"), ISODateValidator())
{
	DEBUG_METHOD
	m_DtOfSgntr.setValue(std::time(NULL));
}

DOMElement* MndtRltdInf::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MndtId.toDOMDocument(pDocument, pElement);
		m_DtOfSgntr.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void MndtRltdInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_MndtId.fromDOMDocument(pElementIterator);
		m_DtOfSgntr.fromDOMDocument(pElementIterator);
	}
}

DrctDbtTx::DrctDbtTx() :
BranchElement(TEXT("DrctDbtTx")),
m_MndtRltdInf()
{
	DEBUG_METHOD
}

DOMElement* DrctDbtTx::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MndtRltdInf.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void DrctDbtTx::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_MndtRltdInf.fromDOMDocument(pElementIterator);
	}
}

RmtInf::RmtInf() :
BranchElement(TEXT("RmtInf")),
m_Ustrd(TEXT("Ustrd"), Max140TextValidator())
{
	DEBUG_METHOD
}

DOMElement* RmtInf::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Ustrd.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void RmtInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Ustrd.fromDOMDocument(pElementIterator);
	}
}

DrctDbtTxInf::DrctDbtTxInf() :
BranchElement(TEXT("DrctDbtTxInf")),
m_PmtId(),
m_InstdAmt(TEXT("InstdAmt"), ActiveOrHistoricCurrencyAndAmountValidator()),
m_DrctDbtTx(),
m_DbtrAgt(TEXT("DbtrAgt")),
m_Dbtr(TEXT("Dbtr")),
m_DbtrAcct(TEXT("DbtrAcct")),
m_RmtInf()
{
	DEBUG_METHOD
}

DOMElement* DrctDbtTxInf::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent)
{
	DEBUG_METHOD
	DOMElement *pInstdAmt;
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_PmtId.toDOMDocument(pDocument, pElement);
		pInstdAmt = m_InstdAmt.toDOMDocument(pDocument, pElement);
		if (pInstdAmt)
			pInstdAmt->setAttribute(TEXT("Ccy"), TEXT("EUR"));
		m_DrctDbtTx.toDOMDocument(pDocument, pElement);
		m_DbtrAgt.toDOMDocument(pDocument, pElement);
		m_Dbtr.toDOMDocument(pDocument, pElement);
		m_DbtrAcct.toDOMDocument(pDocument, pElement);
		m_RmtInf.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void DrctDbtTxInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_PmtId.fromDOMDocument(pElementIterator);
		m_InstdAmt.fromDOMDocument(pElementIterator);
		m_DrctDbtTx.fromDOMDocument(pElementIterator);
		m_DbtrAgt.fromDOMDocument(pElementIterator);
		m_Dbtr.fromDOMDocument(pElementIterator);
		m_DbtrAcct.fromDOMDocument(pElementIterator);
		m_RmtInf.fromDOMDocument(pElementIterator);
	}
}
