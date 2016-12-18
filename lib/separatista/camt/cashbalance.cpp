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

#include <xercesc/dom/DOMDocument.hpp>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/validator.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/camt/cashbalance.h"

using namespace Separatista;

static const ElementDescriptor Separatista::camt_053_001::BalanceType5Choice[] =
{
	{
		SEPARATISTA_TAG("Cd"),			// TagName
		LeafElement::createElement,		// Creator function
		1,								// Min
		1,								// Max
		&Validators.BalanceType5ChoiceValidator,// Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

static const ElementDescriptor Separatista::camt_053_001::BalanceType12[] = 
{
	{
		SEPARATISTA_TAG("CdOrPrtry"),	// TagName
		ChoiceElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::BalanceType5Choice)
	}
};

static const ElementDescriptor Separatista::camt_053_001::CashBalance3[] =
{
	{
		SEPARATISTA_TAG("Tp"),			// TagName
		BranchElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::BalanceType12)
	}
};

