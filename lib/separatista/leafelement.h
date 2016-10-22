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

#ifndef SEPARATISTA_LEAFELEMENT_H
#define SEPARATISTA_LEAFELEMENT_H

#include <ctime>
#include <string>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/validator.h"
#include "separatista/elementdescriptor.h"

namespace Separatista
{
	/**
		LeafElements are elements that hold a value.
	*/
	class SEPARATISTA_EXTERN LeafElement : public Element
	{
	public:
		/**
		Creates the element from it's descriptor
		*/
		static Element* createElement(const ElementDescriptor* pElementDescriptor);


		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMElement *pDOMElement, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Returns the value of the text node
		*/
		const wchar_t* getTextValue() const;

		/**
		Set the value of a text node
		*/
		void setValue(const wchar_t *pValue, const ErrorOptions errorOptions = ThrowExceptions);

		

		
	protected:
		/// Protected constructor
		LeafElement(const ElementDescriptor* pElementDescriptor);

		std::wstring m_value;
	};
}


#endif // SEPARATISTA_LEAFELEMENT_H
