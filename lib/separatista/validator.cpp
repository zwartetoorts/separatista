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

void Validator::validateMaxText(const wchar_t *pValue, size_t max)
{
	DEBUG_METHOD;
	
	if (std::wcslen(pValue) > max)
		throw InvalidValueException(SEPARATISTA_EXCEPTION("Text too long"));
}

void Validator::validateNumeric(const wchar_t *pValue)
{
	DEBUG_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_integer,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			throw InvalidValueException(SEPARATISTA_EXCEPTION("Not a numeric value"));
	}
}

void Validator::isDigit(const wchar_t c)
{
	DEBUG_METHOD;
	for (auto it = m_numericDigits.begin(); it != m_numericDigits.end(); it++)
	{
		if (*it == c)
			return;
	}
	throw InvalidValueException(SEPARATISTA_EXCEPTION("Not a valid digit"));
}

void Validator::validateFractionDigits(const wchar_t *pValue, size_t min, size_t max)
{
	DEBUG_METHOD;

	bool dot = false;
	wchar_t c;
	size_t fc = 0; // Fraction count

	// Scan string
	while ((c = *pValue++) != TEXT('\0'))
	{
		if (c == TEXT('.'))
		{
			if (dot)
				throw InvalidValueException(SEPARATISTA_EXCEPTION("Too many dot's in fraction"));
			else
				dot = true;
		}
		else
		{
			isDigit(c);
			if (++fc > max)
				throw InvalidValueException(SEPARATISTA_EXCEPTION("Too many fraction digits"));
		}
	}
	if (fc < min)
		throw InvalidValueException(SEPARATISTA_EXCEPTION("Too few fraction digits"));
}

void Validator::validateTotalDigits(const wchar_t *pValue, size_t min, size_t max)
{
	DEBUG_METHOD;

	wchar_t c;
	size_t td = 0;

	while ((c = *pValue++) != TEXT('\0'))
	{
		if (c == TEXT('.'))
			break;
		else
		{
			isDigit(c);
			++td;
		}
	}
	if (td < min)
		throw InvalidValueException(SEPARATISTA_EXCEPTION("Too few digits in value"));
	else if (td > max)
		throw InvalidValueException(SEPARATISTA_EXCEPTION("Too many digits in value"));

}

void Validator::validateEnum(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues)
{
	DEBUG_METHOD;

	for (auto it = pPossibleValues.begin(); it != pPossibleValues.end(); it++)
	{
		if (std::wcscmp(*it, pValue) == 0)
			return;
	}
	throw InvalidValueException(SEPARATISTA_EXCEPTION("Not one of the pre-defined values"));
}


void Max35TextValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateMaxText(pValue, 35);
}

void ISODateTimeValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_dateTime,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			throw InvalidValueException(SEPARATISTA_EXCEPTION("Wrong date format"));
	}
}

void Max15NumericTextValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD

	validateMaxText(pValue, 15);
	validateNumeric(pValue);
}

void DecimalNumberValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateFractionDigits(pValue, 0, 17);
	validateTotalDigits(pValue, 0, 18);
}

void Max140TextValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD

	validateMaxText(pValue, 140);
}

void PaymentMethod2CodeValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateEnum(pValue, { TEXT("DD") });
}

void ISODateValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	xercesc::XSValue::Status st;

	if (xercesc::XSValue::validate(
		pValue,
		xercesc::XSValue::DataType::dt_date,
		st))
	{
		if (st != xercesc::XSValue::st_Init)
			throw InvalidValueException(SEPARATISTA_EXCEPTION("Not a date value"));
	}
}

void ChargeBearerType1CodeValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateEnum(
		pValue,
		{
			TEXT("DEBT"),
			TEXT("CRED"),
			TEXT("SHAR"),
			TEXT("SLEV")
		});
}

void ExternalServiceLevel1CodeValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateMaxText(pValue, 4);
}

void SequenceType3CodeValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateEnum(
		pValue,
		{
			TEXT("FRST"),
			TEXT("RCUR"),
			TEXT("FNAL"),
			TEXT("OOFF"),
			TEXT("RPRE")
		});
}

void ActiveOrHistoricCurrencyAndAmountValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateFractionDigits(pValue, 0, 5);
	validateTotalDigits(pValue, 0, 18);
}

void ExternalPersonIdentification1Code::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	validateMaxText(pValue, 35);
}

void IBANValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;

	IBAN iban;
	
	iban = pValue;
	if (!iban.Check())
		throw InvalidValueException(SEPARATISTA_EXCEPTION("Invalid IBAN"));
}

void BICValidator::validate(const wchar_t *pValue)
{
	DEBUG_METHOD;
}