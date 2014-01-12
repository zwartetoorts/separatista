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

#define END_DECLARE_CLASS };

#define DECLARE_CHILD(name) \
	private: \
	name m_##name; \
	public: \
	name& get##name() { return m_##name; };

#define DECLARE_TAG(name) \
	public: \
	static const wchar_t* name; \
	const wchar_t* get##name() { return getChildElementValue(L#name); }; \
	void set##name(const wchar_t *pValue) { setChildElementValue(L#name, pValue); };

namespace Separatista
{

/****/
BEGIN_DECLARE_CLASS(LocalInstrument2Choise, LclInstrm)
DECLARE_TAG(Cd)
DECLARE_TAG(Prtry)
END_DECLARE_CLASS

typedef LocalInstrument2Choise LocalInstrumentChoise;

BEGIN_DECLARE_CLASS(ServiceLevel8Choise, SvcLvl)
DECLARE_TAG(Cd)
DECLARE_TAG(Prtry)
END_DECLARE_CLASS

typedef ServiceLevel8Choise ServiceLevelChoise;

BEGIN_DECLARE_CLASS(PaymentTypeInformation20, PmtTpInf)
DECLARE_CHILD(ServiceLevelChoise)
DECLARE_TAG(InstrPty)
DECLARE_TAG(SvcLvl)
DECLARE_TAG(LclInstrm)
DECLARE_TAG(SeqTp)
DECLARE_TAG(CtgyPurp)
public:
	const wchar_t* getInstructionPriority();
	void setInstructionPriority(const wchar_t *pValue);
END_DECLARE_CLASS

typedef PaymentTypeInformation20 PaymentTypeInformation;

BEGIN_DECLARE_CLASS(PartyIdentification32, InitgPty)
DECLARE_TAG(Nm)
DECLARE_TAG(PstlAdr)
DECLARE_TAG(Id)
DECLARE_TAG(CtryOfRes)
DECLARE_TAG(CtctDtls)
END_DECLARE_CLASS

typedef PartyIdentification32 PartyIdentification;

BEGIN_DECLARE_CLASS(GroupHeader39, GrpHdr)
DECLARE_CHILD(PartyIdentification)
DECLARE_TAG(MsgId)
DECLARE_TAG(CreDtTm)
DECLARE_TAG(Authstn)
DECLARE_TAG(NbOfTxs)
DECLARE_TAG(CtrlSum)
DECLARE_TAG(InitgPty)
DECLARE_TAG(FwdgAgt)
END_DECLARE_CLASS

typedef GroupHeader39 GroupHeader;

BEGIN_DECLARE_CLASS(PaymentInstructionInformation4, PmtInf)
DECLARE_CHILD(PaymentTypeInformation)
DECLARE_TAG(PmtInfId)
DECLARE_TAG(PmtMtd)
DECLARE_TAG(BtchBookg)
DECLARE_TAG(NbOfTxs)
DECLARE_TAG(CtrlSum)
DECLARE_TAG(PmtTpInf)
DECLARE_TAG(ReqdColltnDt)
DECLARE_TAG(Cdtr)
DECLARE_TAG(CdtrAcct)
DECLARE_TAG(CdtrAgt)
DECLARE_TAG(CdtrAgtAcct)
DECLARE_TAG(UlmtCdtr)
DECLARE_TAG(ChrgBr)
DECLARE_TAG(ChrgsAcct)
DECLARE_TAG(ChrgsAgtAcct)
DECLARE_TAG(CdtrSchmeld)
DECLARE_TAG(DrctDbtTxInf)
public:
	static const wchar_t *DirectDebit;

	const wchar_t* getPaymentInformationIdentification();
	void setPaymentInformationIdentification(const wchar_t *pValue);

	const wchar_t* getPaymentMethod();
	void setPaymentMenthod(const wchar_t *pValue);

	const wchar_t* getBatchBooking();
	void setBatchBooking(const wchar_t *pValue);

	uint64_t getNumberOfTransactions();

	uint64_t getControlSum();

	PaymentTypeInformation& getPaymentTypeInformation(bool create = false);

END_DECLARE_CLASS

typedef PaymentInstructionInformation4 PaymentInstructionInformation;

BEGIN_DECLARE_CLASS(CustomerDirectDebitInitiationV02, CstmrDrctDbtInitn)
DECLARE_CHILD(GroupHeader)
DECLARE_TAG(CstmrDrctDbtInitn)
DECLARE_TAG(GrpHdr)
DECLARE_TAG(PmtInf)
public:
	~CustomerDirectDebitInitiationV02();
	void addPaymentInstructionInformation(PaymentInstructionInformation *pPmtInf);
private:
	std::vector<PaymentInstructionInformation*> m_pmtInfs;
	std::vector<PaymentInstructionInformation*>::iterator m_pmtInfIterator;
END_DECLARE_CLASS

typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;

};

#endif // !defined SEPARATISTA_DIRECTDEBITDOCUMENT_H
