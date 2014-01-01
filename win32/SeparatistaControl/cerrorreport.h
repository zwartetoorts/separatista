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

#include <windows.h>
#include <comutil.h>

#include "separatista.h"
#include "dispatch.h"

#ifndef SEPARATISTA_CERRORREPORT_H
#define SEPARATISTA_CERRORREPORT_H

// {DD279C98-8CF9-47D4-94BD-D54DDB2E715B}
DEFINE_GUID(IID_ERRORREPORT ,
	0xdd279c98, 0x8cf9, 0x47d4, 0x94, 0xbd, 0xd5, 0x4d, 0xdb, 0x2e, 0x71, 0x5b);

// {89F10D64-9F8A-4B07-B749-266158D4407A}
DEFINE_GUID(CLSID_CERRORREPORT,
	0x89f10d64, 0x9f8a, 0x4b07, 0xb7, 0x49, 0x26, 0x61, 0x58, 0xd4, 0x40, 0x7a);

struct IErrorReport : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IErrorReport methods
	STDMETHOD(Count)(long *plCount) PURE;
	STDMETHOD(Item)(VARIANT vIndex, BSTR *pMessage) PURE;
	STDMETHOD(_NewEnum)(IUnknown **ppUnk) PURE;
};

struct __declspec(uuid("{DD279C98-8CF9-47D4-94BD-D54DDB2E715B}")) IErrorReport;

/**
COM representation of an IBAN class.
Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released.
Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child
objects in the parent CMT940SDocument.
*/
class CErrorReport : public SepaControlDispatch<IErrorReport>
{
public:
	/**
	@see SepaControllDispatch
	*/
	CErrorReport(IUnknown *pParent = NULL);

	// COM methods
	STDMETHOD(Count)(long *plCount);
	STDMETHOD(Item)(VARIANT vIndex, BSTR *pMessage);
	STDMETHOD(_NewEnum)(IUnknown **ppUnk);

	CErrorReport& operator =(Separatista::ErrorReport *pErrorReport);

protected:
	_bstr_t formatErrorMessage();
private:
	Separatista::ErrorReport *m_pErrorReport;
};

class __declspec(uuid("{89F10D64-9F8A-4B07-B749-266158D4407A}")) CErrorReport;

#endif // !defined SEPARATISTA_CERRORREPORT_H
