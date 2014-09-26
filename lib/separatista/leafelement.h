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

#ifndef SEPARATISTA_LEAFELEMENT_H
#define SEPARATISTA_LEAFELEMENT_H

#include <ctime>
#include <string>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMException.hpp>

#include "element.h"

namespace Separatista
{
	class SEPARATISTA_EXTERN LeafElement : public Element
	{
	public:
		LeafElement(const wchar_t *pTagName);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		/**
		Clears the content of the node
		*/
		void clear();

		/**
		Returns the value of the text node
		*/
		const XMLCh* getTextValue() const;

		/**
		Set the value of a text node
		*/
		void setValue(const wchar_t *pValue);

		/**
		Returns the value of the text node converted to date
		@return -1 on error
		*/
		time_t getDateValue() const;

		/**
		Set the value of a text node by a time_t
		@param bWithTime Wether the time should be included or not
		*/
		void setValue(const time_t Value, bool bWithTime = false);

		/**
		Get the value of a text node converted to int
		*/
		int getIntValue() const;

		/**
		Set the value of a text node by an int
		*/
		void setValue(const int Value);

		/**
		Get the value of a text node converted to double
		*/
		double getDoubleValue() const;

		/**
		Set the value of a text node conveted to double
		*/
		void setValue(double d);

		/**
		Returns true if the element text is empty
		*/
		bool isEmpty() const;


	protected:
		std::wstring m_value;
	};
}
#endif // SEPARATISTA_LEAFELEMENT_H
