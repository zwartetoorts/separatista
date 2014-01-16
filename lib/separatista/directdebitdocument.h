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

#ifndef SEPARATISTA_DIRECTDEBITDOCUMENT_H
#define SEPARATISTA_DIRECTDEBITDOCUMENT_H

#include "element.h"
#include <vector>

#define BEGIN_DECLARE_CLASS(name, tag) \
	class name : public Element \
	{ \
	public: \
	name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t* pTagName = NULL); \
	protected: \
	const wchar_t* const* getOrder(); \
	const wchar_t* getTagName() { static const wchar_t* tagName = L#tag; return tagName; };


#define BEGIN_DECLARE_CLASS_SUPER(name, tag) \
class name : public Element, public Separatista::##name \
	{ \
	public: \
	name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t* pTagName = NULL); \
	protected: \
	const wchar_t* const* getOrder(); \
	const wchar_t* getTagName() { static const wchar_t* tagName = L#tag; return tagName; };

#define END_DECLARE_CLASS };

#define DECLARE_CHILD(type, name, tag) \
	private: \
	type m_##name; \
	public: \
	static const wchar_t* tag; \
	type& get##name() { return m_##name; };

#define DECLARE_TAG_GET(name, tag) \
	public: \
	static const wchar_t* tag; \
	const wchar_t* get##name() { return getChildElementValue(tag); };

#define DECLARE_TAG(name, tag) \
	DECLARE_TAG_GET(name, tag) \
	void set##name(const wchar_t *pValue) { setChildElementValue(tag, pValue); };

namespace SeparatistaPrivate
{


BEGIN_DECLARE_CLASS(LocalInstrument2Choise, LclInstrm)
DECLARE_TAG(Code, Cd)
DECLARE_TAG(Proprietary, Prtry)
END_DECLARE_CLASS

typedef LocalInstrument2Choise LocalInstrumentChoise;

BEGIN_DECLARE_CLASS(ServiceLevel8Choise, SvcLvl)
DECLARE_TAG(Code, Cd)
DECLARE_TAG(Proprietary, Prtry)
END_DECLARE_CLASS

typedef ServiceLevel8Choise ServiceLevelChoise;

BEGIN_DECLARE_CLASS(PaymentTypeInformation20, PmtTpInf)
DECLARE_CHILD(ServiceLevelChoise, ServiceLevel, SvcLvl)
DECLARE_TAG(InstructionPriority, InstrPty)
//DECLARE_TAG(ServiceLevel, SvcLvl)
DECLARE_TAG(LocalInstrument, LclInstrm)
DECLARE_TAG(SequenceType, SeqTp)
DECLARE_TAG(CategoryPurpose, CtgyPurp)
END_DECLARE_CLASS

typedef PaymentTypeInformation20 PaymentTypeInformation;

BEGIN_DECLARE_CLASS_SUPER(PartyIdentification32, InitgPty)
DECLARE_TAG(Name, Nm)
DECLARE_TAG(PostalAddress, PstlAdr)
DECLARE_TAG(Identification, Id)
DECLARE_TAG(CountryOfResidence, CtryOfRes)
DECLARE_TAG(ContactDetails, CtctDtls)
END_DECLARE_CLASS

typedef PartyIdentification32 PartyIdentification;

BEGIN_DECLARE_CLASS(GroupHeader39, GrpHdr)
DECLARE_CHILD(PartyIdentification, InitiatingParty, InitgPty)
DECLARE_TAG(MessageIdentification, MsgId)
DECLARE_TAG(CreationDateTime, CreDtTm)
DECLARE_TAG(Authorisation, Authstn)
DECLARE_TAG_GET(NumberOfTransactions, NbOfTxs)
DECLARE_TAG_GET(ControlSum, CtrlSum)
//DECLARE_TAG(InitgPty)
DECLARE_TAG(ForwardingAgent, FwdgAgt)
END_DECLARE_CLASS

typedef GroupHeader39 GroupHeader;



BEGIN_DECLARE_CLASS(PaymentInstructionInformation4, PmtInf)
DECLARE_CHILD(PaymentTypeInformation, PaymentTypeInformation, PmtTpInf)
DECLARE_TAG(PaymentInformationIdentification, PmtInfId)
DECLARE_TAG(PaymentMethod, PmtMtd)
DECLARE_TAG(BatchBooking, BtchBookg)
DECLARE_TAG_GET(NumberOfTransactions, NbOfTxs)
DECLARE_TAG_GET(ControlSum, CtrlSum)
//DECLARE_TAG(PmtTpInf)
DECLARE_TAG(RequestedCollectionDate, ReqdColltnDt)
DECLARE_TAG(Creditor, Cdtr)
DECLARE_TAG(CreditorAccount, CdtrAcct)
DECLARE_TAG(CreditorAgent, CdtrAgt)
DECLARE_TAG(CreditorAgentAccount, CdtrAgtAcct)
DECLARE_TAG(UltimateCreditor, UlmtCdtr)
DECLARE_TAG(ChargeBearer, ChrgBr)
DECLARE_TAG(ChargesAccount, ChrgsAcct)
DECLARE_TAG(ChargesAccountAgent, ChrgsAgtAcct)
DECLARE_TAG(CreditorSchemeIdentification, CdtrSchmeId)
DECLARE_TAG(DirectDebitTransactionInformation, DrctDbtTxInf)
public:
	static const wchar_t *DirectDebit;
END_DECLARE_CLASS

typedef PaymentInstructionInformation4 PaymentInstructionInformation;

BEGIN_DECLARE_CLASS(CustomerDirectDebitInitiationV02, CstmrDrctDbtInitn)
DECLARE_CHILD(GroupHeader, GroupHeader, GrpHdr)
DECLARE_TAG(CustomerDirectDebitInitiation, CstmrDrctDbtInitn)
//DECLARE_TAG(GroupHeader, GrpHdr)
DECLARE_TAG(PaymentInformation, PmtInf)
public:
	~CustomerDirectDebitInitiationV02();
	void addPaymentInstructionInformation(PaymentInstructionInformation *pPmtInf);

	PaymentInstructionInformation* getPaymentInstructionInformation();

	// PaymentInformation methods
	/// True if we are the end of all PaymentInformations
	bool FEOF();
	/// Resets the internal pointer to the first PaymentInformation
	void moveFirst();
	/// Moves the internal pointer to the next PaymentInformation
	void moveNext();
	/// Get the number of PaymentInformations
	size_t getCount();

private:
	std::vector<PaymentInstructionInformation*> m_pmtInfs;
	std::vector<PaymentInstructionInformation*>::iterator m_pmtInfIterator;
END_DECLARE_CLASS

typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;

};

#endif // !defined SEPARATISTA_DIRECTDEBITDOCUMENT_H
