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

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

#include <xercesc/framework/psvi/XSValue.hpp>

#include <windows.h>
#include "separatista.h"
#include "iban/iban.h"

#include <unordered_map>
#include <ctime>

using namespace xercesc;
using namespace Separatista;

const wchar_t* SeparatistaDocument::Document = L"Document";

SeparatistaDocument::SeparatistaDocument()
{
	m_pDOMDocument = NULL;
	m_pErrorMessage = NULL;
	m_path = NULL;
}

SeparatistaDocument::~SeparatistaDocument()
{
	if (m_pErrorMessage)
		XMLString::release(&m_pErrorMessage);
	if (m_pDOMDocument)
		m_pDOMDocument->release();
	if (m_path)
		XMLString::release(&m_path);
}

const wchar_t* SeparatistaDocument::getErrorMessage() const
{
	return m_pErrorMessage;
}

void SeparatistaDocument::setErrorMessage(const wchar_t *pErrorMessage)
{
	if (m_pErrorMessage)
		XMLString::release(&m_pErrorMessage);

	m_pErrorMessage = XMLString::replicate(pErrorMessage);
}

xercesc::DOMDocument* SeparatistaDocument::getDOMDocument() const
{
	return m_pDOMDocument;
}

void SeparatistaDocument::setDOMDocument(xercesc::DOMDocument *pDOMDocument)
{
	m_pDOMDocument = pDOMDocument;
}

const wchar_t* SeparatistaDocument::getPath() const
{
	return m_path;
}

void SeparatistaDocument::setPath(const wchar_t *pPath)
{
	if (m_path)
		XMLString::release(&m_path);

	m_path = XMLString::replicate(pPath);
}

typedef SeparatistaDocument* (*SeparatistaDocumentCreatorFunc)(xercesc::DOMDocument *pDocument);

template<class T> SeparatistaDocument* SeparatistaDocumentCreator(xercesc::DOMDocument *pDocument)
{
	return new T(pDocument);
}

SeparatistaDocument* SeparatistaDocument::getByDOMDocument(xercesc::DOMDocument* pDocument)
{
	DOMElement *pDocumentElement;
	const XMLCh *pNamespaceURI;

	std::unordered_map<std::wstring, SeparatistaDocumentCreatorFunc> documentCreatorMap(
	{
		{ DirectDebitDocument::NamespaceURI, SeparatistaDocumentCreator<DirectDebitDocument> }
	});

	// Get the document root element
	pDocumentElement = pDocument->getDocumentElement();
	if (!pDocumentElement)
		return NULL;

	// The document root element tag should be "Document"
	if (XMLString::compareString(L"Document", pDocumentElement->getTagName()) != 0)
		return NULL;

	// Find by namespace uri
	SeparatistaDocumentCreatorFunc func;
	pNamespaceURI = pDocumentElement->getNamespaceURI();
	if (!pNamespaceURI)
		return NULL;

	if ((func = documentCreatorMap[pNamespaceURI]) != NULL)
		return func(pDocument);

	return NULL;
}

time_t SeparatistaDocument::toTime(const wchar_t *pDateTime)
{
	XSValue::Status status;
	XSValue *pValue;
	std::tm tm;

	pValue = XSValue::getActualValue(pDateTime, XSValue::dt_dateTime, status);
	if (!pValue || status != XSValue::st_Init)
		return -1;

	tm.tm_year = pValue->fData.fValue.f_datetime.f_year - 1900;
	tm.tm_mon = pValue->fData.fValue.f_datetime.f_month - 1;
	tm.tm_mday = pValue->fData.fValue.f_datetime.f_day;
	tm.tm_hour = pValue->fData.fValue.f_datetime.f_hour;
	tm.tm_min = pValue->fData.fValue.f_datetime.f_min;
	tm.tm_sec = pValue->fData.fValue.f_datetime.f_milisec / 1000;

	return mktime(&tm);
}

long SeparatistaDocument::toLong(const wchar_t *pLong)
{
	XSValue::Status status;
	XSValue *pValue;

	if (!pLong)
		return 0;

	pValue = XSValue::getActualValue(pLong, XSValue::dt_long, status);
	if (!pValue || status != XSValue::st_Init)
		return 0;

	return  pValue->fData.fValue.f_long;
}

uint64_t SeparatistaDocument::toUInt64(const wchar_t *pUInt64)
{
	char *pValue;
	uint64_t ret = 0;

	if (!pUInt64)
		return 0;

	pValue = XMLString::transcode(pUInt64);
	ret = std::strtoull(pValue, NULL, 10);
	XMLString::release(&pValue);

	return ret;
}