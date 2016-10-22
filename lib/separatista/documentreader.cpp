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
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "separatista.h"
#include "xerces_types.h"
#include "documentreader.h"
#include "pain/customerdirectdebitinitiation.h"
#include "debug/debug.h"

using namespace Separatista;

/**
	Private wrapper for mapping xerces class ErrorHandler.
*/

class DocumentReaderErrorHandler : public xercesc::ErrorHandler
{
public:
	DocumentReader *m_pDocumentReader;

	DocumentReaderErrorHandler(DocumentReader *pDocumentReader)
	{
		DEBUG_METHOD
		m_pDocumentReader = pDocumentReader; 
	};

	/// @see SAXParseException
	void warning(const SAXParseException &e)
	{
		DEBUG_METHOD
		m_pDocumentReader->warning(e);
	};

	/// @see SAXParseException
	void error(const SAXParseException &e)
	{
		DEBUG_METHOD
		m_pDocumentReader->error(e);
	};

	/// @see SAXParseException
	void fatalError(const SAXParseException &e)
	{
		DEBUG_METHOD
		m_pDocumentReader->fatalError(e);
	};

	/// @see SAXParseException
	void resetErrors()
	{
		DEBUG_METHOD
		m_pDocumentReader->resetErrors();
	};
};

DocumentReader::DocumentReader()
{
	DEBUG_METHOD
	m_pParser = new xercesc::XercesDOMParser();
	m_pDocument = NULL;
}

DocumentReader::~DocumentReader()
{
	DEBUG_METHOD
	if (m_pParser)
		delete m_pParser;
	resetErrors();
}

typedef SeparatistaDocument* (*SeparatistaDocumentCreatorFunc)(xercesc::DOMDocument *pDocument);

template<class T> SeparatistaDocument* SeparatistaDocumentCreator(xercesc::DOMDocument *pDOMDocument)
{
	DEBUG_METHOD;

	SeparatistaDocument *pDocument = new T(pDOMDocument);
	return pDocument;
}

SeparatistaDocument* DocumentReader::getDocument()
{
	DEBUG_METHOD
	xercesc::DOMElement *pDocumentElement;
	const XMLCh *pNamespaceURI;

	// Insert new supported document types here...
	std::unordered_map<std::wstring, SeparatistaDocumentCreatorFunc> documentCreatorMap(
	{
		{ pain_008_001::CustomerDirectDebitInitiationV04::NameSpaceURI, SeparatistaDocumentCreator<pain_008_001::CustomerDirectDebitInitiationV04> }
	});

	// Check for document
	if (!m_pDocument)
		return NULL;

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
	DEBUG_METHOD
	DocumentReaderErrorHandler handler(this);

	if (!m_pParser)
		return Platform;

	m_pParser->setErrorHandler(&handler);
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
		LOG(e.getMessage());
		return Xerces;
	}
	catch (const xercesc::DOMException &e)
	{
		LOG(e.getMessage());
		return Document_Invalid;
	}
	catch (...)
	{
		return Unknown;
	}

	return m_pDocument ? Success : Document_Invalid;
}

int DocumentReader::getErrorCount() const
{
	DEBUG_METHOD
	return m_ErrorList.size();
}

const ErrorType::ErrorCode DocumentReader::getErrorCode(int index) const
{
	DEBUG_METHOD
	return m_ErrorList.at(index)->errorCode;
}

const wchar_t* DocumentReader::getErrorMessage(int index) const
{
	DEBUG_METHOD
	return m_ErrorList.at(index)->msg.data();

}

void DocumentReader::warning(const xercesc::SAXParseException &e)
{
	DEBUG_METHOD
	appendError(ErrorType::ETC_WARNING, e);
}

void DocumentReader::error(const xercesc::SAXParseException &e)
{
	DEBUG_METHOD
	appendError(ErrorType::ETC_ERROR, e);
}

void DocumentReader::fatalError(const xercesc::SAXParseException &e)
{
	DEBUG_METHOD
	appendError(ErrorType::ETC_FATALERROR, e);
}

void DocumentReader::resetErrors()
{
	DEBUG_METHOD
	std::vector<ErrorType*>::iterator it;

	for (it = m_ErrorList.begin(); it != m_ErrorList.end(); it++)
		delete *it;
}

void DocumentReader::appendError(ErrorType::ErrorCode etc, const xercesc::SAXParseException &e)
{
	DEBUG_METHOD
	std::wostringstream wos;
	ErrorType *pError = new ErrorType;

	pError->errorCode = etc;
	wos
		<< TEXT("@(")
		<< e.getLineNumber()
		<< TEXT(", ")
		<< e.getColumnNumber()
		<< TEXT(") ")
		<< e.getMessage();

	pError->msg = wos.str();
	m_ErrorList.push_back(pError);
}

