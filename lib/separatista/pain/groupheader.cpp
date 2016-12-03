/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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
#include "separatista/elementdescriptor.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/pain/groupheader.h"

using namespace Separatista;

static const ElementDescriptor Separatista::pain_008_001::GroupHeader39[] =
{
	{
		SEPARATISTA_TAG("MsgId"),
		LeafElement::createElement,
		1,
		1,
		&Validators.Max35TextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("CreDtTm"),
		LeafElement::createElement,
		1,
		1,
		&Validators.ISODateTimeValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("NbOfTxs"),
		LeafElement::createElement,
		1,
		1,
		&Validators.Max15NumericTextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("CtrlSum"),
		LeafElement::createElement,
		0,
		1,
		&Validators.DecimalNumberValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("InitgPty"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(PartyIdentification32)
	}
};

static const ElementDescriptor Separatista::pain_008_001::GroupHeader55[] = 
{
	{
		SEPARATISTA_TAG("MsgId"),
		LeafElement::createElement,
		1,
		1,
		&Validators.Max35TextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("CreDtTm"),
		LeafElement::createElement,
		1,
		1,
		&Validators.ISODateTimeValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("NbOfTxs"),
		LeafElement::createElement,
		1,
		1,
		&Validators.Max15NumericTextValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("CtrlSum"),
		LeafElement::createElement,
		0,
		1,
		&Validators.DecimalNumberValidator,
		0,
		NULL
	},
	{
		SEPARATISTA_TAG("InitgPty"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(PartyIdentification43)
	}
};	

