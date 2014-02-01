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

#ifndef SEPARATISTA_MANDATERELATEDINFORMATION_H
#define SEPARATISTA_MANDATERELATEDINFORMATION_H

#include "element.h"
#include "macro.h"
#include "separatista.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(MandateRelatedInformation8, MandateRelatedInformation8)
	DECLARE_TAG(MandateIdentification, MndtId)
	DECLARE_TAG_TIME(DateOfSignature, DtOfSgntr)
	DECLARE_TAG(AmendmentIndicator, AmdmntInd)
	DECLARE_TAG(ElectronicSignature, ElctrncSgntr)
	DECLARE_TAG_TIME(FirstCollectionDate, FrstColltnDt)
	DECLARE_TAG_TIME(FinalCollectionDate, FnlColltnDt)
	DECLARE_TAG_ENUM(Separatista::Frequency6Code, Frequency, 9, Frqcy)
	END_DECLARE_CLASS

}

#endif
