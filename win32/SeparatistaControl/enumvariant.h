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
#include <array>
#include "unknown.cpp"
#include "separatista/debug/debug.h"

#ifndef SEPARATISTA_ENUMVARIANT_H
#define SEPARATISTA_ENUMVARIANT_H

class EnumVariant : public SepaControlUnknown<IEnumVARIANT>
{
public:
	EnumVariant();

	// IEnumVARIANT methods
	STDMETHOD(Next)(unsigned long celt, VARIANT FAR* rgvar, unsigned long FAR* pceltFetched);
	STDMETHOD(Skip)(unsigned long celt);
	STDMETHOD(Reset)();
	STDMETHOD(Clone)(IEnumVARIANT FAR* FAR* ppenum);

	// Other methods
	/**
		Add a variant to the intenal list.
	*/
	HRESULT Add(const VARIANT &vt);

protected:
	/**
		Destructor with protected access. This object has to be freed through Release method
		since it uses reference counting. Calls VariantClear on all objects in the internal list.
		@see Release()
	*/
	~EnumVariant();

	/**
		The count of VARIANT structures in the objects array
		@see m_objects;
	*/
	static const std::size_t VariantBlockSize = 10;

	/**
		Adds one VARIANT block to the objects list.
	*/
	HRESULT Grow();

	/**
		Get the VARIANT at index
	*/
	VARIANT& Get(std::size_t index);

	typedef std::array<VARIANT, VariantBlockSize> VariantBlockType;
	typedef std::vector<VariantBlockType*> VariantBlockList;

private:
	ULONG m_uRefCount;

	/**
		Vector containing array blocks of VARIANT structures
	*/
	VariantBlockList m_objects;
	/**
		The current number of variants available
	*/
	std::size_t m_size;
	/**
		The current insert position
		@see Add
	*/
	std::size_t m_wpos;
	/**
		The current read position
	*/
	std::size_t m_pos;

};

#endif // !defined SEPARATISTA_ENUMVARIANT_H