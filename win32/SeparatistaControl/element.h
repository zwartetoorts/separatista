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
#include <windows.h>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMException.hpp>

class Element
{
public:
	Element(xercesc::DOMDocument *pDocument, const wchar_t *pName);
	Element(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pName);

	~Element();

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
	void SetDateValue(time_t Value);

protected:
	xercesc::DOMElement *m_pElement;
};

class InitgPty : public Element
{
	InitgPty(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_Nm;
};

class GrpHdr : public Element
{
public:
	GrpHdr(xercesc::DOMDocument *pDocument, Element *pParent);

	Element m_MsgId;
	Element m_CreDtTm;
	Element m_NbOfTxs;
	Element m_CtrlSum;

};

class CstmrDrctDbtInitn : public Element
{
public:
	CstmrDrctDbtInitn(xercesc::DOMDocument *pDocument);

	GrpHdr m_GrpHdr;
};

#endif // ifndef SEPARATISTA_CONTROL_ELEMENT_H
