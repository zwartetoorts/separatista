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
}

typedef SeparatistaDocument* (*SeparatistaDocumentCreatorFunc)(xercesc::DOMDocument *pDocument);

template<class T> SeparatistaDocument* SeparatistaDocumentCreator(xercesc::DOMDocument *pDocument)
{
	return new T(pDocument);
}

SeparatistaDocument* DocumentReader::getDocument()
{
	xercesc::DOMElement *pDocumentElement;
	const XMLCh *pNamespaceURI;

	std::unordered_map<std::wstring, SeparatistaDocumentCreatorFunc> documentCreatorMap(
	{
		{ CstmrDrctDbtInitn::NameSpaceURI, SeparatistaDocumentCreator<CstmrDrctDbtInitn> }
	});

	// Get the document root element
	pDocumentElement = m_pDocument->getDocumentElement();
	if (!pDocumentElement)
		return NULL;

	// The document root element tag should be "Document"
	if (xercesc::XMLString::compareString(L"Document", pDocumentElement->getTagName()) != 0)
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
