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

namespace Separatista
{

class PartyIdentification32 : public Element
{	
public:
	static const wchar_t *InitgPty;
	static const wchar_t *Nm;
	static const wchar_t *PstlAdr;
	static const wchar_t *Id;
	static const wchar_t *CtryOfRes;
	static const wchar_t *CtctDtls;

	PartyIdentification32(DOMDocument *pDocument, DOMElement *pElement);
protected:
	const wchar_t* const* getOrder();
};

typedef PartyIdentification32 PartyIdentification;

class GroupHeader39 : public Element
{
public:
	static const wchar_t *GrpHdr;
	static const wchar_t *MsgId;
	static const wchar_t *CreDtTm;
	static const wchar_t *Authstn;
	static const wchar_t *NbOfTxs;
	static const wchar_t *CtrlSum;

	GroupHeader39(DOMDocument *pDocument, DOMElement *pElement);

	PartyIdentification& getInitiatingParty();
protected:
	const wchar_t* const* getOrder();

private:
	PartyIdentification m_InitgPty;
};

typedef GroupHeader39 GroupHeader;

class PaymentInstructionInformation4 : public Element
{
public:
	static const wchar_t *PmtInf;

	PaymentInstructionInformation4(DOMDocument *pDocument, DOMElement *pElement);
protected:
	const wchar_t* const* getOrder();

};

typedef PaymentInstructionInformation4 PaymentInstructionInformation;

class CustomerDirectDebitInitiationV02 : public Element
{
public:
	static const wchar_t *CstmrDrctDbtInitn;

	CustomerDirectDebitInitiationV02(DOMDocument *pDocument);

	~CustomerDirectDebitInitiationV02();

	GroupHeader& getGroupHeader();

	/**
	Add PaymentInstructionInformation to the list. Will reset list position to begin.
	*/
	void addPaymentInstructionInformation(PaymentInstructionInformation *pPmtInf);
protected:
	const wchar_t* const* getOrder();

private:
	std::vector<PaymentInstructionInformation*> m_pmtInfs;
	std::vector<PaymentInstructionInformation*>::iterator m_pmtInfIterator;
	GroupHeader m_GrpHdr;
};

typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;

};

#endif // !defined SEPARATISTA_DIRECTDEBITDOCUMENT_H
