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

#ifndef SEPARATISTA_BRANCHELEMENT_H
#define SEPARATISTA_BRANCHELEMENT_H

#include <string>
#include <map>
#include <iterator>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"

namespace Separatista
{
	/**
		BranchElements are elements that hold child elements. 
	*/
	class SEPARATISTA_EXTERN BranchElement : public Element
	{
	public:
		/**
		Creates the element from it's descriptor
		*/
		static Element* createElement(const ChildElementDescriptor* pChildElementDescriptor);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions) const;

		void fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions = ThrowExceptions);

		/// @see Element::getElementByTag
		Element* getElementByTag(const wchar_t *pTagName, size_t nIndex = 0) const;

		/// @see Element::createElementByTag
		Element* createElementByTag(const wchar_t *pTagName, size_t nIndex = 0);

		/// @see Element::getAllByTagName
		TagKeyRange getAllByTagName(const wchar_t *pTagName);

		/// @see Element::destroyElement
		void destroyElement(Element *pElement);

	protected:
		BranchElement(const ChildElementDescriptor *pChildElementDescriptor);

		~BranchElement();

	private:
		TagKeyMap m_childElements;
	};
}
#endif // SEPARATISTA_BRANCHELEMENT_H
