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

#include "paymentinstructioninformation.h"

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
IMPLEMENT_TAG(PaymentInstructionInformation4, UltmtCdtr)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgBr)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgsAcct)
IMPLEMENT_TAG(PaymentInstructionInformation4, ChrgsAcctAgt)
IMPLEMENT_TAG(PaymentInstructionInformation4, CdtrSchmeId)
IMPLEMENT_TAG(PaymentInstructionInformation4, DrctDbtTxInf)

const wchar_t* Separatista::PaymentInstructionInformation4::DirectDebit = L"DD";

IMPLEMENT_CONSTRUCTOR(PaymentInstructionInformation4)
IMPLEMENT_CHILD(PaymentTypeInformation, PmtTpInf)
IMPLEMENT_CHILD(Creditor, Cdtr)
IMPLEMENT_CHILD(CreditorAccount, CdtrAcct)
IMPLEMENT_CHILD(CreditorAgent, CdtrAgt)
IMPLEMENT_CHILD(UltimateCreditor, UltmtCdtr)
IMPLEMENT_CHILD(CreditorSchemeIdentification, CdtrSchmeId)
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
	UltmtCdtr,
	ChrgBr,
	ChrgsAcct,
	ChrgsAcctAgt,
	CdtrSchmeId,
	DrctDbtTxInf
END_IMPLEMENT_ORDER

