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

#ifndef SEPARATISTA_DISPATCH_H
#define SEPARATISTA_DISPATCH_H

#include <windows.h>

#include "separatista/debug/debug.h"
#include "separatista/exception.h"
#include "unknown.h"

template <class T>
class SepaControlDispatch : public SepaControlUnknown<T>
{
public:
	/**
		
	*/
	SepaControlDispatch();

	template <class C> static HRESULT Create(REFCLSID rclid, void** pvvObject);

	// IUnknown methods
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** pvvObject);

	// IDispatch methods
	HRESULT STDMETHODCALLTYPE GetTypeInfoCount(unsigned int FAR* pctInfo);
	HRESULT STDMETHODCALLTYPE GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);
	HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId);
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);
protected:
	virtual ~SepaControlDispatch();

	/**
		Handle Separatista Exceptions by setting errorinfo
	*/
	HRESULT SetErrorInfo(const Separatista::Exception &e) const;

	/**
		Handle Separatista Exceptions by setting errorinfo text
	*/
	HRESULT SetErrorInfo(const wchar_t *pMessage) const;


	ITypeLib* m_pTypeLib;
	ITypeInfo* m_pTypeInfo;
};

#endif // !defined SEPARATISTA_DISPATCH_H