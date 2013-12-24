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

#include <windows.h>
#include "separatista.h"
#include "iban/iban.h"

#include <unordered_map>

using namespace xercesc;
using namespace Separatista;

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
		{ L"urn:iso:std:iso:20022:tech:xsd:pain.008.001.02", SeparatistaDocumentCreator<DirectDebitDocument> }
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