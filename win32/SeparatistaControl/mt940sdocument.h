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

#ifndef SEPARATISTA_MT940SDOCUMENT_H
#define SEPARATISTA_MT940SDOCUMENT_H

#include <windows.h>
#include <oleauto.h>

#include "mt940s/mt940s.h"
#include "dispatch.cpp"

// {051E4622-F5B0-40c4-81BC-F12EB35F1868}
DEFINE_GUID(IID_IMT940SDocument, 
0x51e4622, 0xf5b0, 0x40c4, 0x81, 0xbc, 0xf1, 0x2e, 0xb3, 0x5f, 0x18, 0x68);

// {6DF05A76-0582-415a-9B96-163F76914250}
DEFINE_GUID(CLSID_CMT940SDocument, 
0x6df05a76, 0x582, 0x415a, 0x9b, 0x96, 0x16, 0x3f, 0x76, 0x91, 0x42, 0x50);

struct IMT940SDocument : public IDispatch
{
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	STDMETHOD(Open)(BSTR Path, Separatista::MT940SDocument::OpenStatus *pStatus) PURE;
};

struct __declspec(uuid("{051E4622-F5B0-40c4-81BC-F12EB35F1868}")) IMT940SDocument;

class CMT940SDocument : public SepaControlDispatch<IMT940SDocument>
{
public:
	STDMETHOD(Open)(BSTR Path, Separatista::MT940SDocument::OpenStatus *pStatus);

private:
	Separatista::MT940SDocument m_MT940SDocument;
};

class __declspec(uuid("{6DF05A76-0582-415a-9B96-163F76914250}")) CMT940SDocument;

#endif // ifndef SEPARATISTA_MT940SDOCUMENT_H