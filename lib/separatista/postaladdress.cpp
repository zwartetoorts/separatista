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

