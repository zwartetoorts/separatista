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
#include "directdebittransactioninformation.h"

using namespace Separatista;

PmtId::PmtId() :
BranchElement(TEXT("PmtId")),
m_EndToEndId(TEXT("EndToEndId"))
{

}

xercesc::DOMElement* PmtId::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_EndToEndId.toDOMDocument(pDocument, pElement);

	return pElement;
}

void PmtId::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_EndToEndId.fromDOMDocument(pElementIterator);
	}
}

MndtRltdInf::MndtRltdInf() :
BranchElement(TEXT("MndtRltdInf")),
m_MndtId(TEXT("MndtId")),
m_DtOfSgntr(TEXT("DtOfSgntr"))
{
	m_DtOfSgntr.setValue(std::time(NULL));
}

xercesc::DOMElement* MndtRltdInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MndtId.toDOMDocument(pDocument, pElement);
		m_DtOfSgntr.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void MndtRltdInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
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

}

xercesc::DOMElement* DrctDbtTx::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MndtRltdInf.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void DrctDbtTx::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_MndtRltdInf.fromDOMDocument(pElementIterator);
	}
}

RmtInf::RmtInf() :
BranchElement(TEXT("RmtInf")),
m_Ustrd(TEXT("Ustrd"))
{

}

xercesc::DOMElement* RmtInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Ustrd.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void RmtInf::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Ustrd.fromDOMDocument(pElementIterator);
	}
}

DrctDbtTxInf::DrctDbtTxInf() :
BranchElement(TEXT("DrctDbtTxInf")),
m_PmtId(),
m_InstdAmt(TEXT("InstdAmt")),
m_DrctDbtTx(),
m_DbtrAgt(TEXT("DbtrAgt")),
m_Dbtr(TEXT("Dbtr")),
m_DbtrAcct(TEXT("DbtrAcct")),
m_RmtInf()
{

}

xercesc::DOMElement* DrctDbtTxInf::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pInstdAmt;
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

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
