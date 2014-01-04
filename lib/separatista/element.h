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
	Element();
	/**
	Custructor setting document and element
	*/
	Element(DOMDocument *pDocument, DOMElement *pElement);
	/**
	Custructor setting document and getting/creating child element of pElement. Will set the internal DOMElement to the gotten/newly created element.
	@param pDocument The document
	@param @pElement The element to get/create the child element for
	@param pTagName The name of the tag to get
	@param create Flag to create the element if not found or not
	*/
	Element(DOMDocument *pDocument, DOMElement *pElement, const wchar_t *pTagName, bool create = false);

	void setDOMDocument(DOMDocument *pDocument);

	/**
	Gets a child element. Creates the child element if requested.
	*/
	DOMElement* getChildElement(const wchar_t *pTagName, bool create = false);
protected:
	DOMElement* getDOMElement() const;
	void setDOMElement(DOMElement *pElement);
private:
	DOMDocument *m_pDocument;
	DOMElement *m_pDOMElement;
};


};

#endif // !defined SEPARATISTA_ELEMENT_H
