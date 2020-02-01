/***************************************************************************
*   Copyright (C) 2020 by Okkel Klaver   *
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
#include <xercesc/framework/LocalFileInputSource.hpp>

#include "separatista.h"
#include "documentreader.h"
#include "setup.h"
#include "debug/debug.h"
#include "internal/sstring.h"

#include <string>

using namespace Separatista;

// Load schema from file resource

IOErrorCode DocumentReader::loadSchema(const wchar_t *name)
{
	DEBUG_METHOD;
        
        if (!m_pParser)
		return Xerces;
        
        try
	{
                xercesc::LocalFileInputSource source(SEPARATISTA_SCHEMA_PATH, _SS(name));
		if (m_pParser->loadGrammar(source, xercesc::Grammar::SchemaGrammarType, true))
		{
			m_pParser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
			m_pParser->useCachedGrammarInParse(true);
			m_pParser->setLoadSchema(false);
			m_pParser->setDoSchema(true);
			m_pParser->setValidationConstraintFatal(true);
			return Success;
		}
	}
	catch (const xercesc::XMLException &e)
	{
		LOG(_SS(e.getMessage()));
	}

	return Xerces;
}