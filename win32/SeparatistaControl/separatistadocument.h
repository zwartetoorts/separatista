/***************************************************************************
*   Copyright (C) 2013 by Okkel Klaver   *
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

#include <vector>
#include <windows.h>
#include <separatista/separatista.h>
#include "separatista/separatistadocument.h"
#include "separatista/debug/debug.h"

#include "dispatch.h"
#include "element.h"

#ifndef SEPARATISTA_CONTROL_SEPARATISTADOCUMENT_H
#define SEPARATISTA_CONTROL_SEPARATISTADOCUMENT_H

// {4B8AC337-5E17-454D-A7EC-8955B07B99CC}
DEFINE_GUID(IID_SEPARATISTADOCUMENT ,
	0x4b8ac337, 0x5e17, 0x454d, 0xa7, 0xec, 0x89, 0x55, 0xb0, 0x7b, 0x99, 0xcc);

// {A3142FEC-FB2E-4715-B5DF-C4F7844D2956}
DEFINE_GUID(CLSID_SEPARATISTADOCUMENT,
	0xa3142fec, 0xfb2e, 0x4715, 0xb5, 0xdf, 0xc4, 0xf7, 0x84, 0x4d, 0x29, 0x56);

struct ISeparatistaDocument : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;
	
	// ICustomerDirectDebitInitiation
	STDMETHOD(GetNamespace)(BSTR *pNamespace) PURE;
	STDMETHOD(SetNamespace)(BSTR NameSpace) PURE;
	STDMETHOD(GetRootElement)(IElement **ppElement) PURE;
	STDMETHOD(Save)(LONG hWnd, Separatista::IOErrorCode *pErrorCode) PURE;
	STDMETHOD(SaveAs)(BSTR Path, Separatista::IOErrorCode *pErrorCode) PURE;
	STDMETHOD(Open)(LONG hWnd, Separatista::IOErrorCode *pErrorCode) PURE;
	STDMETHOD(OpenFrom)(BSTR Path, Separatista::IOErrorCode *pErrorCode) PURE;

}; 

struct __declspec(uuid("{4B8AC337-5E17-454D-A7EC-8955B07B99CC}")) ISeparatistaDocument;

/**
	
*/
class SeparatistaDocument : public SepaControlDispatch<ISeparatistaDocument>
{
public:
	/**
		Constructor for creating new documents
	*/
	SeparatistaDocument();

	// COM methods
	// Subclass for ISupportErrorInfo
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject);

	STDMETHOD(GetNamespace)(BSTR *pNamespace);
	STDMETHOD(SetNamespace)(BSTR NameSpace);
	STDMETHOD(GetRootElement)(IElement **ppElement);
	STDMETHOD(Save)(LONG hWnd, Separatista::IOErrorCode *pErrorCode);
	STDMETHOD(SaveAs)(BSTR Path, Separatista::IOErrorCode *pErrorCode);
	STDMETHOD(Open)(LONG hWnd, Separatista::IOErrorCode *pErrorCode);
	STDMETHOD(OpenFrom)(BSTR Path, Separatista::IOErrorCode *pErrorCode);

protected:
	/**
	Destructor
	*/
	~SeparatistaDocument();

private:
	Separatista::SeparatistaDocument *m_pSeparatistaDocument;
	std::wstring m_Namespace;
};

class __declspec(uuid("{A3142FEC-FB2E-4715-B5DF-C4F7844D2956}")) SeparatistaDocument;

#endif // #define SEPARATISTA_CONTROL_SEPARATISTADOCUMENT_H
