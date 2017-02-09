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

template<class T>
T getActualValue(xercesc::XSValue::DataType dataType, const wchar_t *pArg)
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;

	pValue = xercesc::XSValue::getActualValue(pArg, xercesc::XSValue::DataType::dt_int, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
		return 0;

	return pValue->fData.fValue.;
}

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

void Separatista::Validator::validateDecimal(const wchar_t * pValue, Element * pElement)
{
}

void Separatista::Validator::validateString(const wchar_t * pValue, Element * pElement)
{
}

void Separatista::Validator::validateBoolean(const wchar_t * pValue, Element * pElement)
{
}

void Separatista::Validator::validateMinInclusive(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
}

void Separatista::Validator::validateFractionDigits(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_METHOD;

	
}

void Separatista::Validator::validateTotalDigits(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
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

void Separatista::Validator::validateEnumeration(const wchar_t * pValue, std::initializer_list<const wchar_t*> pPossibleValues, Element * pElement)
{
}

void Separatista::Validator::validatePattern(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
}

void Separatista::Validator::validateMinLength(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
}

void Separatista::Validator::validateMaxLength(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_METHOD;

	size_t max = ::getActualValue<size_t>(xercesc::XSValue::dt_unsignedLong, pArg);

	if (std::wcslen(pValue) > max)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Text too long"), pElement, pValue);

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

void Separatista::Validator::validateDateTime(const wchar_t * pValue, Element * pElement)
{
}

void Separatista::Validator::validateDate(const wchar_t * pValue, Element * pElement)
{
}

