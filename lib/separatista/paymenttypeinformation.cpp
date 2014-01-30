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

#include "paymenttypeinformation.h"

using SeparatistaPrivate::PaymentTypeInformation24;

IMPLEMENT_TAG(PaymentTypeInformation24, InstrPty)
IMPLEMENT_TAG(PaymentTypeInformation24, SvcLvl)
IMPLEMENT_TAG(PaymentTypeInformation24, LclInstrm)
IMPLEMENT_TAG(PaymentTypeInformation24, SeqTp)
IMPLEMENT_TAG(PaymentTypeInformation24, CtgyPurp)

IMPLEMENT_CONSTRUCTOR(PaymentTypeInformation24)
IMPLEMENT_CHILD(ServiceLevel, SvcLvl)
IMPLEMENT_CHILD(LocalInstrument, LclInstrm)
IMPLEMENT_CHILD(CategoryPurpose, CtgyPurp)
{
}

BEGIN_IMPLEMENT_TAG_ENUM(PaymentTypeInformation24, Separatista::Priority2Code, InstructionPriority, InstrPty)
IMPLEMENT_TAG_ENUM(Separatista::Priority2Code::High, HIGH)
IMPLEMENT_TAG_ENUM(Separatista::Priority2Code::Normal, NORMAL)
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_TAG_ENUM(PaymentTypeInformation24, Separatista::SequenceType3Code, SequenceType, SeqTp)
IMPLEMENT_TAG_ENUM(Separatista::SequenceType3Code::First, FRST)
IMPLEMENT_TAG_ENUM(Separatista::SequenceType3Code::Recurring, RCUR)
IMPLEMENT_TAG_ENUM(Separatista::SequenceType3Code::Final, FNAL)
IMPLEMENT_TAG_ENUM(Separatista::SequenceType3Code::OneOff, OOFF)
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_ORDER(PaymentTypeInformation24)
	InstrPty,
	SvcLvl,
	LclInstrm,
	SeqTp,
	CtgyPurp
END_IMPLEMENT_ORDER