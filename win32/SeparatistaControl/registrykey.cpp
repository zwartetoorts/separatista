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

#include <string>
#include <locale>
#include <tchar.h>
#include <shlwapi.h>

#include "registrykey.h"

RegistryKey::RegistryKey(HKEY hKey, LPCTSTR lpSubKey)
{
	m_bIsOpen = false;

	if(RegCreateKeyEx(
		hKey,
		lpSubKey,
		NULL,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&m_hKey,
		NULL) == ERROR_SUCCESS)
	{
		m_bIsOpen = true;
	}
}

RegistryKey::~RegistryKey()
{
	if(m_bIsOpen)
		RegCloseKey(m_hKey);
}

bool RegistryKey::isOpen() const
{
	return m_bIsOpen;
}

bool RegistryKey::setValue(LPCTSTR lpValue)
{
	return setValue(NULL, lpValue);
}

bool RegistryKey::setValue(LPCTSTR lpValueName, LPCTSTR lpValue)
{
	if(!m_bIsOpen)
		return false;

	if(RegSetValueEx(
		m_hKey,
		lpValueName,
		NULL,
		REG_SZ,
		(const BYTE*)lpValue,
		_tcslen(lpValue) * sizeof(TCHAR)) == ERROR_SUCCESS)
	{
		return true;
	}

	return false;
}

void RegistryKey::operator =(LPCTSTR lpValue)
{
	setValue(lpValue);
}

RegistryKey::operator HKEY()
{
	return m_hKey;
}

void RegistryKey::DeleteTree(LPCTSTR lpSubKeyName)
{
	if(m_bIsOpen)
	{
		SHDeleteKey(
			m_hKey,
			lpSubKeyName);
	}
}
