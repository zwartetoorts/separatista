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

#ifndef SEPARATISTA_PAYMENTINSTRUCTIONINFORMATION_H
#define SEPARATISTA_PAYMENTINSTRUCTIONINFORMATION_H

#include "macro.h"
#include "element.h"
#include "paymenttypeinformation.h"
#include "partyidentification.h"
#include "cashaccount.h"
#include "branchandfinancialinstitutionidentification.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(PaymentInstructionInformation4, PaymentInstructionInformation4)
	DECLARE_CHILD(PaymentTypeInformation20, PaymentTypeInformation, PmtTpInf)
	DECLARE_CHILD(PartyIdentification43, Creditor, Cdtr)
	DECLARE_CHILD(CashAccount16, CreditorAccount, CdtrAcct)
	DECLARE_CHILD(BranchAndFinancialInstitutionIdentification4, CreditorAgent, CdtrAgt)
	DECLARE_CHILD(PartyIdentification43, UltimateCreditor, UltmtCdtr)
	DECLARE_CHILD(PartyIdentification43, CreditorSchemeIdentification, CdtrSchmeId)
	DECLARE_TAG(PaymentInformationIdentification, PmtInfId)
	DECLARE_TAG(PaymentMethod, PmtMtd)
	DECLARE_TAG(BatchBooking, BtchBookg)
	DECLARE_TAG_GET(NumberOfTransactions, NbOfTxs)
	DECLARE_TAG_GET(ControlSum, CtrlSum)
	DECLARE_TAG(RequestedCollectionDate, ReqdColltnDt)
	DECLARE_TAG(CreditorAgentAccount, CdtrAgtAcct)
	DECLARE_TAG(ChargeBearer, ChrgBr)
	DECLARE_TAG(ChargesAccount, ChrgsAcct)
	DECLARE_TAG(ChargesAccountAgent, ChrgsAcctAgt)
	DECLARE_TAG(DirectDebitTransactionInformation, DrctDbtTxInf)
	END_DECLARE_CLASS
}

#endif // !defined SEPARATISTA_PAYMENTINSTRUCTIONINFORMATION_H
