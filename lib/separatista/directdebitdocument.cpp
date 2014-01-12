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

#define IMPLEMENT_CONSTRUCTOR(name) \
	name::name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t *pTagName) \
	:Element(pDocument, pParent, pElement, pTagName)

#define IMPLEMENT_CHILD(child, tag) \
	,m_##child(pDocument, this, NULL, tag)

#define IMPLEMENT_TAG(name, tag) \
	const wchar_t* name::tag = L#tag;

#define BEGIN_IMPLEMENT_ORDER(name) \
	const wchar_t* const* name::getOrder() \
	{ \
	static const wchar_t* order[] = { \

#define END_IMPLEMENT_ORDER  \
	, NULL }; \
	return order; }

IMPLEMENT_TAG(LocalInstrument2Choise, Cd)
IMPLEMENT_TAG(LocalInstrument2Choise, Prtry)

IMPLEMENT_CONSTRUCTOR(LocalInstrument2Choise)
{
}

BEGIN_IMPLEMENT_ORDER(LocalInstrument2Choise)
	Cd,
	Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(ServiceLevel8Choise, Cd)
IMPLEMENT_TAG(ServiceLevel8Choise, Prtry)

IMPLEMENT_CONSTRUCTOR(ServiceLevel8Choise)
{
}

BEGIN_IMPLEMENT_ORDER(ServiceLevel8Choise)
		Cd,
		Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(PaymentTypeInformation20, InstrPty)
IMPLEMENT_TAG(PaymentTypeInformation20, SvcLvl)
IMPLEMENT_TAG(PaymentTypeInformation20, LclInstrm)
IMPLEMENT_TAG(PaymentTypeInformation20, SeqTp)
IMPLEMENT_TAG(PaymentTypeInformation20, CtgyPurp)

IMPLEMENT_CONSTRUCTOR(PaymentTypeInformation20)
IMPLEMENT_CHILD(ServiceLevelChoise, PaymentTypeInformation::SvcLvl)
{
}

BEGIN_IMPLEMENT_ORDER(PaymentTypeInformation20)
		InstrPty,
		SvcLvl,
		LclInstrm,
		SeqTp,
		CtgyPurp
END_IMPLEMENT_ORDER

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
			addPaymentInstructionInformation(new PaymentInstructionInformation(pDocument, this, (DOMElement*)pNodeList->item(i)));
	}

	m_pmtInfIterator = m_pmtInfs.begin();
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


void CustomerDirectDebitInitiationV02::addPaymentInstructionInformation(PaymentInstructionInformation *pPmtInf)
{
	m_pmtInfs.push_back(pPmtInf);
	m_pmtInfIterator = m_pmtInfs.begin();
}

IMPLEMENT_TAG(GroupHeader39, MsgId)
IMPLEMENT_TAG(GroupHeader39, CreDtTm)
IMPLEMENT_TAG(GroupHeader39, Authstn)
IMPLEMENT_TAG(GroupHeader39, NbOfTxs)
IMPLEMENT_TAG(GroupHeader39, CtrlSum)
IMPLEMENT_TAG(GroupHeader39, InitgPty)
IMPLEMENT_TAG(GroupHeader39, FwdgAgt)

IMPLEMENT_CONSTRUCTOR(GroupHeader39)
IMPLEMENT_CHILD(PartyIdentification, GroupHeader::InitgPty)
{
}

BEGIN_IMPLEMENT_ORDER(GroupHeader39)
	MsgId,
	CreDtTm,
	Authstn,
	NbOfTxs,
	CtrlSum,
	InitgPty,
	FwdgAgt
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(PaymentInstructionInformation4, PmtInfId)
IMPLEMENT_TAG(PaymentInstructionInformation4, PmtMtd)
IMPLEMENT_TAG(PaymentInstructionInformation4, BtchBookg)
IMPLEMENT_TAG(PaymentInstructionInformation4, NbOfTxs)
IMPLEMENT_TAG(PaymentInstructionInformation4, CtrlSum)
IMPLEMENT_TAG(PaymentInstructionInformation4, PmtTpInf)
IMPLEMENT_TAG(PaymentInstructionInformation4, ReqdColltnDt)
IMPLEMENT_TAG(PaymentInstructionInformation4, Cdtr)
IMPLEMENT_TAG(PaymentInstructionInformation4, CdtrAcct)
IMPLEMENT_TAG(PaymentInstructionInformation4, CdtrAgt)
IMPLEMENT_TAG(PaymentInstructionInformation4, CdtrAgtAcct)
IMPLEMENT_TAG(PaymentInstructionInformation4, UlmtCdtr)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgBr)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgsAcct)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgsAgtAcct)
IMPLEMENT_TAG(PaymentInstructionInformation4, CdtrSchmeld)
IMPLEMENT_TAG(PaymentInstructionInformation4, DrctDbtTxInf)

const wchar_t* PaymentInstructionInformation4::DirectDebit = L"DD";

IMPLEMENT_CONSTRUCTOR(PaymentInstructionInformation4)
IMPLEMENT_CHILD(PaymentTypeInformation,PaymentInstructionInformation::PmtTpInf)
{
}

BEGIN_IMPLEMENT_ORDER(PaymentInstructionInformation4)
		PmtInfId,
		PmtMtd,
		BtchBookg,
		NbOfTxs,
		CtrlSum,
		PmtTpInf,
		ReqdColltnDt,
		Cdtr,
		CdtrAcct,
		CdtrAgt,
		CdtrAgtAcct,
		UlmtCdtr,
		ChrgBr,
		ChrgsAcct,
		ChrgsAgtAcct,
		CdtrSchmeld,
		DrctDbtTxInf
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(PartyIdentification32, Nm)
IMPLEMENT_TAG(PartyIdentification32, PstlAdr)
IMPLEMENT_TAG(PartyIdentification32, Id)
IMPLEMENT_TAG(PartyIdentification32, CtryOfRes)
IMPLEMENT_TAG(PartyIdentification32, CtctDtls)

IMPLEMENT_CONSTRUCTOR(PartyIdentification32)
{
}

BEGIN_IMPLEMENT_ORDER(PartyIdentification32)
		Nm,
		PstlAdr,
		Id,
		CtryOfRes,
		CtctDtls
END_IMPLEMENT_ORDER

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
		
		m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument, NULL, pElement);
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

	m_pCstmrDrctDbtInitn = new CustomerDirectDebitInitiation(pDocument, NULL, pElement);
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

#define IMPLEMENT_PROPERTY_SAFE_GET(getter, tag) \
	(m_pCstmrDrctDbtInitn ? m_pCstmrDrctDbtInitn->##getter.getChildElementValue(tag) : NULL)

#define IMPLEMENT_PROPERTY_SAFE_SET(getter, tag) \
	(m_pCstmrDrctDbtInitn ? m_pCstmrDrctDbtInitn->##getter.setChildElementValue(tag, pValue) : NULL)

#define IMPLEMENT_PROPERTY_GET(cls, name, getter, tag) \
	const wchar_t* cls::get##name() { return IMPLEMENT_PROPERTY_SAFE_GET(getter, tag); }

#define IMPLEMENT_PROPERTY_SET(cls, name, getter, tag) \
	void cls::set##name(const wchar_t *pValue) { IMPLEMENT_PROPERTY_SAFE_SET(getter, tag); }

#define IMPLEMENT_PROPERTY(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_GET(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_SET(cls, name, getter, tag)

#define IMPLEMENT_PROPERTY_TIME_GET(cls, name, getter, tag) \
	time_t cls::get##name() { return toTime(IMPLEMENT_PROPERTY_SAFE_GET(getter, tag)); }

#define IMPLEMENT_PROPERTY_TIME(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_TIME_GET(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_SET(cls, name, getter, tag)

#define IMPLEMENT_PROPERTY_LONG_GET(cls, name, getter, tag) \
	long cls::get##name() { return toLong(IMPLEMENT_PROPERTY_SAFE_GET(getter, tag)); }

#define IMPLEMENT_PROPERTY_LONG(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_LONG_GET(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_SET(cls, name, getter, tag)

#define IMPLEMENT_PROPERTY_UINT64_GET(cls, name, getter, tag) \
	uint64_t cls::get##name() { return toUInt64(IMPLEMENT_PROPERTY_SAFE_GET(getter, tag)); }

#define IMPLEMENT_PROPERTY_UINT64(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_UINT64_GET(cls, name, getter, tag) \
	IMPLEMENT_PROPERTY_SET(cls, name, getter, tag)

IMPLEMENT_PROPERTY(DirectDebitDocument, MessageIdentification, getGroupHeader(), GroupHeader::MsgId)
IMPLEMENT_PROPERTY_TIME(DirectDebitDocument, CreationDateTime, getGroupHeader(), GroupHeader::CreDtTm)
IMPLEMENT_PROPERTY_UINT64_GET(DirectDebitDocument, NumberOfTransactions, getGroupHeader(), GroupHeader::NbOfTxs)
IMPLEMENT_PROPERTY_UINT64_GET(DirectDebitDocument, ControlSum, getGroupHeader(), GroupHeader::CtrlSum)
IMPLEMENT_PROPERTY(DirectDebitDocument, InitiatingPartyName, getGroupHeader().getPartyIdentification(), PartyIdentification::Nm)
IMPLEMENT_PROPERTY(DirectDebitDocument, InitiatingPartyPostalAddress, getGroupHeader().getPartyIdentification(), PartyIdentification::PstlAdr)
IMPLEMENT_PROPERTY(DirectDebitDocument, InitiatingPartyId, getGroupHeader().getPartyIdentification(), PartyIdentification::Id)
IMPLEMENT_PROPERTY(DirectDebitDocument, InitiatingPartyCountryOfResidence, getGroupHeader().getPartyIdentification(), PartyIdentification::CtryOfRes)
IMPLEMENT_PROPERTY(DirectDebitDocument, InitiatingPartyContactDetails, getGroupHeader().getPartyIdentification(), PartyIdentification::CtctDtls)
IMPLEMENT_PROPERTY(DirectDebitDocument, ForwardingAgent, getGroupHeader(), GroupHeader::FwdgAgt)

const wchar_t* DirectDebitDocument::getAuthorisation(unsigned int index)
{
	if (!m_pCstmrDrctDbtInitn)
		return NULL;

	return m_pCstmrDrctDbtInitn->getGroupHeader().getChildElementValue(index, GroupHeader::Authstn);
}

void DirectDebitDocument::setAuthorisation(unsigned int index, const wchar_t *pValue)
{
	if (m_pCstmrDrctDbtInitn)
		m_pCstmrDrctDbtInitn->getGroupHeader().setChildElementValue(index, GroupHeader::Authstn, pValue);
}

