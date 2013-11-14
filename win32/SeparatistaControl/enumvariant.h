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
#include <vector>

#ifndef SEPARATISTA_ENUMVARIANT_H
#define SEPARATISTA_ENUMVARIANT_G

class EnumVariant : public IEnumVARIANT
{
public:
	EnumVariant();

	// Destructor
	~EnumVariant();

	// IUnknown methods
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** pvvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	// IEnumVARIANT methods
	STDMETHOD(Next)(unsigned long celt, VARIANT FAR* rgvar, unsigned long FAR* pceltFetched);
	STDMETHOD(Skip)(unsigned long celt);
	STDMETHOD(Reset)();
	STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);

	// Other methods
	EnumVariant& operator = (std::vector<IUnknown*> *objects);

private:
	ULONG m_uRefCount;
	std::vector<IUnknown*> m_objects;

};

#endif // !defined SEPARATISTA_ENUMVARIANT_H