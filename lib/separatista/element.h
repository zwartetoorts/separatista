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
#include <Windows.h>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "elementdescriptor.h"
#include "exception.h"

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

	/// Invalid value exception, thrown when an element method called doesn't belong to the element type
	class SEPARATISTA_EXTERN ElementException : public Exception
	{
	public:
		ElementException(const wchar_t *pMessage, const Element *pSource) : 
			Exception(pMessage)
		{
			m_pSource = pSource;
		};

#ifdef SEPARATISTA_DEBUG
		ElementException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, const Element *pSource) :
			Exception(pMessage, pPath, nLine)
		{
			m_pSource = pSource;
		};
#endif

		/// Returns the target element 
		const Element* getSourceElement() const
		{
			return m_pSource;
		};

	private:
		const Element *m_pSource;
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
			Get the ElementDescriptor for this element
		*/
		const ElementDescriptor* getElementDescriptor() const;
		
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

		/**
			Returns the child element by tag name.
			@return A pointer to the child element or NULL if not present or unsupported.
			@throws ElementException if the element doesn't have any child elements.
		*/
		virtual Element* getElementByTag(const wchar_t *pTagName, size_t nIndex = 0) const;

		/**
			Returns or creates the child element by tag name. If the element already exists, this function return the existing element.
			If not, it will create the element.
			@return A pointer to the child element. Will not return NULL, unless the the tag isn't known or supported.
			@throws ElementException if the element doesn't have any child elements.
		*/
		virtual Element* createElementByTag(const wchar_t *pTagName, size_t nIndex = 0);

		/**
			Get the element's value as text.
			@returns A pointer to the text value or NULL if no value was set.
			@throws ElementException if the element doesn't support having values.
		*/
		virtual const wchar_t* getTextValue() const;

		/**
			Set the element's value as text.
			@throws ElementException if the element doesn't support having values.
		*/
		virtual void setValue(const wchar_t *pValue, const ErrorOptions errorOptions = ThrowExceptions);

	protected:
		/**
		Construct a new Element
		@param pElementDescriptor The element descriptor to load the element from.
		*/
		Element(const ElementDescriptor* pElementDescriptor);

		/// Calls a registered ElementListener's elementValueChanged
		void onValueChanged(const wchar_t *pNewValue);
		/// Calls a registerd ElementListener's elementDeleted
		void onDeleted();

	private:
		/// ElementDescriptor
		const ElementDescriptor *m_pElementDescriptor;
		
		/// ElementListener
		ElementListener *m_pElementListener;
	};
}

#endif // ifndef SEPARATISTA_ELEMENT_H
