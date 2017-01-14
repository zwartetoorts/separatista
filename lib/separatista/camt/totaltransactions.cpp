/***************************************************************************
*   Copyright (C) 2017 by Okkel Klaver   *
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

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/validator.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/attributedleafelement.h"
#include "separatista/camt/totaltransactions.h"

using namespace Separatista;

static const ElementDescriptor Separatista::camt_053_001::TotalPerBankTransactionCode2[] =
{
	{
		SEPARATISTA_TAG(""),	// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::NumberAndSumOfTransactions2)
	}
};

static const ElementDescriptor Separatista::camt_053_001::NumberAndSumOfTransactions1[] =
{
	{
		SEPARATISTA_TAG("TtlNtries"),	// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.Max15NumericTextValidator,// Validator
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("Sum"),			// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.DecimalNumberValidator,// Validator
		0,
		NULL
	}
};

static const ElementDescriptor Separatista::camt_053_001::NumberAndSumOfTransactions2[] =
{
	{
		SEPARATISTA_TAG("NbOfNtries"),	// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.Max15NumericTextValidator, // Validator
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("Sum"),			// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.DecimalNumberValidator, // Validator
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("TtlNetNtryAmt"),// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.DecimalNumberValidator, // Validator
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("CdtDbtInd"),	// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.CreditDebitCodeValidator, // Validator
		0,
		NULL
	}

};

static const ElementDescriptor Separatista::camt_053_001::TotalTransactions2[] = 
{
	{
		SEPARATISTA_TAG("TtlNtries"),	// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::NumberAndSumOfTransactions2)
	},
	{
		SEPARATISTA_TAG("TtlCdtNtries"),// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::NumberAndSumOfTransactions1)
	},
	{
		SEPARATISTA_TAG("TtlDbtNtries"),// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		1,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::NumberAndSumOfTransactions1)
	},
	{
		SEPARATISTA_TAG("TtlNtriesPerBkTxCd"),// TagName
		BranchElement::createElement,	// Creator function
		0,								// Min
		0,								// Max
		NULL,							// Validator
		SEPARATISTA_ELEMENTS(Separatista::camt_053_001::TotalsPerBankTransactionCode2)
	}
};