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

#include "directdebittransactioninformation.h"

using SeparatistaPrivate::DirectDebitTransactionInformation13;

IMPLEMENT_TAG(DirectDebitTransactionInformation13, PmtId)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, PmtTpInf)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, InstAmd)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, ChrgBr)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, DrctDbtTx)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, UltmtCdtr)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, DbtrAgt)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, DbtrAgtAcct)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, Dbtr)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, DbtrAcct)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, UltmtDbtr)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, InstrForCdtrAgt)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, Purp)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, RgltryRptg)
IMPLEMENT_TAG(DirectDebitTransactionInformation13, Tax)

IMPLEMENT_CONSTRUCTOR(DirectDebitTransactionInformation13)
IMPLEMENT_CHILD(PaymentIdentification, PmtId)
IMPLEMENT_CHILD(PaymentTypeInformation, PmtTpInf)
IMPLEMENT_CHILD(DirectDebitTransaction, DrctDbtTx)
IMPLEMENT_CHILD(UltimateCreditor, UltmtCdtr)
IMPLEMENT_CHILD(DebtorAgent, DbtrAgt)
IMPLEMENT_CHILD(DebtorAgentAccount, DbtrAgtAcct)
IMPLEMENT_CHILD(Debtor, Dbtr)
IMPLEMENT_CHILD(DebtorAccount, DbtrAcct)
IMPLEMENT_CHILD(UltimateDebtor, UltmtDbtr)
IMPLEMENT_CHILD(Purpose, Purp)
BEGIN_IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, RegulatoryReporting, RgltryRptg, 10)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 0, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 1, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 2, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 3, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 4, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 5, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 6, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 7, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 8, RgltryRptg)
IMPLEMENT_CHILD_MULTI(RegulatoryAuthority2, 9, RgltryRptg)
END_IMPLEMENT_CHILD_MULTI
IMPLEMENT_CHILD(Tax, Tax)
{}

BEGIN_IMPLEMENT_TAG_ENUM(DirectDebitTransactionInformation13, Separatista::ChargeBearerType1Code, ChargeBearer, ChrgBr)
IMPLEMENT_TAG_ENUM(Separatista::ChargeBearerType1Code::BorneByDebtor, DEBT)
IMPLEMENT_TAG_ENUM(Separatista::ChargeBearerType1Code::BorneByCreditor, CRED)
IMPLEMENT_TAG_ENUM(Separatista::ChargeBearerType1Code::Shared, SHARED)
IMPLEMENT_TAG_ENUM(Separatista::ChargeBearerType1Code::FollowingServiceLevel, SLEV)
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_ORDER(DirectDebitTransactionInformation13)
PmtId,
PmtTpInf,
InstAmd,
ChrgBr,
DrctDbtTx,
UltmtCdtr,
DbtrAgt,
DbtrAgtAcct,
Dbtr,
DbtrAcct,
UltmtDbtr,
InstrForCdtrAgt,
Purp,
RgltryRptg,
Tax
END_IMPLEMENT_ORDER
