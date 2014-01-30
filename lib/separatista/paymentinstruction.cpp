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

#include "paymentinstruction.h"

IMPLEMENT_TAG(PaymentInstruction10, PmtInfId)
IMPLEMENT_TAG(PaymentInstruction10, PmtMtd)
IMPLEMENT_TAG(PaymentInstruction10, BtchBookg)
IMPLEMENT_TAG(PaymentInstruction10, NbOfTxs)
IMPLEMENT_TAG(PaymentInstruction10, CtrlSum)
IMPLEMENT_TAG(PaymentInstruction10, PmtTpInf)
IMPLEMENT_TAG(PaymentInstruction10, ReqdColltnDt)
IMPLEMENT_TAG(PaymentInstruction10, Cdtr)
IMPLEMENT_TAG(PaymentInstruction10, CdtrAcct)
IMPLEMENT_TAG(PaymentInstruction10, CdtrAgt)
IMPLEMENT_TAG(PaymentInstruction10, CdtrAgtAcct)
IMPLEMENT_TAG(PaymentInstruction10, UltmtCdtr)
IMPLEMENT_TAG(PaymentInstruction10, ChrgBr)
IMPLEMENT_TAG(PaymentInstruction10, ChrgsAcct)
IMPLEMENT_TAG(PaymentInstruction10, ChrgsAcctAgt)
IMPLEMENT_TAG(PaymentInstruction10, CdtrSchmeId)
IMPLEMENT_TAG(PaymentInstruction10, DrctDbtTxInf)

const wchar_t* Separatista::PaymentInstruction10::DirectDebit = L"DD";

IMPLEMENT_CONSTRUCTOR(PaymentInstruction10)
IMPLEMENT_CHILD(PaymentTypeInformation, PmtTpInf)
IMPLEMENT_CHILD(Creditor, Cdtr)
IMPLEMENT_CHILD(CreditorAccount, CdtrAcct)
IMPLEMENT_CHILD(CreditorAgent, CdtrAgt)
IMPLEMENT_CHILD(UltimateCreditor, UltmtCdtr)
IMPLEMENT_CHILD(CreditorSchemeIdentification, CdtrSchmeId)
{
}

BEGIN_IMPLEMENT_ORDER(PaymentInstruction10)
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
	UltmtCdtr,
	ChrgBr,
	ChrgsAcct,
	ChrgsAcctAgt,
	CdtrSchmeId,
	DrctDbtTxInf
END_IMPLEMENT_ORDER

