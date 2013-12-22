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

using namespace xercesc;
using namespace Separatista;

DirectDebitDocument::DirectDebitDocument()
{
	m_pErrorMessage = NULL;
}

DirectDebitDocument::~DirectDebitDocument()
{
	if (m_pErrorMessage)
		XMLString::release(&m_pErrorMessage);
}

DirectDebitDocument::OpenStatus DirectDebitDocument::Open(const char *path)
{
	XercesDOMParser *parser;
	DirectDebitDocument::OpenStatus ret = OK;
	ErrorHandler *handler;

	parser = new XercesDOMParser();
	if (!parser)
		return E_MEMORY;

	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);

	handler = (ErrorHandler*)new HandlerBase();
	if (!handler)
	{
		delete parser;
		return E_MEMORY;
	}
	parser->setErrorHandler(handler);

	try
	{
		parser->parse(path);
	}
	catch (const XMLException &e)
	{
		m_pErrorMessage = XMLString::transcode(e.getMessage());
		ret = E_FORMAT;
	}
	catch (const DOMException &e)
	{
		m_pErrorMessage = XMLString::transcode(e.getMessage());
		ret = E_FORMAT;
	}
	catch (...)
	{
		ret = E_FORMAT;
	}
	
	m_pDOMDocument = parser->getDocument();
	delete parser;
	delete handler;

	return OK;
}
