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

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

#include <vector>
#include <string>

#ifndef SEPARATISTA_ERRORHANDLER_H
#define SEPARATISTA_ERRORHANDLER_H

namespace Separatista
{

class SeparatistaErrorHandler : public xercesc::ErrorHandler
{
public:
	SeparatistaErrorHandler();

	/**
	Set the ErrorList to append messages to.
	Doesn't own the list, not freed on destruction.
	*/
	void setErrorList(std::vector<ErrorMessage*> *pErrorList);

	void warning(const xercesc::SAXParseException &e);
	void error(const xercesc::SAXParseException &e);
	void fatalError(const xercesc::SAXParseException &e);
	void resetErrors();
protected:
	void addErrorMessage(ErrorMessage::ErrorMessageType type, const xercesc::SAXParseException &e);

private:
	std::vector<ErrorMessage*> *m_pErrorList;
};

};
#endif // !defined SEPARATISTA_ERRORHANDLER_H
