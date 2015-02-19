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
	/// Invalid value exception, thrown when an element can't accept a value.
	class SEPARATISTA_EXTERN InvalidValueException : public Exception
	{
	public:
		InvalidValueException(const wchar_t *pMessage, Element *pSource, const wchar_t *pValue) : Exception(pMessage) 
		{ 
			m_pSource = pSource;
			m_pValue = pValue;
		};

#ifdef SEPARATISTA_DEBUG
		InvalidValueException(const wchar_t *pMessage, const wchar_t *pPath, int nLine, Element *pSource, const wchar_t *pValue) :
			Exception(pMessage, pPath, nLine)
		{
			m_pSource = pSource;
			m_pValue = pValue;
		};
#endif

		/// Returns the target element 
		Element* getSourceElement() const
		{
			return m_pSource;
		};

		/// Returns the erronous value
		const wchar_t* getValue() const
		{
			return m_pValue;
		};

	private:
		Element *m_pSource;
		const wchar_t *m_pValue;
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
		virtual void validate(const wchar_t *pValue, Element *pElement) const = 0;

		static void validateMaxText(const wchar_t *pValue, size_t max, Element *pElement);

		static void validateFractionDigits(const wchar_t *pValue, size_t mix, size_t max, Element *pElement);

		static void validateTotalDigits(const wchar_t *pValue, size_t min, size_t max, Element *pElement);

		static void validateNumeric(const wchar_t *pValue, Element *pElement);

		static void validateEnum(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues, Element *pElement);

		static void isDigit(const wchar_t c, Element *pElement);

	private:
		static std::array<wchar_t, 10> m_numericDigits;
	};

	/// Max35Text
	class SEPARATISTA_EXTERN Max35TextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ISODateTimeValidator
	class SEPARATISTA_EXTERN ISODateTimeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// Max15NumericText
	class SEPARATISTA_EXTERN Max15NumericTextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// DecimalNumber
	class SEPARATISTA_EXTERN DecimalNumberValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// Max140Text
	class SEPARATISTA_EXTERN Max140TextValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// PaymentMethod2CodeValidator
	class SEPARATISTA_EXTERN PaymentMethod2CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ISODateValidator
	class SEPARATISTA_EXTERN ISODateValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ChargeBearerType1CodeValidator
	class SEPARATISTA_EXTERN ChargeBearerType1CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ExternalServiceLevel1CodeValidator
	class SEPARATISTA_EXTERN ExternalServiceLevel1CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ExternalLocalInstrumentCodeValidator
	class SEPARATISTA_EXTERN ExternalLocalInstrumentCodeValidator : public Max35TextValidator { };

	/// SequenceType3CodeValidator
	class SEPARATISTA_EXTERN SequenceType3CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// ActiveOrHistoricCurrencyAndAmountValidator
	class SEPARATISTA_EXTERN ActiveOrHistoricCurrencyAndAmountValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};
	
	/// ExternalPersonIdentification1Code
	class SEPARATISTA_EXTERN ExternalPersonIdentification1CodeValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// IBANValidator
	class SEPARATISTA_EXTERN IBANValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	/// BICValidator
	class SEPARATISTA_EXTERN BICValidator : public Validator
	{
	public:
		void validate(const wchar_t *pValue, Element *pElement) const;
	};

	typedef struct
	{
		Max35TextValidator Max35TextValidator;
		ISODateTimeValidator ISODateTimeValidator;
		Max15NumericTextValidator Max15NumericTextValidator;
		DecimalNumberValidator DecimalNumberValidator;
		Max140TextValidator Max140TextValidator;
		PaymentMethod2CodeValidator PaymentMethod2CodeValidator;
		ISODateValidator ISODateValidator;
		ChargeBearerType1CodeValidator ChargeBearerType1CodeValidator;
		ExternalServiceLevel1CodeValidator ExternalServiceLevel1CodeValidator;
		ExternalLocalInstrumentCodeValidator ExternalLocalInstrumentCodeValidator;
		SequenceType3CodeValidator SequenceType3CodeValidator;
		ActiveOrHistoricCurrencyAndAmountValidator ActiveOrHistoricCurrencyAndAmountValidator;
		ExternalPersonIdentification1CodeValidator ExternalPersonIdentification1CodeValidator;
		IBANValidator IBANValidator;
		BICValidator BICValidator;
	} _Validators;

	static const _Validators Validators;
}

#endif // !defined SEPARATISTA_VALIDATOR_H
