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

using namespace Separatista;

PersonIdentificationSchemeName1Choice::PersonIdentificationSchemeName1Choice(const wchar_t *pTag) :
ChoiceElement(pTag, { &m_Cd, &m_Prtry }),
m_Cd(TEXT("Cd"), ExternalPersonIdentification1Code()),
m_Prtry(TEXT("Prtry"), Max35TextValidator())
{
	DEBUG_METHOD
}

GenericPersonIdentification1::GenericPersonIdentification1(const wchar_t *pTag) :
BranchElement(pTag),
m_Id(TEXT("Id"), Max35TextValidator()),
m_SchmeNm(TEXT("SchmeNm"))
{
	DEBUG_METHOD
}

xercesc::DOMElement* GenericPersonIdentification1::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement);
		m_SchmeNm.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void GenericPersonIdentification1::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Id.fromDOMDocument(pElementIterator);
		m_SchmeNm.fromDOMDocument(pElementIterator);
	}
}

PersonIdentification5::PersonIdentification5(const wchar_t *pTag) :
BranchElement(pTag),
m_Othr(TEXT("Othr"))
{
	DEBUG_METHOD
}

xercesc::DOMElement* PersonIdentification5::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Othr.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void PersonIdentification5::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Othr.fromDOMDocument(pElementIterator);
	}
}

Party11Choice::Party11Choice() :
ChoiceElement(TEXT("Id"), { &m_PrvtId }),
m_PrvtId(TEXT("PrvtId"))
{
	DEBUG_METHOD
}

PartyIdentification43::PartyIdentification43(const wchar_t *pTag) :
BranchElement(pTag),
m_Nm(TEXT("Nm"), Max140TextValidator()),
m_Id()
{
	DEBUG_METHOD
}

xercesc::DOMElement* PartyIdentification43::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Nm.toDOMDocument(pDocument, pElement);
		m_Id.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void PartyIdentification43::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	DEBUG_METHOD
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Nm.fromDOMDocument(pElementIterator);
		m_Id.fromDOMDocument(pElementIterator);
	}
}
