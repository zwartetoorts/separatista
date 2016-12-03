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
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/branchandfinancialinstitutionidentification.h"

using namespace Separatista;

static const ElementDescriptor Separatista::FinancialInstitutionIdentification7[] =
{
	{
		SEPARATISTA_TAG("BIC"),			// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

static const ElementDescriptor Separatista::FinancialInstitutionIdentification8[] = 
{
	{
		SEPARATISTA_TAG("BICFI"),		// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

static const ElementDescriptor Separatista::BranchAndFinancialInstitutionIdentification4[] =
{
	{
		SEPARATISTA_TAG("FinInstnId"),	// TagName
		BranchElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(FinancialInstitutionIdentification7)
	}
};

static const ElementDescriptor Separatista::BranchAndFinancialInstitutionIdentification5[] = 
{
	{
		SEPARATISTA_TAG("FinInstnId"),	// TagName
		BranchElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(FinancialInstitutionIdentification8)
	}
};

