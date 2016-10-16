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

#ifndef SEPARATISTA_ELEMENTDESCRIPTOR_H
#define SEPARATISTA_ELEMENTDESCRIPTOR_H

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"

#define SEPARATISTA_COUNTOFELEMENTS(name) sizeof(name) / sizeof(ElementDescriptor), name

namespace Separatista
{
	// Forward decl
	class Element;
	class Validator;

	struct ElementDescriptor
	{
		/// The tag name of the element
		const wchar_t *m_pTag;
		/// Element creator function
		Element* (*m_pfCreateElement)(const ElementDescriptor*);
		/// Minimal presence of the element
		size_t m_nMin;
		/// Maximum presence of the element, 0 = infinite
		size_t m_nMax;
		/// Data validation class
		const Validator *m_pValidator;
		/// Number of child elements
		size_t m_nElementCount;
		/// Child elements
		const ElementDescriptor *m_pElements;
	};
}

#endif // !defined SEPARATISTA_ELEMENTDESCRIPTOR_H
