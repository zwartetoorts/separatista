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

#include "groupheader.h"

using SeparatistaPrivate::Authorisation;

IMPLEMENT_TAG(Authorisation, Cd)
IMPLEMENT_TAG(Authorisation, Prtry)

IMPLEMENT_CONSTRUCTOR(Authorisation)
{}

BEGIN_IMPLEMENT_TAG_ENUM(Authorisation, Separatista::Authorisation1Code, Code, Cd)
IMPLEMENT_TAG_ENUM(Separatista::Authorisation1Code::PreAuthorisedFile, AUTH)
IMPLEMENT_TAG_ENUM(Separatista::Authorisation1Code::FileLevelAuthorisationDetails, FDET)
IMPLEMENT_TAG_ENUM(Separatista::Authorisation1Code::FileLevelAuthorisationSummary, FSUM)
IMPLEMENT_TAG_ENUM(Separatista::Authorisation1Code::InstructionLevelAuthorisation, ILEV)
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_ORDER(Authorisation)
Cd,
Prtry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(GroupHeader55, MsgId)
IMPLEMENT_TAG(GroupHeader55, CreDtTm)
IMPLEMENT_TAG(GroupHeader55, Authstn)
IMPLEMENT_TAG(GroupHeader55, NbOfTxs)
IMPLEMENT_TAG(GroupHeader55, CtrlSum)
IMPLEMENT_TAG(GroupHeader55, InitgPty)
IMPLEMENT_TAG(GroupHeader55, FwdgAgt)

IMPLEMENT_CONSTRUCTOR(GroupHeader55)
IMPLEMENT_CHILD(InitiatingParty, InitgPty)
BEGIN_IMPLEMENT_CHILD_MULTI(Authorisation, Authorisation, Authstn, 2)
IMPLEMENT_CHILD_MULTI(Authorisation, 0, Authstn)
IMPLEMENT_CHILD_MULTI(Authorisation, 1, Authstn)
END_IMPLEMENT_CHILD_MULTI
{
}

BEGIN_IMPLEMENT_ORDER(GroupHeader55)
	MsgId,
	CreDtTm,
	Authstn,
	NbOfTxs,
	CtrlSum,
	InitgPty,
	FwdgAgt
END_IMPLEMENT_ORDER

