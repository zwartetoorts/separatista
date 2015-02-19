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

#include "cashaccount.h"
#include "documentiterator.h"
#include "debug/debug.h"

using namespace Separatista;

AccountIdentification4Choice::AccountIdentification4Choice() :
ChoiceElement<1>(TEXT("Id"), { &m_IBAN }),
m_IBAN(TEXT("IBAN"), Validators.IBANValidator)
{
	DEBUG_METHOD
}

CashAccount24::CashAccount24(const wchar_t *pTag) :
BranchElement(pTag),
m_Id()
{
	DEBUG_METHOD
}

xercesc::DOMElement* CashAccount24::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_Id.toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void CashAccount24::fromDOMDocument(DOMDocumentIterator &elementIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	elementIterator.fromDOMDocument(m_Id, errorOptions);
}
