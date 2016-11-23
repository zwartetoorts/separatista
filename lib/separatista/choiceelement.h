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

#ifndef SEPARATISTA_CHOICEELEMENT_H
#define SEPARATISTA_CHOICEELEMENT_H

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/exception.h"
#include "separatista/debug/debug.h"
#include "separatista/elementdescriptor.h"

namespace Separatista
{
	class InvalidChoiceException : public Exception
	{
	public:
		InvalidChoiceException(const wchar_t *pMessage) : Exception(pMessage) { };

#ifdef SEPARATISTA_DEBUG
		InvalidChoiceException(const wchar_t *pMessage, const wchar_t *pPath, int line) : Exception(pMessage, pPath, line) { };
#endif
	};

	/**
		ChoiceElements are elements that hold only one child element.
	*/

	class ChoiceElement : public Element
	{
	public:
		~ChoiceElement();
		
		/**
			Iterates over the possible choices and calls fromDOMDocument on the chosen element.
		*/
		void fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions = ThrowExceptions);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pDOMParent, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Creates the element from it's descriptor
		*/
		static Element* createElement(const ElementDescriptor *pElementDescriptor);

		/// @see Element::getElementByTag
		Element* getElementByTag(const wchar_t *pTagName, size_t nIndex = 0) const;

		/** 
			As ChoiceElements hold only one child element, the existing child element is destroyed if a new child element is created.
			@see Element::createElementByTag
		*/
		Element* createElementByTag(const wchar_t *pTagName, size_t nIndex = 0);

		/**
			Destroys the one and only child
			@see Element::destroyElement
		*/
		void destroyElement(Element *pChildElement);

	protected:
		/**
		Constructor
		*/
		ChoiceElement(const ElementDescriptor *pElementDescriptor);

	private:
		/// The chosen element 
		Element *m_pChosenElement;
	};
}
#endif // SEPARATISTA_CHOICEELEMENT_H
