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

#ifndef SEPARATISTA_CONTACTDETAILS_H
#define SEPARATISTA_CONTACTDETAILS_H

#include "macro.h"
#include "element.h"
#include "separatista.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(ContactDetails2, ContactDetails2)
	DECLARE_TAG_ENUM(Separatista::NamePrefix1Code, NamePrefix, 4, NmPrfx)
	DECLARE_TAG(Name, Nm)
	DECLARE_TAG(PhoneNumber, PhneNb)
	DECLARE_TAG(MobileNumber, MobNb)
	DECLARE_TAG(FaxNumber, FaxNb)
	DECLARE_TAG(EmailAddress, EmailAdr)
	DECLARE_TAG(Other, Othr)
	END_DECLARE_CLASS
}

#endif