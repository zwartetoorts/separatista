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
#include "separatista/pain/paymenttypeinformation.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"

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
