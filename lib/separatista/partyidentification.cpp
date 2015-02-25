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

#include "partyidentification.h"
#include "debug/debug.h"
#include "separatista/documentiterator.h"

using namespace Separatista;

PersonIdentificationSchemeName1Choice::PersonIdentificationSchemeName1Choice(const wchar_t *pTag, const ElementOptions options) :
ChoiceElement(pTag, { &m_Cd, &m_Prtry }, options),
m_Cd(TEXT("Cd"), Validators.ExternalPersonIdentification1CodeValidator, Element::Optional),
m_Prtry(TEXT("Prtry"), Validators.Max35TextValidator, Element::Optional)
{
	DEBUG_METHOD
}

GenericPersonIdentification1::GenericPersonIdentification1(const wchar_t *pTag, const ElementOptions options) :
BranchElement(pTag, options),
m_Id(TEXT("Id"), Validators.Max35TextValidator, Element::Mandatory),
m_SchmeNm(TEXT("SchmeNm"), Element::Optional)
{
	DEBUG_METHOD
}

xercesc::DOMElement* GenericPersonIdentification1::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement, errorOptions);
		m_SchmeNm.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void GenericPersonIdentification1::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	
	elementIterator.fromDOMDocument(m_Id, errorOptions);
	elementIterator.fromDOMDocument(m_SchmeNm, errorOptions);
}

PersonIdentification5::PersonIdentification5(const wchar_t *pTag, const ElementOptions options) :
BranchElement(pTag, options),
m_Othr(TEXT("Othr"), Element::Optional)
{
	DEBUG_METHOD
}

xercesc::DOMElement* PersonIdentification5::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Othr.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void PersonIdentification5::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	
	elementIterator.fromDOMDocument(m_Othr, errorOptions);
}

Party11Choice::Party11Choice(const ElementOptions options) :
ChoiceElement(TEXT("Id"), { &m_PrvtId }, options),
m_PrvtId(TEXT("PrvtId"), Element::Optional)
{
	DEBUG_METHOD
}

PartyIdentification43::PartyIdentification43(const wchar_t *pTag, const ElementOptions options) :
BranchElement(pTag, options),
m_Nm(TEXT("Nm"), Validators.Max140TextValidator, Element::Optional),
m_Id(Element::Optional)
{
	DEBUG_METHOD
}

xercesc::DOMElement* PartyIdentification43::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Nm.toDOMDocument(pDocument, pElement, errorOptions);
		m_Id.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void PartyIdentification43::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD

	elementIterator.fromDOMDocument(m_Nm, errorOptions);
	elementIterator.fromDOMDocument(m_Id, errorOptions);
}
