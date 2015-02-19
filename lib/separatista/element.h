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

#ifndef SEPARATISTA_ELEMENT_H
#define SEPARATISTA_ELEMENT_H

#include <ctime>
#include <string>

#include "separatista.h"
#include "xerces_types.h"

namespace Separatista
{
	// Forward decl
	class Element;
	class DOMDocumentIterator;

	class ElementListener
	{
	public:
		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue) = 0;
		virtual void elementDeleted(Element *pElement) = 0;
	};

	class SEPARATISTA_EXTERN Element
	{
	public:
		~Element();

		/**
			Options how to handle errors when reading (fromDOMDocument) or writing (toDOMDocument) 
			Separatista files.
		*/
		enum ErrorOptions
		{
			/// Throw exceptions, default
			ThrowExceptions = 0,
			/// Leave an empty value for the node
			ClearValue,
			/// Accept erronous values
			AcceptValue
		};

		/**
			Abstract method to call to write an element to a DOMDocument.
			@param pDocument The DOMDocument to create the element for.
			@param pParent The DOMElement to append the element to.
			@return Pointer to the new created DOMElement, or NULL
			@see createElement
		*/
		virtual DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions) = 0;

		/**
			Tries to load it's value from the document iterator.
			@param DocumentIterator The document iterator to call to continue reading or get value from.
		*/
		virtual void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions) = 0;

		/**
			Set the elementlistener. Will be notified of changes to the element. If a previous elementlistener was registered, it
			will be returned from this function. It's the caller's choice to store this listener and notify it of changes.
			@param pElementListener The elementlistener to register.
			@return A pointer to a previous registered elementlistener or NULL if none was registered.
			@see ElementListener
			*/
		ElementListener* setElementListener(ElementListener* pElementListener);

		/**
			Returns the tag name
		*/
		const wchar_t* getTag() const;

	protected:
		/**
		Construct a new Element
		@param pTagName The name of the xml tag
		*/
		Element(const wchar_t *pTagName);

		/// Calls a registered ElementListener's elementValueChanged
		void onValueChanged(const wchar_t *pNewValue);
		/// Calls a registerd ElementListener's elementDeleted
		void onDeleted();

		/**
			Creates the element and appends it to it's parent. The xml namespace is taken from it's parent.
			@param pDocument The DOMDocument to create the element for
			@param pParent The parent DOMElement to append the element to.
			@return Pointer to the newly created element, or NULL 
		*/
		DOMElement* createElement(DOMDocument *pDocument, DOMElement *pParent);

		/// Tag name
		const wchar_t *m_pTag;
		
		ElementListener *m_pElementListener;
	};

}

#endif // ifndef SEPARATISTA_ELEMENT_H
