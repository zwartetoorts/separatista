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

#include "windows.h"

#include "dispatch.h"
#include "iban/iban.h"

#ifndef SEPARATISTA_CONTROL_IBAN_H
#define SEPARATISTA_CONTROL_IBAN_H

// {3CDADD67-109C-49b4-9B1B-5C10B7121EB6}
DEFINE_GUID(IID_IBAN, 
0x3cdadd67, 0x109c, 0x49b4, 0x9b, 0x1b, 0x5c, 0x10, 0xb7, 0x12, 0x1e, 0xb6);

// {2BD7342E-B12D-45b0-A5D6-ADF118386112}
DEFINE_GUID(CLSID_CIBAN, 
0x2bd7342e, 0xb12d, 0x45b0, 0xa5, 0xd6, 0xad, 0xf1, 0x18, 0x38, 0x61, 0x12);

struct IIBAN : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IIBAN
	STDMETHOD(GetIBAN)(BSTR *pIBAN) PURE;
	STDMETHOD(SetIBAN)(BSTR iban) PURE;
	STDMETHOD(Check)(VARIANT_BOOL *pValid) PURE;
};

struct __declspec(uuid("{3CDADD67-109C-49b4-9B1B-5C10B7121EB6}")) IIBAN;

/**
	COM representation of an IBAN class. 
	Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released. 
	Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child 
	objects in the parent CMT940SDocument. 
*/
class CIBAN : public SepaControlDispatch<IIBAN>
{
public:
	/**
		@see SepaControllDispatch
	*/
	CIBAN(IUnknown *pParent = NULL);

	/**
		Destructor
	*/
	~CIBAN();

	// COM methods
	STDMETHOD(GetIBAN)(BSTR *pIBAN);
	STDMETHOD(SetIBAN)(BSTR iban);
	STDMETHOD(Check)(VARIANT_BOOL *pValid);

	/**
		Assignment operator, will set the internal pointer to the recordset
	*/
	CIBAN& operator = (Separatista::IBAN *pIBAN);

private:
	Separatista::IBAN *m_pIBAN;
	bool m_bOwnIBAN;
};

class __declspec(uuid("{2BD7342E-B12D-45b0-A5D6-ADF118386112}")) CIBAN;

#endif // !defined SEPARATISTA_CONTROL_IBAN_H