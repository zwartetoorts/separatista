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

#include "codeorproprietary.h"

IMPLEMENT_TAG(CategoryPurpose1Choice, Cd)
IMPLEMENT_TAG(CategoryPurpose1Choice, Prtry)

IMPLEMENT_CONSTRUCTOR(CategoryPurpose1Choice)
{
}

BEGIN_IMPLEMENT_ORDER(CategoryPurpose1Choice)
	Cd,
	Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(LocalInstrument2Choice, Cd)
IMPLEMENT_TAG(LocalInstrument2Choice, Prtry)

IMPLEMENT_CONSTRUCTOR(LocalInstrument2Choice)
{
}

BEGIN_IMPLEMENT_ORDER(LocalInstrument2Choice)
	Cd,
	Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(ServiceLevel8Choice, Cd)
IMPLEMENT_TAG(ServiceLevel8Choice, Prtry)

IMPLEMENT_CONSTRUCTOR(ServiceLevel8Choice)
{
}

BEGIN_IMPLEMENT_ORDER(ServiceLevel8Choice)
	Cd,
	Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(SchemeName, Cd)
IMPLEMENT_TAG(SchemeName, Prtry)

IMPLEMENT_CONSTRUCTOR(SchemeName)
{
}

BEGIN_IMPLEMENT_ORDER(SchemeName)
Cd,
Prtry
END_IMPLEMENT_ORDER

