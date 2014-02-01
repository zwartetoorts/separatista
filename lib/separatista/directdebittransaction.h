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

#ifndef SEPARATISTA_DIRECTDEBITTRANSACTION_H
#define SEPARATISTA_DIRECTDEBITTRANSACTION_H

#include "element.h"
#include "macro.h"
#include "separatista.h"
#include "mandaterelatedinformation.h"
#include "partyidentification.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS_SUPER(DirectDebitTransaction7, DirectDebitTransaction7)
	DECLARE_CHILD(MandateRelatedInformation8, MandateRelatedInformation, MndtRltdInf)
	DECLARE_CHILD(PartyIdentification43, CreditorSchemeId, CdtrSchmeId)
	DECLARE_TAG(PreNotificationIdentification, PreNtfctnId)
	DECLARE_TAG_TIME(PreNotificationDate, PreNtfctnDt)
	END_DECLARE_CLASS
}

#endif
