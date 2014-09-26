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
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMException.hpp>

#include "separatista.h"

namespace Separatista
{
	/**
		Class for enumerating a DOMDocument
	*/
	class SEPARATISTA_EXTERN DOMDocumentIterator
	{
	public:
		DOMDocumentIterator(xercesc::DOMDocument *pDocument);

		~DOMDocumentIterator();

		xercesc::DOMElement* getCurrentElement() const;

		xercesc::DOMElement* nextElement();

		/**
			Get the current position. Can be used to check for dead loops.
		*/
		unsigned int getPosition() const;

	private:
		xercesc::DOMNodeIterator *m_pNodeIterator;
		xercesc::DOMNode *m_pCurrentNode;
		unsigned int m_nPos;
	};

	// Forward decl
	class Element;

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
			Abstract method to call to write an element to a DOMDocument.
			@param pDocument The DOMDocument to create the element for.
			@param pParent The DOMElement to append the element to.
			@return Pointer to the new created DOMElement, or NULL
			@see createElement
		*/
		virtual xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent) = 0;

		/**
			Tries to load it's value from the document iterator.
			@param pDocumentIterator The document iterator to read from.
		*/
		virtual void fromDOMDocument(DOMDocumentIterator *pDocumentIterator) = 0;

		/**
			Set the elementlistener. Will be notified of changes to the element. If a previous elementlistener was registered, it
			will be returned from this function. It's the caller's choise to store this listener and notify it of changes.
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
		xercesc::DOMElement* createElement(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		/**
			Checks wether the position in a DOMDocumentIterator matches the current tag name.
		*/
		bool compareTag(const DOMDocumentIterator *DocumentIterator) const;

		/// Tag name
		const wchar_t *m_pTag;
		
		ElementListener *m_pElementListener;
	};

}

#endif // ifndef SEPARATISTA_ELEMENT_H
