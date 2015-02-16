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

#include "separatista/separatista.h"
#include "separatista/pain/groupheader.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

GrpHdr::GrpHdr() :
BranchElement(TEXT("GrpHdr")),
m_MsgId(TEXT("MsgId"), Validators.Max35TextValidator),
m_CreDtTm(TEXT("CreDtTm"), Validators.ISODateTimeValidator),
m_NbOfTxs(TEXT("NbOfTxs"), Validators.Max15NumericTextValidator),
m_CtrlSum(TEXT("CtrlSum"), Validators.DecimalNumberValidator),
m_InitgPty(TEXT("InitgPty"))
{
	DEBUG_METHOD
}

DOMElement* GrpHdr::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MsgId.toDOMDocument(pDocument, pElement, errorOptions);
		m_CreDtTm.toDOMDocument(pDocument, pElement, errorOptions);
		m_NbOfTxs.toDOMDocument(pDocument, pElement, errorOptions);
		m_CtrlSum.toDOMDocument(pDocument, pElement, errorOptions);
		m_InitgPty.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void GrpHdr::fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_MsgId.fromDOMDocument(pElementIterator, errorOptions);
		m_CreDtTm.fromDOMDocument(pElementIterator, errorOptions);
		m_NbOfTxs.fromDOMDocument(pElementIterator, errorOptions);
		m_CtrlSum.fromDOMDocument(pElementIterator, errorOptions);
		m_InitgPty.fromDOMDocument(pElementIterator, errorOptions);
	}
}
