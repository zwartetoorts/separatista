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

#ifndef SEPARATISTA_MT940S_H
#define SEPARATISTA_MT940S_H

#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

#include "separatista/iban/iban.h"

#ifdef MT940S_BUILDINGDLL
#	define MT940S_EXTERN __declspec(dllexport)
#elif defined MT940S_USINGDLL
#	define MT940S_EXTERN __declspec(dllimport)
#else
#	define MT940S_EXTERN
#endif

namespace Separatista 
{

class MT940SCurrency
{
public:
	/**
		Constructor
	*/
	MT940S_EXTERN MT940SCurrency();

	/**
		Set all values
		@param dcCode D for Debet or C for Credit
		@param currency International currencty code
		@param amount Amount as text with decimal sign
	*/
	MT940S_EXTERN void set(const char dcCode, const char *currency, const char *amount);

	/**
		Converts to a char array. Will include sign.
	*/
	MT940S_EXTERN const char* getCurrency();
	MT940S_EXTERN operator const char* ();

private:
	char m_dcCode;
	std::string m_currency;
	std::string m_amount;
	std::string m_buffer;	// Internal buffer for formatting
};

class MT940SDate
{
public:
	/**
		Constructor
	*/
	MT940S_EXTERN MT940SDate();

	/**
		Set the date
		@param date Must be in YYMMDD format
	*/
	MT940S_EXTERN MT940SDate& operator = (const char *date);

	MT940S_EXTERN time_t getTime() const;

	MT940S_EXTERN operator time_t () const;
private:
	std::string m_date;
};

class MT940STransaction
{
public:
	/**
		Constructor
	*/
	MT940S_EXTERN MT940STransaction();

	MT940S_EXTERN ~MT940STransaction();

	MT940S_EXTERN MT940SDate* getDate();
	MT940S_EXTERN void setDate(const char *date);

	MT940S_EXTERN const char* getRDCCode() const;
	MT940S_EXTERN void setRDCCode(const char *code);

	MT940S_EXTERN MT940SCurrency* getCurrency();
	MT940S_EXTERN void setCurrency(const char dcCode, const char *currency, const char *amount);

	MT940S_EXTERN const char* getTransactionCode() const;
	MT940S_EXTERN void setTransactionCode(const char *code);

	MT940S_EXTERN const char* getTransactionReference() const;
	MT940S_EXTERN void setTransactionReference(const char *code);

	MT940S_EXTERN const IBAN* getForeignIBAN() const;
	MT940S_EXTERN void setForeignIBAN(const char *iban);
	
	/**
		Adds a description. Will move the internal pointer back to the first description.
		@see moveFirstDescription
	*/
	MT940S_EXTERN void addDescription(const char *key, const char *value);
	MT940S_EXTERN const char* getDescription(const char *key);

	MT940S_EXTERN void moveFirstDescription();
	MT940S_EXTERN bool moveNextDescription();
	MT940S_EXTERN bool descriptionEOF() const;
	MT940S_EXTERN const char* getDescriptionKey() const;
	MT940S_EXTERN const char* getDescriptionValue() const;

private:
	MT940SDate m_date;
	std::string m_rdcCode;
	MT940SCurrency m_currency;
	std::string m_transactionCode;
	std::string m_transactionReference;
	IBAN m_foreignIBAN;
	std::unordered_map<std::string, std::string> m_descriptionMap;
	std::unordered_map<std::string, std::string>::iterator m_descriptionIterator;
};

// Forward declaration
class MT940SRecordset;

class MT940SDocument
{
public:
	/**
		Constructor
	*/
	MT940S_EXTERN MT940SDocument();

	/**
		Destructor
	*/
	MT940S_EXTERN ~MT940SDocument();

	/**
		Code indicating success or failure reading a MT940S file
	*/
	enum OpenStatus 
	{
		/// Success
		OK = 0,
		/// Error opening/reading file
		E_FILE,
		/// Error parsing file or not a MT940S file
		E_FORMAT,
		/// No memory available
		E_MEMORY
	};

	/**
		Read a MT940S file
		@param path The path to the file
		@return OK for success, or error code
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus Open(const char *path);

	/**
		Get the number of recordsets in the document
	*/
	MT940S_EXTERN size_t getRecordsetCount();

	/**
		Get the MT940SRecord at index i
	*/
	MT940S_EXTERN MT940SRecordset* getRecordset(size_t i);
protected:
	/**
		Handle header 940 Optional standard header
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord940(int line, int rline);

private:
	std::vector<MT940SRecordset*> m_recordsets;
};

class MT940SRecordset 
{
public:
	/**
		Constructor	
	*/
	MT940S_EXTERN MT940SRecordset();

	/**
		Destructor
	*/
	MT940S_EXTERN ~MT940SRecordset();

	MT940SDocument::OpenStatus MT940S_EXTERN getStatus() const;

	/**
		Handles the data according to the header
		@param line The line number in the document
		@param rline The line number in the record
		@param header The record id header, without the semicolons
		@param data The to be parsed data
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord(int line, int rline, std::string& header, std::string& data);

	MT940S_EXTERN const char* getCurrencyClient() const;

	MT940S_EXTERN const char* getTransactionReference() const;

	MT940S_EXTERN const char* getSerialNumber() const;

	MT940S_EXTERN const IBAN* getIBANClient() const;

	MT940S_EXTERN MT940SCurrency* getPreviousBalance();

	MT940S_EXTERN const MT940SDate* getPreviousBalanceDate() const;

	MT940S_EXTERN MT940SCurrency* getCurrentBalance();

	MT940S_EXTERN const MT940SDate* getCurrentBalanceDate() const;

	MT940S_EXTERN size_t getTransactionCount() const;

	MT940S_EXTERN MT940STransaction* getTransaction(size_t index);

	
protected:
	
	/**
		Handle header 20 Transaction record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord20(int line, int rline, std::string& data);
	
	/**
		Handle header 25 Account number record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord25(int line, int rline, std::string& data);
	
	/**
		Handle header 28C Serial number record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord28C(int line, int rline, std::string& data);
	
	/**
		Handle header 60F Previous balance record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord60F(int line, int rline, std::string& data);
	
	/**
		Handle header 61 Transcript record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord61(int line, int rline, std::string& data);
	
	/**
		Handle header 86 Description record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord86(int line, int rline, std::string& data);
	
	/**
		Handle header 62F Current balance record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord62F(int line, int rline, std::string& data);

private:
	std::string m_currencyClient;
	std::string m_transactionReference;
	std::string m_serialNumber;
	IBAN m_ibanClient;
	MT940SCurrency m_previousBalance;
	MT940SDate m_previousBalanceDate;
	MT940SCurrency m_currentBalance;
	MT940SDate m_currentBalanceDate;
	std::vector<MT940STransaction*> m_transactions;
	std::vector<MT940STransaction*>::iterator m_transactionsIterator;
	std::string m_description;
};

}

#endif // !defined SEPARATISTA_MT940S_H
