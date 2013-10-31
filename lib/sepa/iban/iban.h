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

#ifndef SEPARATISTA_IBAN_H
#define SEPARATISTA_IBAN_H

#include "separatista.h"

#include <string>

#ifdef IBAN_BUILD
#define IBAN_EXTERN
#else
#	ifdef IBAN_EXPORTS
#		define IBAN_EXTERN __declspec(dllexport)
#	else
#		define IBAN_EXTERN __declspec(dllimport)
#	endif
#endif

#define IBAN_MAX_LENGTH 34

namespace Separatista 
{

class IBAN_EXTERN IBAN 
{
public:
	IBAN& operator = (const char *iban);

private:
	std::string m_iban;
};

}

#endif // !defined SAPARATISTA_IBAN_H