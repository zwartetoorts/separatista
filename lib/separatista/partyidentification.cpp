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

#include "partyidentification.h"

IMPLEMENT_TAG(PartyIdentification43, Nm)
IMPLEMENT_TAG(PartyIdentification43, PstlAdr)
IMPLEMENT_TAG(PartyIdentification43, Id)
IMPLEMENT_TAG(PartyIdentification43, CtryOfRes)
IMPLEMENT_TAG(PartyIdentification43, CtctDtls)

IMPLEMENT_CONSTRUCTOR(PartyIdentification43)
IMPLEMENT_CHILD(PostalAddress, PstlAdr)
IMPLEMENT_CHILD(Identification, Id)
IMPLEMENT_CHILD(ContactDetails, CtctDtls)
{
}

BEGIN_IMPLEMENT_ORDER(PartyIdentification43)
	Nm,
	PstlAdr,
	Id,
	CtryOfRes,
	CtctDtls
END_IMPLEMENT_ORDER
