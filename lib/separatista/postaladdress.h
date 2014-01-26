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

#ifndef SEPARATISTA_POSTALADDRESS_H
#define SEPARATISTA_POSTALADDRESS_H

#include "macro.h"
#include "element.h"
#include "separatista.h"
#include "postaladdress.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(PostalAddress6, PostalAddress6)
	DECLARE_TAG_ENUM(Separatista::AddressType2Code, AddressType, 6, AdrTp)
	DECLARE_TAG(Department, Dept)
	DECLARE_TAG(SubDepartment, SubDept)
	DECLARE_TAG(StreetName, StrtNm)
	DECLARE_TAG(BuildingNumber, BldgNb)
	DECLARE_TAG(PostCode, PstCd)
	DECLARE_TAG(TownName, TwnNm)
	DECLARE_TAG(CountrySubDivision, CtrySubDvsn)
	DECLARE_TAG(Country, Ctry)
	DECLARE_TAG_MULTI(AddressLine, AdrLine, 7)
	END_DECLARE_CLASS
}

#endif // !defined SEPARATISTA_POSTALADDRESS_H
