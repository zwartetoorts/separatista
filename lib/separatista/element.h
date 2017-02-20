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
#include <map>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/debug/debug.h"
#include "separatista/elementdescriptor.h"
#include "separatista/exception.h"

namespace Separatista
{
	// Forward decl
	class ElementException;
	class UnsupportedElementException;

	/**
		Elementlistener interface
	*/
	class ElementListener
	{
	public:
		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue) = 0;
		virtual void elementCreated(Element *pParent, Element *pChild) = 0;
		virtual void elementDeleted(Element *pElement) = 0;
	};

	
	class SEPARATISTA_EXTERN Element
	{
	public:
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
		virtual xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pDOMParent, const ErrorOptions errorOptions = ThrowExceptions) const = 0;

		/**
			Tries to load it's value from the document element.
			@param DocumentIterator The document iterator to call to continue reading or get value from.
		*/
		virtual void fromDOMDocument(xercesc::DOMElement *pDOMElement, const ErrorOptions errorOptions = ThrowExceptions) = 0;

		/**
			Add an elementlistener. Will be notified of changes to the element.
			@param pElementListener The elementlistener to register.
			@see ElementListener
			*/
		void addElementListener(ElementListener* pElementListener);

		/**
			Remove a registered elementlistener.
			@param pElementListener The ElementListener to remove.
			@see ElementListener
		*/
		void removeElementListener(ElementListener* pElementListener);

		/**
			Returns the tag name
		*/
		const wchar_t* getTag() const;

		/**
			Returns the child element by tag name and index.
			@return A pointer to the child element or NULL if not present or unsupported.
			@throws ElementException if the element doesn't support having child elements.
		*/
		virtual Element* getElementByTag(const wchar_t *pTagName, size_t nIndex = 0) const;

		/**
			Returns or creates the child element by tag name. If the element already exists, this function return the existing element.
			If not, it will create the element.
			@return A pointer to the child element. Will not return NULL. If the element isn't supported an UnsupportedTagException is thrown.
			@throws ElementException if the element doesn't support having child elements.
			@throws UnsupportedTagException if the requested tag isn't supported by Separatista
		*/
		virtual Element* createElementByTag(const wchar_t *pTagName, size_t nIndex = 0);

		/**
			Destroys the child element.
			@throws ElementException if the element doesn't support having child elements.
		*/
		virtual void destroyElement(Element *pChildElement);

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

		/**
			Get the element's attribute value
			@param pAttributeName The name of the attribute
			@return The value as text or NULL
			@throws ElementException if the element doesn't support having attributes.
		*/
		virtual const wchar_t* getAttributeValue(const wchar_t *pAttributeName) const;

		/**
			Set the element's attribute value
			@param pAttributeName The name of the attribute
			@param pValue The (new) value to set
			@throws ElementException if the elements doesn't support having attributes.
		*/
		virtual void setAttributeValue(const wchar_t *pAttributeName, const wchar_t *pValue);

		/**
		Returns the value of the text node converted to date
		@return -1 on error
		*/
		time_t getDateValue() const;

		/**
		Set the value of a text node by a time_t
		@param bWithTime Wether the time should be included or not
		*/
		void setValue(const time_t Value, bool bWithTime = false, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Get the value of a text node converted to int
		*/
		int getIntValue() const;

		/**
		Set the value of a text node by an int
		*/
		void setValue(const int Value, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Get the value of a text node converted to double
		*/
		double getDoubleValue() const;

		/**
		Set the value of a text node conveted to double
		*/
		void setValue(const double d, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Returns true if the element text is empty
		*/
		bool isEmpty() const;

		/**
			Key container class with custom sort and compare functions. TagKey are ordered by the pBranchElementDescriptor's tag order first
			and second by their index.
		*/
		class TagKey
		{
		public:
			/// Constructor
			TagKey(const wchar_t *pTagName, size_t  nIndex, const ElementDescriptor *pBranchElementDescriptor);

			bool operator <(const TagKey &Other) const;

			bool operator ==(const TagKey &Other) const;

			/**
				Public available method for key hashing.
			*/
			static unsigned int HashKey(const wchar_t *pTagName);

			const wchar_t* getTagName() const;
			
			unsigned int getHash() const;

		private:
			size_t m_nIndex;
			const wchar_t *m_pTagName;
			unsigned int m_nHash;
			const ElementDescriptor *m_pBranchElementDescriptor;
		};

		typedef std::map<const TagKey, Element*> TagKeyMap;

		typedef struct
		{
			TagKeyMap::const_iterator m_begin;
			TagKeyMap::const_iterator m_end;
		} TagKeyRange;

		/**
			Returns a range containing a begin iterator and an end iterator.
			@throws ElementException If this element doesn't support having child elements.
		*/
		virtual TagKeyRange getAllByTagName(const wchar_t *pTagName);

	protected:
		/**
			Construct a new Element
			@param pElementDescriptor The element descriptor to load the element from.
		*/
		Element(const ChildElementDescriptor* pChildElementDescriptor);

		/**
			Protected destructor to protect the object from being destroyed by non Element derived classes.
		*/
		virtual ~Element();

		/**
			Get the parent element
			@retrn The parent element or NULL if no parent was found in the ElementDescriptor
		*/
		Element* getParentElement() const;

		/**
			Method to make it possible for derived classes to delete Elements. 
			Calls pChildElement->onElementDeleted()
			@see Element::onElementDeleted
		*/
		static void deleteElement(Element *pChildElement);

		/// Calls a registered ElementListener's elementValueChanged
		void onElementValueChanged(const wchar_t *pNewValue);

		/// Calls a registered ElementListener's elementCreated
		void onElementCreated(Element *pChildElement);

		/// Calls a registered ElementListener's elementDeleted
		void onElementDeleted();

	private:
		/// ChildElementDescriptor
		const ChildElementDescriptor *m_pChildElementDescriptor;
		
		/// ElementListeners
		std::vector<ElementListener*> m_ElementListeners;

		/// Parent element
		Element *m_pParent;

		/// Tag
		const wchar_t *m_pTag;

		friend class SeparatistaDocument;
	};
}

#endif // ifndef SEPARATISTA_ELEMENT_H
