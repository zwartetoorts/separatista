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

#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE;

namespace Separatista
{

class Element
{
public:
	/**
	Constructor setting document and getting child element of pParent. Will set the internal DOMElement to the found element.
	@param pDocument The document
	@param pParent The parent element, can be NULL
	@param pElement The element to set, can be NULL.
	@param pTagName If pElement is NULL, pParent->getChildElement(pTagName) is used.
	*/
	Element(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t* pTagName = NULL);

	/**
	Gets a child element. Creates the child element if requested and inserts it as sorted by given order.
	@index The Nth occurance of this element.
	@see getOrder
	*/
	DOMElement* getChildElement(unsigned int index, const wchar_t *pTagName, bool create = false);

	DOMElement* getChildElement(const wchar_t *pTagName, bool create = false);

	/**
	Get the child element text content.
	*/
	const wchar_t* getChildElementValue(const wchar_t *pTagName);

	/**
	Gets the child element at index text content, useful for child elements that can occur more than once
	*/
	const wchar_t* getChildElementValue(unsigned int index, const wchar_t* pTagName);

	/**
	Set the child element text content, creates the element if it doensn't exist.
	*/
	void setChildElementValue(const wchar_t *pTagName, const wchar_t *pValue);

	/**
	Sets the child element at index text content, useful for child elements that can occur more than once
	*/
	void setChildElementValue(unsigned int index, const wchar_t* pTagName, const wchar_t *pValue);

	/**
	Gets a DOMNodeList of child elements, just like xerces
	*/
	DOMNodeList* getElementsByTagName(const wchar_t *pTagName);

protected:
	DOMElement* getDOMElement() const;
	operator DOMElement* ();

	/**
	Returns the order of child elements as a NULL terminated array. If it returns NULL 
	no ordering is applied.
	*/
	virtual const wchar_t* const* getOrder() = 0;

	virtual const wchar_t* getTagName() = 0;

private:
	/**
	Insert a child element for pParent ordering child elements as indicated by getOrder
	*/
	void insertChildElement(DOMElement *pElement);

	DOMDocument *m_pDocument;
	Element *m_pParent;
	DOMElement *m_pDOMElement;
};


};

#endif // !defined SEPARATISTA_ELEMENT_H
