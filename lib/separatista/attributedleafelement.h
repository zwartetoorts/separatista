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

#ifndef SEPARATISTA_ATTRIBUTEDLEAFELEMENT_H
#define SEPARATISTA_ATTRIBUTEDLEAFELEMENT_H

#include <map>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/leafelement.h"
#include "separatista/elementdescriptor.h"

namespace Separatista
{
	/**
	LeafElements are elements that hold a value.
	*/
	class SEPARATISTA_EXTERN AttributedLeafElement : public LeafElement
	{
	public:
		/**
		Creates the element from it's descriptor
		*/
		static Element* createElement(const ElementDescriptor* pElementDescriptor);


		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions) const;

		void fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions = ThrowExceptions);

		/// @see Element::getAttributeValue
		const wchar_t* getAttributeValue(const wchar_t *pAttributeName) const;

		/// @see Element::setAttributeValue
		void setAttributeValue(const wchar_t *pAttributeName, const wchar_t *pValue);
	protected:
		/// Protected constructor
		AttributedLeafElement(const ElementDescriptor* pElementDescriptor);

		std::map<std::wstring, std::wstring> m_Attributes;
	};
}


#endif // SEPARATISTA_ATTRIBUTEDLEAFELEMENT_H
