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

#ifndef SEPARATISTA_IBAN_H
#define SEPARATISTA_IBAN_H

#include <string>

// Disable Visual c++ warning C4251
#ifdef _MSC_VER 
#pragma warning(disable: 4251)
#endif

#ifdef SEPARATISTA_IBAN_BUILDINGDLL
#	define IBAN_EXTERN __declspec(dllexport)
#elif defined SEPARATISTA_IBAN_USINGDLL
#		define IBAN_EXTERN __declspec(dllimport)
#else
#	define IBAN_EXTERN
#endif

/// Max length of the account part of IBAN
#define SEPARATISTA_IBAN_MAX_ACCOUNT 30

namespace Separatista 
{

typedef wchar_t IBANCC[2];

class IBAN_EXTERN IBAN
{
public:
	/**
		Constructor
	*/
	IBAN();

	/**
		Sets the value from a string
	*/
	IBAN& operator = (const char *iban);

	/**
		Set the value from a wide char string
	*/
	IBAN& operator = (const wchar_t *pIBAN);

	/**
		Sets the value from a string, no error checking is applied
	*/
	void set(const char *iban);
	
	/**
		Sets the value from a wide string, no error checking is applied
	*/
	void set(const wchar_t *pIBAN);

	/**
		Returns the formatted IBAN. 
		@return Pointer to a internal buffer. The buffer is only valid until the next call to this object is made.
		It's recommended to copy the contents as soon as possible.
	*/
	const char* getIBAN();
	
	/**
		@see getIBAN()
	*/
	operator const char* ();

	/**
		returns the 2 characters long countrycode
	*/
	const IBANCC& getCountryCode() const;
	
	/**
		returns the 2 characters long controlsum
	*/
	const IBANCC& getControlSum() const;

	/**
		Checks a IBAN for validity. This is done with the controlsum, no other checks are being made.
	*/
	bool Check() const;

	/**
		Clears all values
	*/
	void Clear();

protected:
	/**
		Writes the value of this IBAN to the internal buffer. 
		@param seperator If true, the IBAN is divided every four characters by a space (NL00 RBOS 0123 4567 89)
	*/
	void format(bool seperator = true);

	/**
		C string equivalent of format
		@see format
	*/
	void mbformat(bool separator = true);

private:
	IBANCC m_countryCode;
	IBANCC m_controlSum;
	wchar_t m_accountNumber[SEPARATISTA_IBAN_MAX_ACCOUNT];
	size_t m_accountNumberLength;

	std::string m_mbformatted;
	std::wstring m_formatted;
};

}

#endif // !defined SAPARATISTA_IBAN_H