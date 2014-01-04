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

using namespace xercesc;
using namespace Separatista;

const wchar_t* CustomerDirectDebitInitiationV02::CstmrDrctDbtInitn = L"CstmrDrctDbtInitn";

CustomerDirectDebitInitiationV02::CustomerDirectDebitInitiationV02(DOMDocument *pDocument)
:Element(pDocument, pDocument->getDocumentElement(), CstmrDrctDbtInitn, true),
m_GrpHdr(pDocument, getChildElement(GroupHeader::GrpHdr, true)),
m_PmtInf(pDocument, getChildElement(PaymentInstructionInformation::PmtInf, true))
{
}

const wchar_t* GroupHeader39::GrpHdr = L"GrpHdr";

GroupHeader39::GroupHeader39(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement)
{
}

const wchar_t* PaymentInstructionInformation4::PmtInf = L"PmtInf";

PaymentInstructionInformation4::PaymentInstructionInformation4(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement)
{
}

const wchar_t* DirectDebitDocument::NamespaceURI = L"urn:iso:std:iso:20022:tech:xsd:pain.008.001.02";

DirectDebitDocument::DirectDebitDocument()
{
	DOMDocument *pDocument;

	try
	{
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(L"core");
		if (!impl)
			return;

		pDocument = impl->createDocument(NamespaceURI, Document, NULL);
		if (!pDocument)
			return;

		setDOMDocument(pDocument);

		m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument);

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
	setDOMDocument(pDocument);

	m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument);
}

DirectDebitDocument::~DirectDebitDocument()
{
	if (m_pCstmrDrctDbtInitn)
		delete m_pCstmrDrctDbtInitn;
}

const SeparatistaDocument::DocumentType DirectDebitDocument::getDocumentType() const
{
	return SeparatistaDocument::DirectDebitDocumentType;
}

