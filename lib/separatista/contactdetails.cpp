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

#include "contactdetails.h"

using SeparatistaPrivate::ContactDetails2;

IMPLEMENT_TAG(ContactDetails2, NmPrfx)
IMPLEMENT_TAG(ContactDetails2, Nm)
IMPLEMENT_TAG(ContactDetails2, PhneNb)
IMPLEMENT_TAG(ContactDetails2, MobNb)
IMPLEMENT_TAG(ContactDetails2, FaxNb)
IMPLEMENT_TAG(ContactDetails2, EmailAdr)
IMPLEMENT_TAG(ContactDetails2, Othr)

IMPLEMENT_CONSTRUCTOR(ContactDetails2)
{}

BEGIN_IMPLEMENT_TAG_ENUM(ContactDetails2, Separatista::NamePrefix1Code, NamePrefix, NmPrfx)
IMPLEMENT_TAG_ENUM(Separatista::NamePrefix1Code::Doctor, DOCT)
IMPLEMENT_TAG_ENUM(Separatista::NamePrefix1Code::Mister, MIST)
IMPLEMENT_TAG_ENUM(Separatista::NamePrefix1Code::Miss, MISS)
IMPLEMENT_TAG_ENUM(Separatista::NamePrefix1Code::Madam, MADM)
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_ORDER(ContactDetails2)
NmPrfx,
Nm,
PhneNb,
MobNb,
FaxNb,
EmailAdr,
Othr
END_IMPLEMENT_ORDER
