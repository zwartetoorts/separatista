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

#ifndef SEPARATISTA_ERRORHANDLER_H
#define SEPARATISTA_ERRORHANDLER_H

namespace Separatista
{

class SeparatistaErrorHandler : public xercesc::ErrorHandler
{
public:
	SeparatistaErrorHandler();

	void warning(const xercesc::SAXParseException &e);
	void error(const xercesc::SAXParseException &e);
	void fatalError(const xercesc::SAXParseException &e);
	void resetErrors();
private:

};

};
#endif // !defined SEPARATISTA_ERRORHANDLER_H
