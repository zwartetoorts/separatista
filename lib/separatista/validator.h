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
		static void validateMaxText(const wchar_t *pValue, size_t max, Element *pElement);

		static void validateFractionDigits(const wchar_t *pValue, size_t min, size_t max, Element *pElement);

		static void validateTotalDigits(const wchar_t *pValue, size_t min, size_t max, Element *pElement);

		static void validateNumeric(const wchar_t *pValue, Element *pElement);

		static void validateEnum(const wchar_t *pValue, std::initializer_list<const wchar_t*> pPossibleValues, Element *pElement);

		static void isDigit(const wchar_t c, Element *pElement);

		static void validateISODateTime(const wchar_t *pValue, Element *pElement);

		static void validateISODate(const wchar_t *pValue, Element *pElement);


	private:
		static std::array<wchar_t, 10> m_numericDigits;
	};

}

#endif // !defined SEPARATISTA_VALIDATOR_H
