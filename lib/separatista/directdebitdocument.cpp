/***************************************************************************
*   Copyright (C) 2013 by Okkel Klaver   *
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

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>

#include "separatista.h"
#include "directdebitdocument.h"
#include "iban/iban.h"

#include <string>

using namespace xercesc;
using namespace SeparatistaPrivate;
using Separatista::DirectDebitDocument;

IMPLEMENT_TAG(CustomerDirectDebitInitiationV02, CstmrDrctDbtInitn)
IMPLEMENT_TAG(CustomerDirectDebitInitiationV02, GrpHdr)
IMPLEMENT_TAG(CustomerDirectDebitInitiationV02, PmtInf)

IMPLEMENT_CONSTRUCTOR(CustomerDirectDebitInitiationV02)
IMPLEMENT_CHILD(GroupHeader, CustomerDirectDebitInitiation::GrpHdr)
{
	// Find all PaymentInformation elements if they exist
	DOMNodeList *pNodeList;

	pNodeList = getElementsByTagName(PmtInf);
	if (pNodeList)
	{
		for (XMLSize_t i = 0; i < pNodeList->getLength(); i++)
			addPaymentInstructionInformation(new PaymentInstructionInformation4(pDocument, this, (DOMElement*)pNodeList->item(i), PmtInf));
	}

	moveFirst();
}

BEGIN_IMPLEMENT_ORDER(CustomerDirectDebitInitiationV02)
	GrpHdr,
	PmtInf
END_IMPLEMENT_ORDER

CustomerDirectDebitInitiationV02::~CustomerDirectDebitInitiationV02()
{
	// Delete all PaymentInstructionInformations
	while (!m_pmtInfs.empty())
	{
		delete m_pmtInfs.back();
		m_pmtInfs.pop_back();
	}
}

void CustomerDirectDebitInitiationV02::addPaymentInstructionInformation(PaymentInstructionInformation4 *pPmtInf)
{
	m_pmtInfs.push_back(pPmtInf);
	moveFirst();
}

PaymentInstructionInformation4* CustomerDirectDebitInitiationV02::getPaymentInstructionInformation()
{
	if (m_pmtInfIterator == m_pmtInfs.end())
		return NULL;

	return *m_pmtInfIterator;
}

bool CustomerDirectDebitInitiationV02::FEOF()
{
	if (m_pmtInfIterator != m_pmtInfs.end())
		return false;
	return true;
}

void CustomerDirectDebitInitiationV02::moveFirst()
{
	m_pmtInfIterator = m_pmtInfs.begin();
}

void CustomerDirectDebitInitiationV02::moveNext()
{
	if (m_pmtInfIterator != m_pmtInfs.end())
		++m_pmtInfIterator;
}

size_t CustomerDirectDebitInitiationV02::getCount()
{
	return m_pmtInfs.size();
}


const wchar_t* DirectDebitDocument::NamespaceURI = L"urn:iso:std:iso:20022:tech:xsd:pain.008.001.02";

DirectDebitDocument::DirectDebitDocument()
{
	DOMDocument *pDocument;
	DOMElement *pElement, *pDocumentElement;

	try
	{
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(L"core");
		if (!impl)
			return;

		pDocument = impl->createDocument(NamespaceURI, Document, NULL);
		if (!pDocument)
			return;
		setDOMDocument(pDocument);

		pDocumentElement = pDocument->getDocumentElement();
		if (!pDocumentElement)
			return;

		pElement = pDocument->createElement(CustomerDirectDebitInitiation::CstmrDrctDbtInitn);
		if (!pElement)
			return;
		pDocumentElement->appendChild(pElement);
		
		m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument, NULL, pElement, CustomerDirectDebitInitiationV02::CstmrDrctDbtInitn);
	}
	catch (const DOMException &e)
	{
		setErrorMessage(e.getMessage());
	}
	catch (...)
	{
	}
}

DirectDebitDocument::DirectDebitDocument(xercesc::DOMDocument *pDocument)
{
	DOMElement *pElement;

	setDOMDocument(pDocument);

	m_pCstmrDrctDbtInitn = NULL;

	pElement = pDocument->getDocumentElement();
	if (!pElement)
		return;
	pElement = pElement->getFirstElementChild();
	if (XMLString::compareString(pElement->getTagName(), CustomerDirectDebitInitiation::CstmrDrctDbtInitn) != 0)
		return;

	m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument, NULL, pElement, CustomerDirectDebitInitiation::CstmrDrctDbtInitn);
}

DirectDebitDocument::~DirectDebitDocument()
{
	if (m_pCstmrDrctDbtInitn)
		delete m_pCstmrDrctDbtInitn;
}

const Separatista::SeparatistaDocument::DocumentType DirectDebitDocument::getDocumentType() const
{
	return SeparatistaDocument::DirectDebitDocumentType;
}

bool DirectDebitDocument::FEOF()
{
	if (!m_pCstmrDrctDbtInitn)
		return true;

	return m_pCstmrDrctDbtInitn->FEOF();
}

void DirectDebitDocument::moveNext()
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->moveNext();
}

void DirectDebitDocument::moveFirst()
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->moveFirst();
}

size_t DirectDebitDocument::getCount()
{
	if (!m_pCstmrDrctDbtInitn)
		return 0;

	return m_pCstmrDrctDbtInitn->getCount();
}

