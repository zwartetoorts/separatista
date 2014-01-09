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

const wchar_t* const* CustomerDirectDebitInitiationV02::getOrder()
{
	static const wchar_t* const order[] = {
		GroupHeader::GrpHdr,
		PaymentInstructionInformation::PmtInf,
		NULL
	};

	return order;
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
const wchar_t* GroupHeader39::Authstn = L"Authstn";
const wchar_t* GroupHeader39::NbOfTxs = L"NbOfTxs";
const wchar_t* GroupHeader39::CtrlSum = L"CtrlSum";

GroupHeader39::GroupHeader39(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement),
m_InitgPty(pDocument, getChildElement(PartyIdentification::InitgPty, true))
{
}

const wchar_t* const* GroupHeader39::getOrder()
{
	static const wchar_t* const order[] = {
		MsgId,
		CreDtTm,
		Authstn,
		NbOfTxs,
		CtrlSum,
		NULL
	};

	return order;
}

PartyIdentification& GroupHeader39::getInitiatingParty()
{
	return m_InitgPty;
}



const wchar_t* PaymentInstructionInformation4::PmtInf = L"PmtInf";

PaymentInstructionInformation4::PaymentInstructionInformation4(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement)
{
}

const wchar_t* const* PaymentInstructionInformation4::getOrder()
{
	static const wchar_t* const order[] =
	{
		NULL
	};

	return order;
}

const wchar_t* PartyIdentification32::InitgPty = L"InitgPty";
const wchar_t* PartyIdentification32::Nm = L"Nm";
const wchar_t* PartyIdentification32::PstlAdr = L"PstlAdr";
const wchar_t* PartyIdentification32::Id = L"Id";
const wchar_t* PartyIdentification32::CtryOfRes = L"CtryOfRes";
const wchar_t* PartyIdentification32::CtctDtls = L"CtctDtls";

PartyIdentification32::PartyIdentification32(DOMDocument *pDocument, DOMElement *pElement)
:Element(pDocument, pElement)
{

}

const wchar_t* const* PartyIdentification32::getOrder()
{
	static const wchar_t* const order[] = {
		Nm,
		PstlAdr,
		Id,
		CtryOfRes,
		CtctDtls,
		NULL
	};

	return order;
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

const wchar_t* DirectDebitDocument::getMessageIdentification()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(GroupHeader::MsgId);
}

void DirectDebitDocument::setMessageIdentification(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().setChildElementValue(GroupHeader::MsgId, pValue);
}

time_t DirectDebitDocument::getCreationDateTime()
{
	const wchar_t *pDateTime;
	
	if (!m_pCstmrDrctDbtInitn)
		return -1;
	
	pDateTime = m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(GroupHeader::CreDtTm);
	if (!pDateTime)
		return -1;

	return toTime(pDateTime);
}

void DirectDebitDocument::setCreationDateTime(const wchar_t *pDateTime)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().setChildElementValue(GroupHeader::CreDtTm, pDateTime);
}

uint64_t DirectDebitDocument::getNumberOfTransactions()
{
	const wchar_t *pValue;

	if (!m_pCstmrDrctDbtInitn)
		return 0;

	pValue = m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(GroupHeader::NbOfTxs);
	if (!pValue)
		return 0;

	return toLong(pValue);
}

const wchar_t* DirectDebitDocument::getAuthorisation(unsigned int index)
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(index, GroupHeader39::Authstn);
}

void DirectDebitDocument::setAuthorisation(unsigned int index, const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().setChildElementValue(index, GroupHeader::Authstn, pValue);
}

uint64_t DirectDebitDocument::getControlSum()
{
	const wchar_t *pValue;

	if (!m_pCstmrDrctDbtInitn)
		return 0;

	pValue = m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(GroupHeader::CtrlSum);
	if (!pValue)
		return 0;

	return toUInt64(pValue);
}

const wchar_t* DirectDebitDocument::getInitiatingPartyName()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().getChildElementValue(PartyIdentification::Nm);
}

void DirectDebitDocument::setInitiatingPartyName(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().setChildElementValue(PartyIdentification::Nm, pValue);
}

const wchar_t* DirectDebitDocument::getInitiatingPartyPostalAddress()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().getChildElementValue(PartyIdentification::PstlAdr);
}

void DirectDebitDocument::setInitiatingPartyPostalAddress(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().setChildElementValue(PartyIdentification::PstlAdr, pValue);
}

const wchar_t* DirectDebitDocument::getInitiatingPartyId()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().getChildElementValue(PartyIdentification::Id);
}

void DirectDebitDocument::setInitiatingPartyId(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().setChildElementValue(PartyIdentification::Id, pValue);
}

const wchar_t* DirectDebitDocument::getInitiatingPartyCountryOfResidence()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().getChildElementValue(PartyIdentification::CtryOfRes);
}

void DirectDebitDocument::setInitiatingPartyCountryOfResidence(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().setChildElementValue(PartyIdentification::CtryOfRes, pValue);
}

const wchar_t* DirectDebitDocument::getInitiatingPartyContactDetails()
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().getChildElementValue(PartyIdentification::CtctDtls);
}

void DirectDebitDocument::setInitiatingPartyContactDetails(const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().getInitiatingParty().setChildElementValue(PartyIdentification::CtctDtls, pValue);
}

