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

#ifndef SEPARATISTA_FINANCIALINSTITUTIONIDENTIFICATION_H
#define SEPARATISTA_FINANCIALINSTITUTIONIDENTIFICATION_H

#include "macro.h"
#include "element.h"
#include "separatista.h"
#include "codeorproprietary.h"
#include "postaladdress.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(ClearingSystemMemberIdentification2, ClearingSystemMemberIdentification2)
	DECLARE_CHILD(ClearingSystemIdentification2Choice, ClearingSystemIdentification, ClrSysId)
	DECLARE_TAG(MemberIdentification, MmbId)
	END_DECLARE_CLASS

	BEGIN_DECLARE_CLASS_SUPER(GenericFinancialIdentification1, GenericFinancialIdentification1)
	DECLARE_TAG(Identification, Id)
	DECLARE_CHILD(SchemeName, SchemeName, SchmeNm)
	DECLARE_TAG(Issuer, Issr)
	END_DECLARE_CLASS

	BEGIN_DECLARE_CLASS_SUPER(FinancialInstitutionIdentification8, FinancialInstitutionIdentification8)
	DECLARE_TAG(BICFI, BICFI)
	DECLARE_CHILD(ClearingSystemMemberIdentification2, ClearingSystemMemberIdentification, ClrSysMmbId)
	DECLARE_CHILD(PostalAddress6, PostalAddress, PstlAddr)
	DECLARE_CHILD(GenericFinancialIdentification1, Other, Othr)
	END_DECLARE_CLASS
}

#endif
