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

#include <string>
#include <sstream>
#include <unordered_map>
#include <windows.h>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLString.hpp>

#include "separatista.h"
#include "documentreader.h"
#include "customerdirectdebitinitiation.h"

using namespace Separatista;

DocumentReader::DocumentReader()
{
	m_pParser = new xercesc::XercesDOMParser();
	m_pDocument = NULL;
}

DocumentReader::~DocumentReader()
{
	if (m_pParser)
		delete m_pParser;
	if (m_pDocument)
		m_pDocument->release();
	resetErrors();
}

typedef SeparatistaDocument* (*SeparatistaDocumentCreatorFunc)(xercesc::DOMDocument *pDocument);

template<class T> SeparatistaDocument* SeparatistaDocumentCreator(xercesc::DOMDocument *pDOMDocument)
{
	SeparatistaDocument *pDocument;
	xercesc::DOMElement *pElement;

	pDocument = new T();
	if (pDocument)
	{
		pElement = pDOMDocument->getDocumentElement();
		if (pElement)
			pDocument->fromDOMDocument(pElement);
	}
	
	return pDocument;
}

SeparatistaDocument* DocumentReader::getDocument()
{
	xercesc::DOMElement *pDocumentElement;
	const XMLCh *pNamespaceURI;

	// Insert new supported document types here...
	std::unordered_map<std::wstring, SeparatistaDocumentCreatorFunc> documentCreatorMap(
	{
		{ CstmrDrctDbtInitn::NameSpaceURI, SeparatistaDocumentCreator<CstmrDrctDbtInitn> }
	});

	// Get the document root element
	pDocumentElement = m_pDocument->getDocumentElement();
	if (!pDocumentElement)
		return NULL;

	// The document root element tag should be "Document"
	if (xercesc::XMLString::compareString(TEXT("Document"), pDocumentElement->getTagName()) != 0)
		return NULL;

	// Find by namespace uri
	SeparatistaDocumentCreatorFunc func;
	pNamespaceURI = pDocumentElement->getNamespaceURI();
	if (!pNamespaceURI)
		return NULL;

	if ((func = documentCreatorMap[pNamespaceURI]) != NULL)
		return func(m_pDocument);

	return NULL;
}

IOErrorCode DocumentReader::parseFile(const wchar_t *pPath)
{	
	if (!m_pParser)
		return Platform;

	m_pParser->setErrorHandler(this);
	m_pParser->setDoNamespaces(true);
	
	// Parse the file
	try
	{
		m_pParser->parse(pPath);

		// Get the document
		if (m_pDocument)
			m_pDocument->release();
		m_pDocument = m_pParser->getDocument();
	}
	catch (const xercesc::XMLException &e)
	{
		SetDebugMessage(e.getMessage());
		return Xerces;
	}
	catch (const xercesc::DOMException &e)
	{
		SetDebugMessage(e.getMessage());
		return Document_Invalid;
	}
	catch (...)
	{
		return Unknown;
	}

	return Success;
}

int DocumentReader::getErrorCount() const
{
	return m_ErrorList.size();
}

const ErrorType::ErrorCode DocumentReader::getErrorCode(int index) const
{
	return m_ErrorList.at(index)->errorCode;
}

const wchar_t* DocumentReader::getErrorMessage(int index) const
{
	return m_ErrorList.at(index)->msg.data();

}

void DocumentReader::warning(const xercesc::SAXParseException &e)
{
	appendError(ErrorType::ETC_WARNING, e);
}

void DocumentReader::error(const xercesc::SAXParseException &e)
{
	appendError(ErrorType::ETC_ERROR, e);
}

void DocumentReader::fatalError(const xercesc::SAXParseException &e)
{
	appendError(ErrorType::ETC_FATALERROR, e);
}

void DocumentReader::resetErrors()
{
	std::vector<ErrorType*>::iterator it;

	for (it = m_ErrorList.begin(); it != m_ErrorList.end(); it++)
		delete *it;
}

void DocumentReader::appendError(ErrorType::ErrorCode etc, const xercesc::SAXParseException &e)
{
	std::wostringstream wos;
	ErrorType *pError = new ErrorType;

	pError->errorCode = etc;
	wos
		<< TEXT('(')
		<< e.getLineNumber()
		<< TEXT(',')
		<< e.getColumnNumber()
		<< TEXT(") ")
		<< e.getMessage();

	pError->msg = wos.str();
	m_ErrorList.push_back(pError);
}

