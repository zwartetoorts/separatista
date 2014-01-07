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
using namespace Separatista;

const wchar_t* CustomerDirectDebitInitiationV02::CstmrDrctDbtInitn = L"CstmrDrctDbtInitn";

CustomerDirectDebitInitiationV02::CustomerDirectDebitInitiationV02(DOMDocument *pDocument)
:Element(pDocument, pDocument->getDocumentElement(), CstmrDrctDbtInitn, true),
m_GrpHdr(pDocument, getChildElement(GroupHeader::GrpHdr, true))
{
	// Find all PaymentInformation elements if they exist
	DOMNodeList *pNodeList;

	pNodeList = getElementsByTagName(PaymentInstructionInformation::PmtInf);
	if (pNodeList)
	{
		for (XMLSize_t i = 0; i < pNodeList->getLength(); i++)
			addPaymentInstructionInformation(new PaymentInstructionInformation(pDocument, (DOMElement*)pNodeList->item(i)));
	}

	m_pmtInfIterator = m_pmtInfs.begin();
}

CustomerDirectDebitInitiationV02::~CustomerDirectDebitInitiationV02()
{
	// Delete all PaymentInstructionInformations
	while (!m_pmtInfs.empty())
	{
		delete m_pmtInfs.back();
		m_pmtInfs.pop_back();
	}
}

GroupHeader& CustomerDirectDebitInitiationV02::getGroupHeader()
{
	return m_GrpHdr;
}

void CustomerDirectDebitInitiationV02::addPaymentInstructionInformation(PaymentInstructionInformation *pPmtInf)
{
	m_pmtInfs.push_back(pPmtInf);
	m_pmtInfIterator = m_pmtInfs.begin();
}

const wchar_t* GroupHeader39::GrpHdr = L"GrpHdr";
const wchar_t* GroupHeader39::MsgId = L"MsgId";
const wchar_t* GroupHeader39::CreDtTm = L"CreDtTm";
const wchar_t* GroupHeader39::NbOfTxs = L"NbOfTxs";
const wchar_t* GroupHeader39::CtrlSum = L"CtrlSum";

GroupHeader39::GroupHeader39(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement),
m_InitgPty(pDocument, getChildElement(PartyIdentification::InitgPty, true))
{
}

const wchar_t* PaymentInstructionInformation4::PmtInf = L"PmtInf";

PaymentInstructionInformation4::PaymentInstructionInformation4(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement)
{
}

const wchar_t* PartyIdentification32::InitgPty = L"InitgPty";

PartyIdentification32::PartyIdentification32(DOMDocument *pDocument, DOMElement *pElement)
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

const wchar_t* DirectDebitDocument::getGroupHeaderValue(const wchar_t *pTagName)
{
	DOMElement *pElement;

	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	try
	{
		GroupHeader grphdr = m_pCstmrDrctDbtInitn->getGroupHeader();
		pElement = grphdr.getChildElement(pTagName);
		if (!pElement)
			return NULL;

		return pElement->getTextContent();
	}
	catch (const DOMException &e)
	{
		setErrorMessage(e.getMessage());
		return NULL;
	}
}


void DirectDebitDocument::setGroupHeaderValue(const wchar_t *pTagName, const wchar_t *pValue)
{
	DOMElement *pElement;

	if (!m_pCstmrDrctDbtInitn)
		return;

	try
	{
		GroupHeader grphdr = m_pCstmrDrctDbtInitn->getGroupHeader();
		pElement = grphdr.getChildElement(pTagName, true);
		if (!pElement)
			return;

		pElement->setNodeValue(pValue);
	}
	catch (const DOMException &e)
	{
		setErrorMessage(e.getMessage());
	}
}

const wchar_t* DirectDebitDocument::getMessageIdentification()
{
	return getGroupHeaderValue(GroupHeader::MsgId);
}

void DirectDebitDocument::setMessageIdentification(const wchar_t *pValue)
{
	setGroupHeaderValue(GroupHeader::MsgId, pValue);
}

time_t DirectDebitDocument::getCreationDateTime()
{
	const wchar_t *pDateTime;
	
	pDateTime = getGroupHeaderValue(GroupHeader::CreDtTm);
	if (!pDateTime)
		return -1;

	return toTime(pDateTime);
}

void DirectDebitDocument::setCreationDateTime(const wchar_t *pDateTime)
{
	setGroupHeaderValue(GroupHeader::CreDtTm, pDateTime);
}

uint64_t DirectDebitDocument::getNumberOfTransactions()
{
	const wchar_t *pValue;

	pValue = getGroupHeaderValue(GroupHeader::NbOfTxs);
	if (!pValue)
		return 0;

	return toLong(pValue);
}

uint64_t DirectDebitDocument::getControlSum()
{
	const wchar_t *pValue;

	pValue = getGroupHeaderValue(GroupHeader::CtrlSum);
	if (!pValue)
		return 0;

	return toUInt64(pValue);
}

