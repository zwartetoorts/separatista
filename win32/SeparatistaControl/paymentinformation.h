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

#include <windows.h>
#include <xercesc/dom/DOMDocument.hpp>

#include "dispatch.h"
#include "element.h"
#include "customerdirectdebitinitiation.h"

#ifndef SEPARATISTA_CONTROL_PAYMENTINFORMATION_H
#define SEPARATISTA_CONTROL_PAYMENTINFORMATION_H

// {9D52C4C2-B5FF-43E0-9FAC-600AF2986686}
DEFINE_GUID(IID_IPaymentInformation ,
	0x9d52c4c2, 0xb5ff, 0x43e0, 0x9f, 0xac, 0x60, 0xa, 0xf2, 0x98, 0x66, 0x86);

// {CBDAC56C-5A90-443F-9511-D3F3B5AC3CF7}
DEFINE_GUID(CLSID_PAYMENTINFORMATION,
	0xcbdac56c, 0x5a90, 0x443f, 0x95, 0x11, 0xd3, 0xf3, 0xb5, 0xac, 0x3c, 0xf7);



struct IPaymentInformation : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;

	// IPaymentInformation


};

struct __declspec(uuid("{9D52C4C2-B5FF-43E0-9FAC-600AF2986686}")) IPaymentInformation;

/**
	COM representation of an IBAN class.
	Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released.
	Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child
	objects in the parent CMT940SDocument.
*/
class PaymentInformation : public SepaControlDispatch<IPaymentInformation>
{
public:
	/**
	@see SepaControllDispatch
	*/
	PaymentInformation(CustomerDirectDebitInitiation *pParent, xercesc::DOMDocument *pDomDocument);

private:
	xercesc::DOMDocument *m_pDomDocument;
};

class __declspec(uuid("{CBDAC56C-5A90-443F-9511-D3F3B5AC3CF7}")) PaymentInformation;

#endif // SEPARATISTA_CONTROL_PAYMENTINFORMATION_H
