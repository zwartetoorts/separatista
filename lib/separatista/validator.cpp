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

#include <cwchar>

#include <xercesc/framework/psvi/XSValue.hpp>

#include "separatista.h"
#include "debug/debug.h"
#include "validator.h"
#include "iban/iban.h"

using namespace Separatista;

std::array<wchar_t, 10> Validator::m_numericDigits =
{
	TEXT('0'),
	TEXT('1'),
	TEXT('2'),
	TEXT('3'),
	TEXT('4'),
	TEXT('5'),
	TEXT('6'),
	TEXT('7'),
	TEXT('8'),
	TEXT('9')
};

void Validator::validateMaxText(const wchar_t *pValue, size_t max, Element *pElement)
{
	DEBUG_METHOD;
	
	if (std::wcslen(pValue) > max)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Text too long"), pElement, pValue);
}

void Validator::validateNumeric(const wchar_t *pValue, Element *pElement)
{
	DEBUG_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_integer,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a numeric value"), pElement, pValue);
	}
}

void Validator::isDigit(const wchar_t c, Element *pElement)
{
	DEBUG_METHOD;
	for (auto it = m_numericDigits.begin(); it != m_numericDigits.end(); it++)
	{
		if (*it == c)
			return;
	}
	SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a valid digit"), pElement, NULL);
}

void Validator::validateFractionDigits(const wchar_t *pValue, size_t min, size_t max, Element *pElement)
{
	DEBUG_METHOD;

	bool dot = false;
	wchar_t c;
	size_t fc = 0; // Fraction count

	// Remove + and - sign
	if (*pValue == TEXT('+') || *pValue == TEXT('-'))
		pValue++;

	// Scan string
	while ((c = *pValue++) != TEXT('\0'))
	{
		if (c == TEXT('.'))
		{
			if (dot)
				SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Too many dot's in fraction"), pElement, pValue);
			else
				dot = true;
		}
		else
		{
			isDigit(c, pElement);
			if (++fc > max)
				SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Too many fraction digits"), pElement, pValue);
		}
	}
	if (fc < min)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Too few fraction digits"), pElement, pValue);
}

void Validator::validateTotalDigits(const wchar_t *pValue, size_t min, size_t max, Element *pElement)
{
	DEBUG_METHOD;

	wchar_t c;
	size_t td = 0;

	// Remove + and - sign
	if (*pValue == TEXT('+') || *pValue == TEXT('-'))
		pValue++;

	while ((c = *pValue++) != TEXT('\0'))
	{
		if (c == TEXT('.'))
			;
		else
		{
			isDigit(c, pElement);
			++td;
		}
	}
	if (td < min)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Too few digits in value"), pElement, pValue);
	else if (td > max)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Too many digits in value"), pElement, pValue);

}

void Validator::validateEnum(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues, Element *pElement)
{
	DEBUG_METHOD;

	for (auto it = pPossibleValues.begin(); it != pPossibleValues.end(); it++)
	{
		if (std::wcscmp(*it, pValue) == 0)
			return;
	}
	SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not one of the pre-defined values"), pElement, pValue);
}


void Validator::validateISODateTime(const wchar_t *pValue, Element *pElement)
{
	DEBUG_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_dateTime,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Wrong date format"), pElement, pValue);
	}
}

void Validator::validateISODate(const wchar_t *pValue, Element *pElement)
{
	DEBUG_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_date,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a date value"), pElement, pValue);
	}
}

