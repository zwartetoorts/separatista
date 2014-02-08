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

#ifndef SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H
#define SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H

#include <vector>
#include "element.h"
#include "macro.h"
#include "separatista.h"
#include "paymentidentification.h"
#include "paymenttypeinformation.h"
#include "directdebittransaction.h"
#include "partyidentification.h"
#include "cashaccount.h"
#include "branchandfinancialinstitutionidentification.h"
#include "regulatoryreporting.h"
#include "taxinformation.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(DirectDebitTransactionInformation13, DirectDebitTransactionInformation13)
	DECLARE_CHILD(PaymentIdentification1, PaymentIdentification, PmtId)
	DECLARE_CHILD(PaymentTypeInformation24, PaymentTypeInformation, PmtTpInf)
	DECLARE_TAG(InstructedAmount, InstAmd)
	DECLARE_TAG_ATTRIBUTE(InstructedAmount, InstAmd, Ccy)
	DECLARE_TAG_ENUM(Separatista::ChargeBearerType1Code, ChargeBearer, 4, ChrgBr)
	DECLARE_CHILD(DirectDebitTransaction7, DirectDebitTransaction, DrctDbtTx)
	DECLARE_CHILD(PartyIdentification43, UltimateCreditor, UltmtCdtr)
	DECLARE_CHILD(BranchAndFinancialInstitutionIdentification5, DebtorAgent, DbtrAgt)
	DECLARE_CHILD(PartyIdentification43, DebtorAgentAccount, DbtrAgtAcct)
	DECLARE_CHILD(PartyIdentification43, Debtor, Dbtr)
	DECLARE_CHILD(CashAccount24, DebtorAccount, DbtrAcct)
	DECLARE_CHILD(CashAccount24, UltimateDebtor, UltmtDbtr)
	DECLARE_TAG(InstructionForCreditorAgent, InstrForCdtrAgt)
	DECLARE_CHILD(Purpose2Choice, Purpose, Purp)
	DECLARE_CHILD_MULTI(RegulatoryAuthority2, RegulatoryReporting, RgltryRptg, 10)
	DECLARE_CHILD(TaxInformation3, Tax, Tax)

	END_DECLARE_CLASS
}

#endif
