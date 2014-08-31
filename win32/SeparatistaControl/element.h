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

// Forward decl
class Element;

class ElementListener
{
public:
	virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue) = 0;
	virtual void elementDeleted(Element *pElement) = 0;
};

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
		Set the elementlistener. Will be notified of changed to the element. If a previous elementlistener was registered, it 
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

	/**
		Clears the content of the node
	*/
	void Delete();

	/**
		Returns the value of the text node
	*/
	const XMLCh* getTextValue() const;

	/**
		Set the value of a text node
	*/
	void setValue(const XMLCh *pValue);

	/**
		Returns the value of the text node converted to date
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
		Returns true of the element text is empty
	*/
	bool empty() const;

protected:
	/// Calls a registered ElementListener's elementValueChanged
	void onValueChanged();
	/// Calls a registerd ElementListener's elementDeleted
	void onDeleted();

	/// Tag name
	const wchar_t *m_pTag;
	std::wstring m_value;
	ElementListener *m_pElementListener;
};


#endif // ifndef SEPARATISTA_CONTROL_ELEMENT_H
