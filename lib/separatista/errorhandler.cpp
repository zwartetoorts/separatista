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

#include <xercesc/sax/SAXParseException.hpp>

#include "separatista.h"
#include "errorhandler.h"

#include <string>

using namespace Separatista;
using namespace xercesc;

ErrorMessage::ErrorMessage(ErrorMessage::ErrorMessageType type)
{
	m_type = type;
	m_columnNumber = 0;
	m_lineNumber = 0;

	m_pErrorMessage = NULL;
	m_pPublicId = NULL;
	m_pSystemId = NULL;
}

ErrorMessage::ErrorMessage(ErrorMessage::ErrorMessageType type, const xercesc::SAXParseException &e)
{
	m_type = type;
	m_columnNumber = e.getColumnNumber();
	m_lineNumber = e.getLineNumber();

	m_pErrorMessage = XMLString::replicate(e.getMessage());
	m_pSystemId = XMLString::replicate(e.getSystemId());
	m_pPublicId = XMLString::replicate(e.getPublicId());
}

ErrorMessage::~ErrorMessage()
{
	if (m_pErrorMessage)
		XMLString::release(&m_pErrorMessage);

	if (m_pPublicId)
		XMLString::release(&m_pPublicId);

	if (m_pSystemId)
		XMLString::release(&m_pSystemId);
}

ErrorMessage::ErrorMessageType ErrorMessage::getType() const
{
	return m_type;
}

void ErrorMessage::setType(ErrorMessage::ErrorMessageType type)
{
	m_type = type;
}

const wchar_t* ErrorMessage::getErrorMessage() const
{
	return m_pErrorMessage;
}

void ErrorMessage::setErrorMessage(const wchar_t *pErrorMessage)
{
	if (m_pErrorMessage)
		XMLString::release(&m_pErrorMessage);

	m_pErrorMessage = XMLString::replicate(pErrorMessage);
}

const wchar_t* ErrorMessage::getPublicId() const
{
	return m_pPublicId;
}

void ErrorMessage::setPublicId(const wchar_t *pPublicId)
{
	if (m_pPublicId)
		XMLString::release(&m_pPublicId);

	m_pPublicId = XMLString::replicate(pPublicId);
}

const wchar_t* ErrorMessage::getSystemId() const
{
	return m_pSystemId;
}

void ErrorMessage::setSystemId(const wchar_t *pSystemId)
{
	if (m_pSystemId)
		XMLString::release(&m_pSystemId);

	m_pSystemId = XMLString::replicate(pSystemId);
}

size_t ErrorMessage::getColumnNumber() const
{
	return m_columnNumber;
}

void ErrorMessage::setColumnNumber(size_t columnNumber)
{
	m_columnNumber = columnNumber;
}

size_t ErrorMessage::getLineNumber() const
{
	return m_lineNumber;
}

void ErrorMessage::setLineNumber(size_t lineNumber)
{
	m_lineNumber = lineNumber;
}

ErrorReport::ErrorReport()
{
	m_pErrorList = NULL;
}

ErrorReport::ErrorReport(std::vector<ErrorMessage*> *pErrorList)
{
	setErrorList(pErrorList);
}

size_t ErrorReport::getCount() const
{
	if (!m_pErrorList)
		return 0;

	return m_pErrorList->size();
}

void ErrorReport::setErrorList(std::vector<ErrorMessage*> *pErrorList)
{
	m_pErrorList = pErrorList;
	reset();
}

void ErrorReport::reset()
{
	if (!m_pErrorList)
		return;

	m_iterator = m_pErrorList->begin();
}

const ErrorMessage* ErrorReport::getErrorMessage(size_t index)
{
	if (!m_pErrorList)
		return NULL;

	return (*m_pErrorList)[index];
}

const ErrorMessage* ErrorReport::getErrorMessage()
{
	if (!m_pErrorList)
		return NULL;

	if (m_iterator == m_pErrorList->end())
		return NULL;

	return (*m_iterator++);
}


SeparatistaErrorHandler::SeparatistaErrorHandler()
{
	m_pErrorList = NULL;
}

void SeparatistaErrorHandler::setErrorList(std::vector<ErrorMessage*> *pErrorList)
{
	m_pErrorList = pErrorList;
}

void SeparatistaErrorHandler::warning(const SAXParseException &e)
{
	addErrorMessage(ErrorMessage::M_WARNING, e);
}

void SeparatistaErrorHandler::error(const SAXParseException &e)
{
	addErrorMessage(ErrorMessage::M_ERROR, e);
}

void SeparatistaErrorHandler::fatalError(const SAXParseException& e)
{
	addErrorMessage(ErrorMessage::M_FATALERROR, e);
}

void SeparatistaErrorHandler::resetErrors()
{
	// Delete all ErrorMessages
	while (!m_pErrorList->empty())
	{
		delete m_pErrorList->back();
		m_pErrorList->pop_back();
	}
}

void SeparatistaErrorHandler::addErrorMessage(ErrorMessage::ErrorMessageType type, const SAXParseException &e)
{
	ErrorMessage *pMessage;

	if (!m_pErrorList)
		return;

	pMessage = new ErrorMessage(type, e);
	if (!pMessage)
		return;

	m_pErrorList->push_back(pMessage);
}
