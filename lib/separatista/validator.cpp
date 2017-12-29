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
#include <xercesc/util/regx/RegularExpression.hpp>
#include <xercesc/validators/datatype/StringDatatypeValidator.hpp>
#include <xercesc/validators/datatype/DecimalDatatypeValidator.hpp>
#include <xercesc/validators/datatype/DateDatatypeValidator.hpp>
#include <xercesc/validators/datatype/DateTimeDatatypeValidator.hpp>
#include <xercesc/validators/datatype/InvalidDatatypeValueException.hpp>

#include "separatista.h"
#include "debug/debug.h"
#include "validator.h"
#include "iban/iban.h"

using namespace Separatista;

void Separatista::Validator::validateDecimal(const wchar_t * pValue, Element * pElement)
{
	DEBUG_STATIC_METHOD;
	xercesc::XSValue::Status status;

	if(!xercesc::XSValue::validate(pValue, xercesc::XSValue::dt_decimal, status) || status != xercesc::XSValue::st_Init)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a decimal value"), pElement, pValue);
}

void Separatista::Validator::validateString(const wchar_t * pValue, Element * pElement)
{
	DEBUG_STATIC_METHOD;
	xercesc::XSValue::Status status;

	if (!xercesc::XSValue::validate(pValue, xercesc::XSValue::dt_string, status) || status != xercesc::XSValue::st_Init)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a string value"), pElement, pValue);
}

void Separatista::Validator::validateBoolean(const wchar_t * pValue, Element * pElement)
{
	DEBUG_STATIC_METHOD;
	xercesc::XSValue::Status status;

	if (!xercesc::XSValue::validate(pValue, xercesc::XSValue::dt_boolean, status) || status != xercesc::XSValue::st_Init)
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a boolean value"), pElement, pValue);

}

void Separatista::Validator::validateMinInclusive(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	validate<xercesc::DecimalDatatypeValidator>(xercesc::SchemaSymbols::fgELT_MININCLUSIVE, pValue, pArg, pElement);
}

void Separatista::Validator::validateFractionDigits(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	validate<xercesc::DecimalDatatypeValidator>(xercesc::SchemaSymbols::fgELT_FRACTIONDIGITS, pValue, pArg, pElement);
}

void Separatista::Validator::validateTotalDigits(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	validate<xercesc::DecimalDatatypeValidator>(xercesc::SchemaSymbols::fgELT_TOTALDIGITS, pValue, pArg, pElement);
}

void Validator::validateNumeric(const wchar_t *pValue, Element *pElement)
{
	DEBUG_STATIC_METHOD;

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

void Separatista::Validator::validateEnumeration(const wchar_t * pValue, std::initializer_list<const wchar_t*> PossibleValues, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	for (auto possibleValue : PossibleValues)
	{
		if (std::wcscmp(possibleValue, pValue) == 0)
			return;
	}
	SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Value doesn't match predefined set"), pElement, pValue);
}

void Separatista::Validator::validatePattern(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	xercesc::RegularExpression rex(pArg);
	if (!rex.matches(pValue))
		SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Value doesn't match predefined pattern"), pElement, pValue);
}

void Separatista::Validator::validateMinLength(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	validate<xercesc::StringDatatypeValidator>(xercesc::SchemaSymbols::fgELT_MINLENGTH, pValue, pArg, pElement);
}

void Separatista::Validator::validateMaxLength(const wchar_t * pValue, const wchar_t * pArg, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	validate<xercesc::StringDatatypeValidator>(xercesc::SchemaSymbols::fgELT_MAXLENGTH, pValue, pArg, pElement);
}

void Separatista::Validator::validateDateTime(const wchar_t * pValue, Element * pElement)
{
	DEBUG_STATIC_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_dateTime,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Not a datetime value"), pElement, pValue);
	}
}

void Separatista::Validator::validateDate(const wchar_t * pValue, Element * pElement)
{
	DEBUG_STATIC_METHOD;

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

