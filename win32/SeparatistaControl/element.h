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

#ifndef SEPARATISTA_CONTROL_ELEMENT_H
#define SEPARATISTA_CONTROL_ELEMENT_H

#include <ctime>
#include <string>
#include <windows.h>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMException.hpp>

class Element
{
public:
	Element(const wchar_t *pName);

	~Element();

	/**
		Appends the actual element to the DOMDocument.
		@param bForce If true the element will always be created, even if no value was set.
		@return Pointer to the new created DOMElement.
	*/
	xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent, bool bForce = false);

	/**
		Returns the value of the text node
	*/
	const XMLCh* GetTextValue() const;

	/**
		Set the value of a text node
	*/
	void SetTextValue(const XMLCh *pValue);

	/**
		Returns the value of the text node converted to date
	*/
	time_t GetDateValue() const;

	/**
		Set the value of a text node by a time_t
	*/
	void SetDateValue(const time_t Value);

	/**
		Get the value of a text node converted to int
	*/
	int GetIntValue() const;

	/**
		Set the value of a text node by an int
	*/
	void SetIntValue(const int Value);

protected:
	/// Tag name
	const wchar_t *m_pTag;
	std::wstring m_value;
};


#endif // ifndef SEPARATISTA_CONTROL_ELEMENT_H
