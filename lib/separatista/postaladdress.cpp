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

#include "postaladdress.h"

using SeparatistaPrivate::PostalAddress6;

IMPLEMENT_TAG(PostalAddress6, AdrTp)
IMPLEMENT_TAG(PostalAddress6, Dept)
IMPLEMENT_TAG(PostalAddress6, SubDept)
IMPLEMENT_TAG(PostalAddress6, StrtNm)
IMPLEMENT_TAG(PostalAddress6, BldgNb)
IMPLEMENT_TAG(PostalAddress6, PstCd)
IMPLEMENT_TAG(PostalAddress6, TwnNm)
IMPLEMENT_TAG(PostalAddress6, CtrySubDvsn)
IMPLEMENT_TAG(PostalAddress6, Ctry)
IMPLEMENT_TAG(PostalAddress6, AdrLine)

IMPLEMENT_CONSTRUCTOR(PostalAddress6)
BEGIN_IMPLEMENT_TAG_MULTI(AddressLine, AdrLine, 7)
IMPLEMENT_TAG_MULTI(0, AdrLine)
IMPLEMENT_TAG_MULTI(1, AdrLine)
IMPLEMENT_TAG_MULTI(2, AdrLine)
IMPLEMENT_TAG_MULTI(3, AdrLine)
IMPLEMENT_TAG_MULTI(4, AdrLine)
IMPLEMENT_TAG_MULTI(5, AdrLine)
IMPLEMENT_TAG_MULTI(6, AdrLine)
END_IMPLEMENT_TAG_MULTI
{
}

BEGIN_IMPLEMENT_ORDER(PostalAddress6)
AdrTp,
Dept,
SubDept,
StrtNm,
BldgNb,
PstCd,
TwnNm,
CtrySubDvsn,
Ctry
END_IMPLEMENT_ORDER

BEGIN_IMPLEMENT_TAG_ENUM(PostalAddress6, Separatista::AddressType2Code, AddressType, AdrTp)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::Postal, ADDR)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::POBox, PBOX)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::Residential, HOME)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::Business, BIZZ)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::MailTo, MLTO)
IMPLEMENT_TAG_ENUM(Separatista::AddressType2Code::DeliveryTo, DLVY)
END_IMPLEMENT_TAG_ENUM;
