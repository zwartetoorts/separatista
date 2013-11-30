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

#include <istream>
#include <fstream>
#include <string>

#include "mt940s.h"
#include "iban/iban.h"

using namespace std;
using namespace Separatista;

MT940SDocument::~MT940SDocument()
{
	vector<MT940SRecordset*>::iterator it;

	// Delete all recordsets
	for(it = m_recordsets.begin(); it != m_recordsets.end(); it++)
		delete *it;
}

size_t MT940SDocument::getRecordsetCount()
{
	return m_recordsets.size();
}

MT940SRecordset* MT940SDocument::getRecordset(size_t i) 
{
	return m_recordsets[i];
}

MT940SRecordset::~MT940SRecordset()
{
	vector<MT940STransaction*>::iterator it;

	// Delete all transactions
	for(it = m_transactions.begin(); it != m_transactions.end(); it++)
		delete *it;
}

MT940SDocument::OpenStatus MT940SDocument::Open(const char *path)
{
	ifstream ifs;
	string line, header;
	string::iterator it;
	MT940SRecordset::ReadInfo info;
	MT940SRecordset *recordset;
	int nline, rline;
	MT940SDocument::OpenStatus status = OK;

	// Open file
	ifs.open(path);
	if(!ifs.is_open())
		return MT940SDocument::E_FILE;

	// Read lines from file
	nline = 0;
	recordset = NULL;
	while (ifs.good() && status == OK)
	{
		// Read line
		getline(ifs, line);
		
		// Check for first :
		if(line.length() != 0)
		{
			it = line.begin();
			if(*it == ':')
			{
				// It's a new record, get the code
				rline = 0;
				header.clear();
				for(++it; *it != ':'; ++it)
					header += *it;

				if(header == "940")
				{
					recordset = NULL;
					status = ReadRecord940(nline, rline);
				}
				else
				{
					// Recordset should start with record 20
					if(header == "20")
					{
						recordset = new MT940SRecordset();
						m_recordsets.push_back(recordset);
					}
				}

				// Next character
				++it;
			} else {
				// It's the same record
				rline++;
			}

			// Check recordset
			if(recordset != NULL)
				status = recordset->ReadRecord(nline, rline, header, string(it, line.end()), &info);
		}
		nline++;
	}

	ifs.close();
	return status;
}

MT940SDocument::OpenStatus MT940SDocument::ReadRecord940(int line, int rline)
{
	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord(int line, int rline, std::string &header, std::string &data, MT940SRecordset::ReadInfo *info)
{
	// Transaction Reference record
	if(header == "20")
		return ReadRecord20(line, rline, data, info);

	// Account number record
	if(header == "25")
		return ReadRecord25(line, rline, data, info);

	// Serial number record
	if(header == "28C")
		return ReadRecord28C(line, rline, data, info);

	// Previous balance record
	if(header == "60F")
		return ReadRecord60F(line, rline, data, info);

	// Transcript record
	if(header == "61")
		return ReadRecord61(line, rline, data, info);

	// Description record
	if(header == "86")
		return ReadRecord86(line, rline, data, info);

	// Current balance record
	if(header == "62F")
		return ReadRecord62F(line, rline, data, info);

	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord20(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	m_transactionReference = data;
	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord25(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	size_t i;

	// Account number and currency seperated by space
	i = data.find(' ');
	if(i == string::npos)
		return MT940SDocument::E_FORMAT;
	m_ibanClient = data.substr(0, i - 2).c_str();
	m_currencyClient = data.substr(i + 1);
	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord28C(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	m_serialNumber = data;
	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord60F(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	// Get the date first
	m_previousBalanceDate = data.substr(1, 6).c_str();
	// Get the balance
	m_previousBalance.set(data[0], data.substr(7, 3).c_str(), data.substr(10).c_str());
	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord61(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	size_t i;
	string code;

	// Check record line
	if(rline == 0)
	{
		// Initialize ReadInfo
		info->key.clear();

		// Create new transaction
		info->transaction = new MT940STransaction;

		// Get the transaction date
		info->transaction->setDate(data.substr(0, 6).c_str());

		// rdc code
		if(data[6] == 'R')
		{
			// RD or RC
			i = 1;
			code = "R";
			code += data[7];
		} 
		else 
		{
			i = 0;
			code = data[6];
		}
		info->transaction->setRDCCode(code.c_str());

		// Currency
		info->transaction->setCurrency(data[6 + i], m_currencyClient.c_str(), data.substr(7 + i, 15).c_str());

		// Transaction code
		info->transaction->setTransactionCode(data.substr(22 + i, 4).c_str());

		// Transaction reference
		info->transaction->setTransactionReference(data.substr(26 + i, 16).c_str());
	}
	else
	{
		// Check transaction
		if(!info->transaction)
			return MT940SDocument::E_FORMAT;

		// Get current record
		info->transaction->setForeignIBAN(data.c_str());
		
		// Save the record
		m_transactions.push_back(info->transaction);
	}

	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord86(int line, int rline, std::string &data, MT940SRecordset::ReadInfo *info)
{
	string part;
	string::iterator it;
	
	if(!info->transaction)
		return MT940SDocument::E_FORMAT;

	it = data.begin();

	// First run, initialize
	if(rline == 0 && it != data.end())
	{
		// Check first /
		if(*it != '/')
			return MT940SDocument::E_FORMAT;

		it++;
		info->isKey = true;
		info->key.clear();
	}

	// Split string by / chars
	for(; it != data.end(); it++)
	{
		if(*it != '/')
		{
			if(info->isKey)
				info->key += *it;
			else
				info->value += *it;
		}
		else
		{
			if(info->isKey)
			{
				info->value.clear();
				info->isKey = false;
			}
			else
			{
				info->transaction->addDescription(info->key.c_str(), info->value.c_str());
				info->isKey = true;
				info->key.clear();
			}
		}
	}

	return MT940SDocument::OK;
}

MT940SDocument::OpenStatus MT940SRecordset::ReadRecord62F(int line, int rline, std::string &data, Separatista::MT940SRecordset::ReadInfo *info)
{
	// Get the date first
	m_currentBalanceDate = data.substr(1, 6).c_str();
	// Get the balance
	m_currentBalance.set(data[0], data.substr(7, 3).c_str(), data.substr(10).c_str());

	return MT940SDocument::OK;
}

const char* MT940SRecordset::getCurrencyClient() const
{
	return m_currencyClient.c_str();
}

const char* MT940SRecordset::getTransactionReference() const
{
	return m_transactionReference.c_str();
}

const char* MT940SRecordset::getSerialNumber() const
{
	return m_serialNumber.c_str();
}

const IBAN* MT940SRecordset::getIBANClient() const
{
	return &m_ibanClient;
}

const MT940SCurrency* MT940SRecordset::getPreviousBalance() const
{
	return &m_previousBalance;
}

const MT940SDate* MT940SRecordset::getPreviousBalanceDate() const
{
	return &m_previousBalanceDate;
}

const MT940SCurrency* MT940SRecordset::getCurrentBalance() const
{
	return &m_currentBalance;
}

const MT940SDate* MT940SRecordset::getCurrentBalanceDate() const
{
	return &m_currentBalanceDate;
}

const MT940SRecordset::TransactionIterator MT940SRecordset::getTransactionBegin()
{
	return m_transactions.begin();
}

const MT940SRecordset::TransactionIterator MT940SRecordset::getTransactionEnd()
{
	return m_transactions.end();
}

const MT940SDate* MT940STransaction::getDate() const
{
	return &m_date;
}

void MT940STransaction::setDate(const char *date)
{
	m_date = date;
}

const char* MT940STransaction::getRDCCode() const
{
	return m_rdcCode.c_str();
}

void MT940STransaction::setRDCCode(const char *code)
{
	m_rdcCode = code;
}

const MT940SCurrency* MT940STransaction::getCurrency() const
{
	return &m_currency;
}

void MT940STransaction::setCurrency(const char dcCode, const char *currency, const char *amount)
{
	m_currency.set(dcCode, currency, amount);
}

const char* MT940STransaction::getTransactionCode() const
{
	return m_transactionCode.c_str();
}

void MT940STransaction::setTransactionCode(const char *code)
{
	m_transactionCode = code;
}

const char* MT940STransaction::getTransactionReference() const
{
	return m_transactionReference.c_str();
}

void MT940STransaction::setTransactionReference(const char *code)
{
	m_transactionReference = code;
}

const IBAN* MT940STransaction::getForeignIBAN() const
{
	return &m_foreignIBAN;
}

void MT940STransaction::setForeignIBAN(const char *iban)
{
	m_foreignIBAN = iban;
}

const char* MT940STransaction::getDescription(const char *key)
{
	return m_descriptionMap[key].c_str();
}

void MT940STransaction::addDescription(const char *key, const char *value)
{
	m_descriptionMap[key] = value;
}

const MT940STransaction::DescriptionIterator MT940STransaction::getDescriptionBegin()
{
	return m_descriptionMap.begin();
}

const MT940STransaction::DescriptionIterator MT940STransaction::getDescriptionEnd()
{
	return m_descriptionMap.end();
}

void MT940SCurrency::set(const char dcCode, const char *currency, const char *amount)
{
	m_dcCode = dcCode;
	m_currency = currency;
	m_amount = amount;
}

MT940SCurrency::operator const char* ()
{
	// dcCode
	if(m_dcCode == 'D' || m_dcCode == 'd')
		m_buffer = "-";
	else
		m_buffer.clear();

	// Value
	m_buffer += m_currency;

	return m_buffer.c_str();
}

MT940SDate& MT940SDate::operator =(const char *date)
{
	m_date = date;

	return *this;
}

time_t MT940SDate::getTime() const 
{
	tm timeinfo;
	tm *ptm;
	time_t t;

	// Get the current time for tm_year
	t = time(NULL);
	ptm = localtime(&t);

	//Create the tm
	timeinfo.tm_sec = 0;
	timeinfo.tm_min = 0;
	timeinfo.tm_hour = 0;
	timeinfo.tm_mday = stoi(m_date.substr(4, 1));		// Day of the month
	timeinfo.tm_mon = stoi(m_date.substr(2,1)) - 1;		// Months since jan
	timeinfo.tm_year = ptm->tm_year - (ptm->tm_year % 100) + stoi(m_date.substr(0, 1));	// YY converted to this century
	
	// Convert to time_t
	return mktime(&timeinfo); 
}

MT940SDate::operator time_t() const
{
	return getTime();
}


