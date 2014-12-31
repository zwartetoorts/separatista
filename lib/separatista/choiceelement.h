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

#include <array>
#include <ctime>
#include <string>
#include <initializer_list>
#include <algorithm>

#include "separatista.h"
#include "xerces_types.h"
#include "element.h"
#include "exception.h"

namespace Separatista
{
	class InvalidChoiceException : public Exception
	{
	public:
		InvalidChoiceException() {};

#ifdef SEPARATISTA_DEBUG
		InvalidChoiceException(const wchar_t *pPath, int line) : Exception(pPath, line) {};
#endif
	};

	/**
		Choice elements require to choose a child element to be written on save.
		Separatista subclasses always have a default choice set in their constructor.
	*/

	template <size_t T>
	class ChoiceElement : public Element
	{
	public:
		ChoiceElement(const wchar_t *pTagName, std::initializer_list<Element*> pChoices) :
			Element(pTagName)
			{
				m_pChosenElement = NULL;
				std::copy(pChoices.begin(), pChoices.end(), m_pChoices.begin());
			};

		/**
			@return The element created or NULL if no element was choosen.
		*/

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent)
		{
			if (!m_pChosenElement)
				return NULL;

			DOMElement *pElement = createElement(pDocument, pParent);

			if (pElement)
			{
				m_pChosenElement->toDOMDocument(pDocument, pElement);
			}

			return pElement;
		};

		void fromDOMDocument(DOMDocumentIterator *pDocumentIterator)
		{
			if (compareTag(pDocumentIterator))
			{
				pDocumentIterator->nextElement();
				for (auto it = m_pChoices.begin(); it != m_pChoices.end(); it++)
				{
					if ((*it)->compareTag(pDocumentIterator))
					{
						m_pChosenElement = *it;
						m_pChosenElement->fromDOMDocument(pDocumentIterator);
						break;
					}
				}
			}
		};
		
		/**
			Choose the child element to be the chosen one.
			@param pChildElement Make sure this actually a child element of the choice element. Can be NULL,
			this means this element won't be outputted on toDOMDocument.
			@throws InvalidChoiceException if the chosen element isn't a child of this element.
		*/
		void choose(Element *pChildElement)
		{
			for (auto it = m_pChoices.begin(); it != m_pChoices.end(); it++)
			{
				if (*it == pChildElement)
				{
					m_pChosenElement = pChildElement;
					return;
				}
			}

			throw InvalidChoiceException(SEPARATISTA_EXCEPTION);
		};

		/**
			Returns the chosen element.
			@return The chosen element or NULL if no choice was registered.
		*/
		Element* getChoice()
		{
			return m_pChosenElement;
		};

	private:
		/// The chosen element 
		Element *m_pChosenElement;
		/// Array containing all choices
		std::array<Element*, T> m_pChoices;

	};
}
#endif // SEPARATISTA_CHOICEELEMENT_H
