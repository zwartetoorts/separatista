/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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

#include <windows.h>
#include <separatista/separatista.h>
#include <separatista/element.h>
#include "separatista/debug/debug.h"

#include "dispatch.h"

#ifndef SEPARATISTA_CONTROL_ELEMENT_H
#define SEPARATISTA_CONTROL_ELEMENT_H

// {006D9323-D6C2-4D53-9072-9AE379CEF7DE}
DEFINE_GUID(IID_ELEMENT ,
	0x6d9323, 0xd6c2, 0x4d53, 0x90, 0x72, 0x9a, 0xe3, 0x79, 0xce, 0xf7, 0xde);

// {0F74285B-C429-4A58-95AC-B1A05B856530}
DEFINE_GUID(CLSID_ELEMENT ,
	0xf74285b, 0xc429, 0x4a58, 0x95, 0xac, 0xb1, 0xa0, 0x5b, 0x85, 0x65, 0x30);


struct IElement : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IElement
	STDMETHOD(GetTagName)(BSTR *pTagName) PURE;
	STDMETHOD(GetValue)(VARIANT *pValue) PURE;
	STDMETHOD(SetValue)(BSTR Value) PURE;
	STDMETHOD(GetDateValue)(DATE *pDateValue) PURE;
	STDMETHOD(SetDateValue)(DATE DateValue) PURE;
	STDMETHOD(GetElementByTagName)(BSTR TagName, UINT index, IElement **ppElement) PURE;
	STDMETHOD(CreateElementByTagName)(BSTR TagName, UINT index, IElement **ppElement) PURE;
	STDMETHOD(DestroyElement)(IElement *pChildElement) PURE;
	STDMETHOD(GetAttributeValue)(BSTR AttributeName, BSTR *pValue) PURE;
	STDMETHOD(SetAttributeValue)(BSTR AttributeName, BSTR Value) PURE;
	

};

struct __declspec(uuid("{006D9323-D6C2-4D53-9072-9AE379CEF7DE}")) IElement;

/**
	Elements are interfaces to the Separatista library Element types. They support error information.
	They keep track of their Separatista counterparts by being elementlisteners.
*/
class Element : public SepaControlDispatch<IElement>, public Separatista::ElementListener
{
public:
	/**
		Creates an Element with a Separatista element
	*/
	Element(Separatista::Element *pElement);

	// COM methods
	// Subclass for ISupportErrorInfo
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject);

	// Element Methods
	STDMETHOD(GetTagName)(BSTR *pTagName);
	STDMETHOD(GetValue)(VARIANT *pValue);
	STDMETHOD(SetValue)(BSTR Value);
	STDMETHOD(GetDateValue)(DATE *pDateValue);
	STDMETHOD(SetDateValue)(DATE DateValue);
	STDMETHOD(GetElementByTagName)(BSTR TagName, UINT index, IElement **ppElement);
	STDMETHOD(CreateElementByTagName)(BSTR TagName, UINT index, IElement **ppElement);
	STDMETHOD(DestroyElement)(IElement *pChildElement);
	STDMETHOD(GetAttributeValue)(BSTR AttributeName, BSTR *pValue);
	STDMETHOD(SetAttributeValue)(BSTR AttributeName, BSTR Value);
	

	// Elementlistener
	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pValue);
	void elementCreated(Separatista::Element *pParentElement, Separatista::Element *pChildElement);
	void elementDeleted(Separatista::Element *pParentElement, Separatista::Element *pChildElement);

protected:
	/**
	Destructor
	*/
	~Element();

	/**
		Returns  the Separatista element.
		@return The Separatista element.
	*/
	Separatista::Element *getElement() const;

	/**
		Set the Separatista element. Does not check for existing element, nor does it delete it.
		@param pElement The element to set.
	*/
	void setElement(Separatista::Element *pElement);

private:
	Separatista::Element *m_pElement;
};

class __declspec(uuid("{0F74285B-C429-4A58-95AC-B1A05B856530}")) Element;

#endif // #define SEPARATISTA_CONTROL_ELEMENT_H
