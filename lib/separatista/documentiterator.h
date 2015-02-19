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

#ifndef SEPARATISTA_DOCUMENTITERATOR_H
#define SEPARATISTA_DOCUMENTITERATOR_H

#include <ctime>
#include <string>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/leafelement.h"

namespace Separatista
{
	/**
	Class for enumerating a DOMDocument.
	*/
	class SEPARATISTA_EXTERN DOMDocumentIterator
	{
	public:
		/**
			Constructor, sets the internal element pointer to the root document element.
		*/
		DOMDocumentIterator(Separatista::DOMDocument *pDocument);

		/**
			Searches for the next sibbling with the same tag as element. Will call fromDOMDocument on this element if the element was found.
			@throws A MissingElementException if the element wasn't optional and throwing was requested.
		*/
		void fromDOMDocument(Element &element, const Element::ErrorOptions errorOptions);

		/**
		Searches for the next sibbling with the same tag as element. Will call fromDOMDocument on this element if the element was found.
		@throws A MissingElementException if the element wasn't optional and throwing was requested.
		*/
		void fromDOMDocument(LeafElement &leafElement, const Element::ErrorOptions errorOptions);

		/**
			Returns the text value of the current element.
		*/
		const wchar_t *getTextValue() const;

		/**
			Checks if there are no more elements left to iterate
		*/
		bool isDone() const;
	protected:
		DOMElement *findElement(Element &element);

	private:
		DOMElement *m_pElement;
	};

}

#endif // !defined SEPARATISTA_DOCUMENTITERATOR_H
