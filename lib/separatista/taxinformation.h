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

#ifndef SEPARATISTA_TAXINFORMATION_H
#define SEPARATISTA_TAXINFORMATION_H

#include "element.h"
#include "macro.h"
#include "separatista.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(TaxParty1, TaxParty1)
	DECLARE_TAG(TaxIdentification, TaxId)
	DECLARE_TAG(RegistrationIdentification, RegnId)
	DECLARE_TAG(TaxType, TaxTp)
	END_DECLARE_CLASS

	BEGIN_DECLARE_CLASS_SUPER(TaxAuthorisation1, TaxAuthorisation1)
	DECLARE_TAG(Title, Titl)
	DECLARE_TAG(Name, Nm)
	END_DECLARE_CLASS

	BEGIN_DECLARE_CLASS_SUPER(TaxParty2, TaxParty2)
	DECLARE_TAG(TaxIdentification, TaxId)
	DECLARE_TAG(RegistrationIdentification, RegnId)
	DECLARE_TAG(TaxType, TaxTp)
	DECLARE_CHILD(TaxAuthorisation1, Authorisation, Authstn)
	END_DECLARE_CLASS

	BEGIN_DECLARE_CLASS_SUPER(TaxInformation3, TaxInformation3)
	DECLARE_CHILD(TaxParty1, Creditor, Cdtr)
	DECLARE_CHILD(TaxParty2, Debtor, Dbtr)
	DECLARE_TAG(AdministrationZone, AdmstnZn)
	DECLARE_TAG(ReferenceNumber, RefNb)
	DECLARE_TAG(Method, Mtd)
	DECLARE_TAG(TotalTaxableBaseAmount, TtlTaxblBaseAmt)
	DECLARE_TAG_ATTRIBUTE(TotalTaxableBaseAmount, TtlTaxblBaseAmt, Ccy)
	DECLARE_TAG(TotalTaxAmount, TtlTaxAmt)
	DECLARE_TAG_ATTRIBUTE(TotalTaxAmount, TtlTaxAmt, Ccy)
	DECLARE_TAG_TIME(Date, Dt)
	DECLARE_TAG(SequenceNumber, SeqNb)
	// Record not implemented yet
	END_DECLARE_CLASS

}

#endif
