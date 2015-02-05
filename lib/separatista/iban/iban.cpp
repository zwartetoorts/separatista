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

#include "separatista/debug/debug.h"
#include "iban.h"

#include <cwchar>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace Separatista;

IBAN::IBAN()
{
	Clear();	
}

void IBAN::Clear()
{
	m_accountNumberLength = 0;
	m_countryCode[0] = TEXT(' ');
	m_countryCode[1] = TEXT(' ');
	m_controlSum[0] = TEXT(' ');
	m_controlSum[1] = TEXT(' ');
}

IBAN& IBAN::operator =(const char *iban)
{
	set(iban);
	return *this;
}

IBAN& IBAN::operator =(const wchar_t *pIBAN)
{
	set(pIBAN);
	return *this;
}

const char* IBAN::getIBAN()
{
	mbformat();
	return m_mbformatted.data();
}

IBAN::operator const char* ()
{
	return getIBAN();
}

const IBANCC& IBAN::getControlSum() const
{
	return m_controlSum;
}

const IBANCC& IBAN::getCountryCode() const
{
	return m_countryCode;
}

void IBAN::set(const char* iban)
{
	// Convert to wchar_t
	wchar_t buffer[SEPARATISTA_IBAN_MAX_ACCOUNT + 1];

	mbstowcs(buffer, iban, SEPARATISTA_IBAN_MAX_ACCOUNT);
	buffer[SEPARATISTA_IBAN_MAX_ACCOUNT] = TEXT('\0');
	set(buffer);
}

void IBAN::set(const wchar_t *pIBAN)
{
	std::wstring value = pIBAN;

	int pos = 0;

	// Iterate over the characters
	for (auto it = value.begin(); it != value.end(); ++it)
	{
		// Skip white space
		if (*it != ' ')
		{
			char c = toupper(*it);
			if (pos < 2)
				// Country code
				m_countryCode[pos] = c;
			else if (pos < 4)
				// Controlsum
				m_controlSum[pos - 2] = c;
			else if (pos < 34)
			{
				// Account number
				m_accountNumber[pos - 4] = c;
				m_accountNumberLength = pos - 3;
			}
			++pos;
		}
	}
}

int translate_table(const wchar_t c)
{
	static const wchar_t* table = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	for (int i = 0; i < 36; i++)
		if (table[i] == c)
			return i;
	return 0;
}

bool IBAN::Check() const
{
	std::string val;
	std::ostringstream ss;
	
	// Build value
	for (size_t i = 0; i < m_accountNumberLength; i++)
	{
		// Account number
		ss << translate_table(m_accountNumber[i]);
	}
	// Countrycode and ControlSum
	ss << translate_table(m_countryCode[0]);
	ss << translate_table(m_countryCode[1]);
	ss << translate_table(m_controlSum[0]);
	ss << translate_table(m_controlSum[1]);

	val = ss.str();
	int sum = 0, c;
	for (auto it = val.begin(); it != val.end(); it++)
	{
		c = *it;
		c -= '0';
		sum *= 10;
		sum += c;
		//if (sum >= 97)
			sum %= 97;
	}

	return sum == 1;
}

void IBAN::format(bool seperator)
{
	m_formatted.clear();

	m_formatted += m_countryCode[0];
	m_formatted += m_countryCode[1];
	m_formatted += m_controlSum[0];
	m_formatted += m_controlSum[1];

	// Group by 4
	for (size_t i = 0; i < m_accountNumberLength; i++)
	{
		// Space every 4 characters
		if (seperator && i % 4 == 0)
			m_formatted += TEXT(' ');
		m_formatted += m_accountNumber[i];
	}
}

void IBAN::mbformat(bool seperator)
{
	m_mbformatted.clear();

	m_mbformatted += std::wctob(m_countryCode[0]);
	m_mbformatted += std::wctob(m_countryCode[1]);
	m_mbformatted += std::wctob(m_controlSum[0]);
	m_mbformatted += std::wctob(m_controlSum[1]);

	// Group by 4
	for (size_t i = 0; i < m_accountNumberLength; i++)
	{
		// Space every 4 characters
		if (seperator && i % 4 == 0)
			m_mbformatted += TEXT(' ');
		m_mbformatted += std::wctob(m_accountNumber[i]);
	}
}
