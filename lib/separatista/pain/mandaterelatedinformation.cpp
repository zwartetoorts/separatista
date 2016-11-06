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
#include "separatista/pain/mandaterelatedinformation.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

static const ElementDescriptor Separatista::pain_008_001::MandateRelatedInformation8[] =
{
	{
		SEPARATISTA_TAG("MndtId"),		// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.Max35TextValidator, // Validator
		0,								// Number of child elements
		NULL							// Child elements
	},
	{
		SEPARATISTA_TAG("DtOfSgntr"),	// TagName
		LeafElement::createElement,		// Creator function
		0,								// Min
		1,								// Max
		&Validators.ISODateValidator,	// Validator
		0,								// Number of child elements
		NULL							// Child elements
	}
};

