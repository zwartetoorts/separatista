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

#include <string>
#include <unordered_map>

#include "separatista/separatista.h"
#include "separatista/documentregistry.h"
#include "separatista/exception.h"
#include "separatista/camt/camt.053.001.02.h"
#include "separatista/pain/pain.001.001.03.h"
#include "separatista/pain/pain.008.001.02.h"
#include "separatista/debug/debug.h"

const Separatista::ChildElementDescriptor* Separatista::DocumentRegistry::getDocumentChildElementDescriptor(const wchar_t *pNamespace)
{
	DEBUG_STATIC_METHOD;

	// Insert new supported document types here...
	std::unordered_map<std::wstring, const Separatista::ChildElementDescriptor*> documentCreatorMap(
	{
		{
			Separatista::camt_053_001_02::Namespace, &Separatista::camt_053_001_02::DocumentElementDescriptor
		},
		{
			Separatista::pain_001_001_03::Namespace, &Separatista::pain_001_001_03::DocumentElementDescriptor
		},
		{
			Separatista::pain_008_001_02::Namespace, &Separatista::pain_008_001_02::DocumentElementDescriptor
		},

	});

	const Separatista::ChildElementDescriptor *pDescriptor = documentCreatorMap[pNamespace];
	if (!pDescriptor)
		SEPARATISTA_THROW_EXCEPTION(UnsupportedNamespaceException, TEXT("Unsupported Namespace"), NULL, pNamespace);
	return pDescriptor;
}

