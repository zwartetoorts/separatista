/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/camt/banktocustomerstatement.h"
#include "separatista/camt/camt_groupheader.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/documentreader.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"
#include "separatista/elementdescriptor.h"

using namespace Separatista;
using namespace Separatista::camt_053_001;

const wchar_t* BankToCustomerStatementV02::m_NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:camt.053.001.02");

const ElementDescriptor BankToCustomerStatementV02[] =
{
	{
		SEPARATISTA_TAG("GrpHdr"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(GroupHeader42)
	}
};

const ElementDescriptor BankToCustomerStatementV02::m_BankToCustomerStatementV02[] =
{
	{
		SEPARATISTA_TAG("BkToCstmrStmt"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(::BankToCustomerStatementV02)
	}
};

BankToCustomerStatement::BankToCustomerStatement(const ElementDescriptor *pElementDescriptor)
	:BranchElement(pElementDescriptor)
{
	DEBUG_METHOD;

	addElementListener(this);
}

BankToCustomerStatement::BankToCustomerStatement(const ElementDescriptor *pElementDescriptor, xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	:BranchElement(pElementDescriptor)
{
	DEBUG_METHOD;

	addElementListener(this);
	fromDOMDocument(pDOMDocument->getDocumentElement()->getFirstElementChild(), errorOptions);
}

void BankToCustomerStatement::calcSum()
{
	DEBUG_METHOD;

	
}

void BankToCustomerStatement::elementValueChanged(Element * pElement, const wchar_t * pNewValue)
{
	DEBUG_METHOD;

	// Call calcSum on the right child elements
}

void BankToCustomerStatement::elementCreated(Element * pParent, Element * pChild)
{
	DEBUG_METHOD;

	// Set hooks on child elements

}

void BankToCustomerStatement::elementDeleted(Element * pElement)
{
	DEBUG_METHOD;

	if (std::wcscmp(TEXT("PmtInf"), pElement->getTag()) == 0)
	{
		calcSum();
	}
	else if (std::wcscmp(TEXT("DrctDbtTxInf"), pElement->getTag()) == 0)
	{
		calcSum();
	}
	else if (std::wcscmp(TEXT("InstdAmt"), pElement->getTag()) == 0)
	{
		calcSum();
	}

}

BankToCustomerStatementV02::BankToCustomerStatementV02()
	:BankToCustomerStatement(m_BankToCustomerStatementV02)
{
	DEBUG_METHOD;
}

BankToCustomerStatementV02::BankToCustomerStatementV02(xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	: BankToCustomerStatement(m_BankToCustomerStatementV02, pDOMDocument, errorOptions)
{
	DEBUG_METHOD;
}
