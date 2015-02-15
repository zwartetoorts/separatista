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

#include "separatista.h"
#include "xerces_types.h"
#include "element.h"
#include "validator.h"

namespace Separatista
{
	class SEPARATISTA_EXTERN LeafElement : public Element
	{
	public:
		LeafElement(const wchar_t *pTagName, const Validator &validator);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

		/**
		Clears the content of the node
		*/
		void clear();

		/**
		Returns the value of the text node
		*/
		const wchar_t* getTextValue() const;

		/**
		Set the value of a text node
		*/
		void setValue(const wchar_t *pValue, const ErrorOptions errorOptions = ThrowExceptions);

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


	protected:
		std::wstring m_value;
		const Validator *m_pValidator;
	};
}


#endif // SEPARATISTA_LEAFELEMENT_H
