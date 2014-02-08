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

#include "regulatoryreporting.h"

IMPLEMENT_TAG(RegulatoryAuthority2, Nm)
IMPLEMENT_TAG(RegulatoryAuthority2, Ctry)

IMPLEMENT_CONSTRUCTOR(RegulatoryAuthority2)
{}

BEGIN_IMPLEMENT_ORDER(RegulatoryAuthority2)
Nm,
Ctry
END_IMPLEMENT_ORDER

IMPLEMENT_TAG(RegulatoryReporting3, DbtCdtRptgInd)
IMPLEMENT_TAG(RegulatoryReporting3, Authrty)

IMPLEMENT_CONSTRUCTOR(RegulatoryReporting3)
IMPLEMENT_CHILD(Authority, Authrty)
{}

BEGIN_IMPLEMENT_TAG_ENUM(RegulatoryReporting3, Separatista::RegulatoryReportingType1Code, DebitCreditReportingIndicator, DbtCdtRptgInd)
IMPLEMENT_TAG_ENUM(Separatista::RegulatoryReportingType1Code::Credit, "CRED")
IMPLEMENT_TAG_ENUM(Separatista::RegulatoryReportingType1Code::Debit, "DEBT")
IMPLEMENT_TAG_ENUM(Separatista::RegulatoryReportingType1Code::Both, "BOTH")
END_IMPLEMENT_TAG_ENUM

BEGIN_IMPLEMENT_ORDER(RegulatoryReporting3)
DbtCdtRptgInd,
Authrty
END_IMPLEMENT_ORDER

