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

#include "accountidentificationchoice.h"

IMPLEMENT_TAG(GenericAccountIdentification1, Id)
IMPLEMENT_TAG(GenericAccountIdentification1, SchmeNm)
IMPLEMENT_TAG(GenericAccountIdentification1, Issr)

IMPLEMENT_CONSTRUCTOR(GenericAccountIdentification1)
IMPLEMENT_CHILD(SchemeName, SchmeNm)
{}

BEGIN_IMPLEMENT_ORDER(GenericAccountIdentification1)
Id,
SchmeNm,
Issr
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(AccountIdentification4Choice, IBAN)
IMPLEMENT_TAG(AccountIdentification4Choice, Othr)

IMPLEMENT_CONSTRUCTOR(AccountIdentification4Choice)
IMPLEMENT_CHILD(Other, Othr)
{}

BEGIN_IMPLEMENT_ORDER(AccountIdentification4Choice)
IBAN,
Othr
END_IMPLEMENT_ORDER
