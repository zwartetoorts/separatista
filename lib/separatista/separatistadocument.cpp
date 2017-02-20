/***************************************************************************
*   Copyright (C) 2017 by Okkel Klaver   *
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
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/separatistadocument.h"
#include "separatista/documentregistry.h"
#include "separatista/debug/debug.h"

using namespace Separatista;

SeparatistaDocument::SeparatistaDocument(const wchar_t *pNameSpaceURI) :
	BranchElement(DocumentRegistry::getDocumentChildElementDescriptor(pNameSpaceURI)),
	m_NamespaceURI(pNameSpaceURI)
{
	DEBUG_METHOD;
}

SeparatistaDocument::~SeparatistaDocument()
{
	DEBUG_METHOD;

}

const wchar_t* SeparatistaDocument::getNamespaceURI() const
{
	return m_NamespaceURI.c_str();
}

IOErrorCode SeparatistaDocument::saveAs(const wchar_t *pPath)
{
	DEBUG_METHOD;

	// Create a DOM Document
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("LS"));
	xercesc::DOMDocument *pDocument;
	IOErrorCode ret;

	if (!pDomImpl)
		return IOErrorCode::Xerces;

	try
	{
		pDocument = pDomImpl->createDocument(
			getNamespaceURI(), 
			getTag(),
			NULL);

		if (toDOMDocument(pDocument, pDocument->getDocumentElement()))
		{
			xercesc::DOMLSSerializer *pSerializer = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSSerializer();
			xercesc::DOMLSOutput *pOutput = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSOutput();
			xercesc::LocalFileFormatTarget *pTarget = new xercesc::LocalFileFormatTarget(pPath);

			pOutput->setByteStream(pTarget);
			pOutput->setEncoding(TEXT("UTF-8"));
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMXMLDeclaration, true);
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
			pSerializer->write(pDocument, pOutput);
			pTarget->flush();

			delete pTarget;
			pOutput->release();
			pSerializer->release();

			ret = IOErrorCode::Success;
		}
		else
			ret = IOErrorCode::Separatista;
	}
	catch (const xercesc::DOMException &e)
	{
		LOG(e.getMessage());
		return IOErrorCode::Xerces;
	}

	return ret;
}
