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

#include "taxinformation.h"

IMPLEMENT_TAG(TaxParty1, TaxId)
IMPLEMENT_TAG(TaxParty1, RegnId)
IMPLEMENT_TAG(TaxParty1, TaxTp)

IMPLEMENT_CONSTRUCTOR(TaxParty1)
{}

BEGIN_IMPLEMENT_ORDER(TaxParty1)
TaxId,
RegnId,
TaxTp
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(TaxAuthorisation1, Titl)
IMPLEMENT_TAG(TaxAuthorisation1, Nm)

IMPLEMENT_CONSTRUCTOR(TaxAuthorisation1)
{}

BEGIN_IMPLEMENT_ORDER(TaxAuthorisation1)
Titl,
Nm
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(TaxParty2, TaxId)
IMPLEMENT_TAG(TaxParty2, RegnId)
IMPLEMENT_TAG(TaxParty2, TaxTp)
IMPLEMENT_TAG(TaxParty2, Authstn)

IMPLEMENT_CONSTRUCTOR(TaxParty2)
IMPLEMENT_CHILD(Authorisation, Authstn)
{}

BEGIN_IMPLEMENT_ORDER(TaxParty2)
TaxId,
RegnId,
TaxTp,
Authstn
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(TaxInformation3, Cdtr)
IMPLEMENT_TAG(TaxInformation3, Dbtr)
IMPLEMENT_TAG(TaxInformation3, AdmstnZn)
IMPLEMENT_TAG(TaxInformation3, RefNb)
IMPLEMENT_TAG(TaxInformation3, Mtd)
IMPLEMENT_TAG(TaxInformation3, TtlTaxblBaseAmt)
IMPLEMENT_TAG(TaxInformation3, TtlTaxAmt)
IMPLEMENT_TAG(TaxInformation3, Dt)
IMPLEMENT_TAG(TaxInformation3, SeqNb)

IMPLEMENT_CONSTRUCTOR(TaxInformation3)
IMPLEMENT_CHILD(Creditor, Cdtr)
IMPLEMENT_CHILD(Debtor, Dbtr)
{}

BEGIN_IMPLEMENT_ORDER(TaxInformation3)
Cdtr,
Dbtr,
AdmstnZn,
RefNb,
Mtd,
TtlTaxblBaseAmt,
TtlTaxAmt,
Dt,
SeqNb
END_IMPLEMENT_ORDER
