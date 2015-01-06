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
#ifndef SEPARATISTA_VALIDATOR_H
#define SEPARATISTA_VALIDATOR_H

#include <initializer_list>
#include <array>

#include "separatista.h"
#include "element.h"
#include "exception.h"

namespace Separatista
{
	/// Invalid value exception
	class SEPARATISTA_EXTERN InvalidValueException : public Exception
	{
	public:
		InvalidValueException(const wchar_t *pMessage) : Exception(pMessage) { };

#ifdef SEPARATISTA_DEBUG
		InvalidValueException(const wchar_t *pMessage, const wchar_t *pPath, int nLine) :
			Exception(pMessage, pPath, nLine) { };
#endif
	};

	/// Validator interface
	class SEPARATISTA_EXTERN Validator
	{
	public:
		/**
			The one and only purpose of this class.
			@param pValue The value to validate as string.
			@throws InvalidValueException
		*/
		virtual void validate(const wchar_t *pValue) = 0;

		static void validateMaxText(const wchar_t *pValue, size_t max);

		static void validateFractionDigits(const wchar_t *pValue, size_t mix, size_t max);

		static void validateTotalDigits(const wchar_t *pValue, size_t min, size_t max);

		static void validateNumeric(const wchar_t *pValue);

		static void validateEnum(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues);

	private:
		static void isDigit(const wchar_t c);

		static std::array<wchar_t, 10> m_numericDigits;
	};

	/// Max35Text
	class SEPARATISTA_EXTERN Max35TextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ISODateTimeValidator
	class SEPARATISTA_EXTERN ISODateTimeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// Max15NumericText
	class SEPARATISTA_EXTERN Max15NumericTextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// DecimalNumber
	class SEPARATISTA_EXTERN DecimalNumberValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// Max140Text
	class SEPARATISTA_EXTERN Max140TextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// PaymentMethod2CodeValidator
	class SEPARATISTA_EXTERN PaymentMethod2CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ISODateValidator
	class SEPARATISTA_EXTERN ISODateValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ChargeBearerType1CodeValidator
	class SEPARATISTA_EXTERN ChargeBearerType1CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ExternalServiceLevel1CodeValidator
	class SEPARATISTA_EXTERN ExternalServiceLevel1CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ExternalLocalInstrumentCodeValidator
	class SEPARATISTA_EXTERN ExternalLocalInstrumentCodeValidator : public Max35TextValidator { };

	/// SequenceType3CodeValidator
	class SEPARATISTA_EXTERN SequenceType3CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// ActiveOrHistoricCurrencyAndAmountValidator
	class SEPARATISTA_EXTERN ActiveOrHistoricCurrencyAndAmountValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};
	
	/// ExternalPersonIdentification1Code
	class SEPARATISTA_EXTERN ExternalPersonIdentification1Code : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// IBANValidator
	class SEPARATISTA_EXTERN IBANValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};

	/// BICValidator
	class SEPARATISTA_EXTERN BICValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue);
	};
}

#endif // !defined SEPARATISTA_VALIDATOR_H
