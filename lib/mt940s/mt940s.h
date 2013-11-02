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
#include <map>

#include "iban/iban.h"

#ifdef MT940S_EXPORTS
#	define MT940S_EXTERN __declspec(dllexport)
#	define MT940S_EXPIMP 
#else
#	define MT940S_EXTERN __declspec(dllimport)
#	define MT940S_EXPIMP extern
#endif

namespace Separatista 
{

class MT940S_EXTERN MT940SCurrency
{
public:
	/**
		Set all values
		@param dcCode D for Debet or C for Credit
		@param currency International currencty code
		@param amount Amount as text with decimal sign
	*/
	void set(const char dcCode, const char *currency, const char *amount);

private:
	char m_dcCode;
	std::string m_currency;
	std::string m_amount;
};

class MT940S_EXTERN MT940SDate
{
public:
	/**
		Set the date
		@param date Must be in YYMMDD format
	*/
	void operator = (const char *date);
private:
	std::string m_date;
};

class MT940STransaction
{
public:
	MT940S_EXTERN MT940STransaction() {};

	MT940S_EXTERN const MT940SDate* getDate() const;
	MT940S_EXTERN void setDate(const char *date);

	MT940S_EXTERN const char* getRDCCode() const;
	MT940S_EXTERN void setRDCCode(const char *code);

	MT940S_EXTERN const MT940SCurrency* getCurrency() const;
	MT940S_EXTERN void setCurrency(const char dcCode, const char *currency, const char *amount);

	MT940S_EXTERN const char* getTransactionCode() const;
	MT940S_EXTERN void setTransactionCode(const char *code);

	MT940S_EXTERN const char* getTransactionReference() const;
	MT940S_EXTERN void setTransactionReference(const char *code);

	MT940S_EXTERN const IBAN* getForeignIBAN() const;
	MT940S_EXTERN void setForeignIBAN(const char *iban);

	MT940S_EXTERN void addDescription(const char *key, const char *value);
	MT940S_EXTERN const char* getDiscription(const char *key);

private:
	MT940SDate m_date;
	std::string m_rdcCode;
	MT940SCurrency m_currency;
	std::string m_transactionCode;
	std::string m_transactionReference;
	IBAN m_foreignIBAN;
	std::map<std::string, std::string> m_descriptionMap;
};

// Forward declaration
class MT940SRecordset;

class MT940SDocument
{
public:
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
		E_FORMAT
	};

	/**
		Read a MT940S file
		@param path The path to the file
		@return OK for success, or error code
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus Open(const char *path);
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
		Destructor
	*/
	MT940S_EXTERN ~MT940SRecordset();

	MT940SDocument::OpenStatus MT940S_EXTERN getStatus() const;

	struct ReadInfo
	{
		MT940STransaction* transaction;
		std::string key, value;
		bool isKey;
	};

	/**
		Handles the data according to the header
		@param line The line number in the document
		@param rline The line number in the record
		@param header The record id header, without the semicolons
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord(int line, int rline, std::string& header, std::string& data, ReadInfo *info);

protected:
	
	/**
		Handle header 20 Transaction record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord20(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 25 Account number record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord25(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 28C Serial number record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord28C(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 60F Previous balance record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord60F(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 61 Transcript record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord61(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 86 Description record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord86(int line, int rline, std::string& data, ReadInfo *info);
	
	/**
		Handle header 62F Current balance record
		@param line The line number in the document
		@param rline The line number in the record
		@param data The to be parsed data
		@param info Parser information needed internally. Should be provided by the caller.
		@see ReadRecord
	*/
	MT940S_EXTERN MT940SDocument::OpenStatus ReadRecord62F(int line, int rline, std::string& data, ReadInfo *info);

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
};

}

#endif // !defined SEPARATISTA_MT940S_H
