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
#include "separatista/cashaccount.h"
#include "separatista/choiceelement.h"
#include "separatista/leafelement.h"

using namespace Separatista;

static const ElementDescriptor Separatista::AccountIdentification4Choice[] =
{
	{
		SEPARATISTA_TAG("IBAN"),		// TagName
		LeafElement::createElement,		// Creator function
		1,								// Min
		1,								// Max
		&Validators.IBANValidator,		// Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

static const ElementDescriptor Separatista::GenericAccountIdentification1[] =
{
	{
		SEPARATISTA_TAG("IBAN"),
		LeafElement::createElement,
		1,
		1,
		&Validators.IBANValidator,
		0,
		NULL
	}
};

static const ElementDescriptor Separatista::CashAccount16[] =
{
	{
		SEPARATISTA_TAG("Id"),			// TagName
		ChoiceElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(AccountIdentification4Choice)
	}
};

static const ElementDescriptor Separatista::CashAccount20[] = 
{
	{
		SEPARATISTA_TAG("Id"),
		ChoiceElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(GenericAccountIdentification1)
	},
	{
		SEPARATISTA_TAG("Ccy"),
		LeafElement::createElement,
		0,
		1,
		&Validators.ActiveOrHistoricCurrencyAndAmountValidator,
		0,
		NULL
	}
};

static const ElementDescriptor Separatista::CashAccount24[] = 
{
	{
		SEPARATISTA_TAG("Id"),			// TagName
		ChoiceElement::createElement,	// Creator function
		1,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(AccountIdentification4Choice)
	}
};


