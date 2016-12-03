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
#include "separatista/partyidentification.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/validator.h"

using namespace Separatista;

static const ElementDescriptor Separatista::PersonIdentificationSchemeName1Choice[] = 
{
	{
		SEPARATISTA_TAG("Prtry"),		// TagName
		LeafElement::createElement,		// Creator function
		1,								// Min
		1,								// Max
		&Validators.Max35TextValidator, // Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

static const ElementDescriptor Separatista::GenericPersonIdentification1[] =
{
	{
		SEPARATISTA_TAG("Id"),		// TagName
		LeafElement::createElement,		// Creator function
		1,								// Min
		1,								// Max
		&Validators.Max35TextValidator, // Validator
		0,								// Number of child elements
		NULL							// Child elements
	},
	{
		SEPARATISTA_TAG("SchmeNm"),		// TagName
		ChoiceElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(PersonIdentificationSchemeName1Choice)
	}
};

static const ElementDescriptor Separatista::PersonIdentification5[] = 
{
	{
		SEPARATISTA_TAG("Othr"),		// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		0,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(GenericPersonIdentification1)
	}
};

static const ElementDescriptor Separatista::Party6Choice[] =
{
	{
		SEPARATISTA_TAG("PrvtId"),		// TagName
		BranchElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(PersonIdentification5)
	}
};

static const ElementDescriptor Separatista::Party11Choice[] = 
{
	{
		SEPARATISTA_TAG("PrvtId"),		// TagName
		BranchElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(PersonIdentification5)
	}
};

static const ElementDescriptor Separatista::PartyIdentification32[] =
{
	{
		SEPARATISTA_TAG("Nm"),
		LeafElement::createElement,
		0,
		1,
		&Validators.Max140TextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("Id"),			// TagName
		ChoiceElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Party6Choice)
	}
};


static const ElementDescriptor Separatista::PartyIdentification43[] = 
{
	{
		SEPARATISTA_TAG("Nm"),
		LeafElement::createElement,
		0,
		1,
		&Validators.Max140TextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("Id"),			// TagName
		ChoiceElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Party11Choice)
	}
};

