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

#ifndef SEPARATISTA_REGISTRYKEY_H
#define SEPARATISTA_REGISTRYKEY_H

#include <windows.h>
#include "separatista/debug/debug.h"

class RegistryKey
{
public:
	RegistryKey(HKEY hKey, LPCTSTR lpSubKey);

	~RegistryKey();

	bool isOpen() const;

	bool setValue(LPCTSTR lpValue);

	bool setValue(LPCTSTR lpValueName, LPCTSTR lpValue);

	void operator = (LPCTSTR lpValue);

	operator HKEY();

	void DeleteTree(LPCTSTR lpSubKeyName);
private:
	HKEY m_hKey;
	bool m_bIsOpen;
};
#endif // SEPARATISTA_REGISTRYKEY_H