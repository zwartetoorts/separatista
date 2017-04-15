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
		static void validateDecimal(const wchar_t *pValue, Element *pElement);

		static void validateString(const wchar_t *pValue, Element *pElement);

		static void validateBoolean(const wchar_t *pValue, Element *pElement);

		static void validateMinInclusive(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateFractionDigits(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateTotalDigits(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateNumeric(const wchar_t *pValue, Element *pElement);

		static void validateEnumeration(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues, Element *pElement);

		static void validatePattern(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateMinLength(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateMaxLength(const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

		static void validateDateTime(const wchar_t *pValue, Element *pElement);

		static void validateDate(const wchar_t *pValue, Element *pElement);

		template <class T>
		static void validate(const wchar_t* pSchemaSymbols, const wchar_t *pValue, const wchar_t *pArg, Element *pElement);

	};

	template<class T>
	inline void Validator::validate(const wchar_t * pSchemaSymbols, const wchar_t * pValue, const wchar_t * pArg, Element *pElement)
	{
		xercesc::RefHashTableOf<xercesc::KVStringPair>* pFacets = new xercesc::RefHashTableOf<xercesc::KVStringPair>(1, true);
		pFacets->put(
			(void*)pSchemaSymbols,
			new xercesc::KVStringPair(
				pSchemaSymbols,
				pArg));

		T *pValidator = new T(NULL, pFacets, NULL, 0);
		if (pValidator)
		{
			try
			{
				pValidator->validate(pValue);
			}
			catch (const xercesc::InvalidDatatypeValueException &)
			{
				delete pValidator;
				//delete pFacets;
				SEPARATISTA_THROW_EXCEPTION(InvalidValueException, TEXT("Invalid value"), pElement, pValue);
			}
		}
		delete pValidator;
		//delete pFacets;
	}
}

#endif // !defined SEPARATISTA_VALIDATOR_H
