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
#include "separatista/documentiterator.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

SvcLvl::SvcLvl(const ElementOptions options) :
ChoiceElement<2>(TEXT("SvcLvl"), { &m_Cd, &m_Prtry }, options),
m_Cd(TEXT("Cd"), Validators.ExternalServiceLevel1CodeValidator, Element::Optional),
m_Prtry(TEXT("Prtry"), Validators.Max35TextValidator, Element::Optional)
{
	DEBUG_METHOD
}

LclInstrm::LclInstrm(const ElementOptions options) :
ChoiceElement<2>(TEXT("LclInstrm"), { &m_Cd, &m_Prtry }, options),
m_Cd(TEXT("Cd"), Validators.ExternalLocalInstrumentCodeValidator, Element::Optional),
m_Prtry(TEXT("Prtry"), Validators.Max35TextValidator, Element::Optional)
{
	DEBUG_METHOD
}

PmtTpInf::PmtTpInf(const ElementOptions options) :
BranchElement(TEXT("PmtTpInf"), options),
m_SvcLvl(Element::Optional),
m_LclInstrm(Element::Optional),
m_SeqTp(TEXT("SeqTp"), Validators.SequenceType3CodeValidator, Element::Optional)
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

void PmtTpInf::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	
	elementIterator.fromDOMDocument(m_SvcLvl, errorOptions);
	elementIterator.fromDOMDocument(m_LclInstrm, errorOptions);
	elementIterator.fromDOMDocument(m_SeqTp, errorOptions);
}
