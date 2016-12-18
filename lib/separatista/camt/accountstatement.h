/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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

#include "separatista/separatista.h"
#include "separatista/elementdescriptor.h"

#ifndef SEPARATISTA_CAMT_ACCOUNTSTATEMENT_H
#define SEPARATISTA_CAMT_ACCOUNTSTATEMENT_H

namespace Separatista
{
	namespace camt_053_001
	{
		extern const ElementDescriptor DateAndDateTimeChoice[1];
		extern const ElementDescriptor AccountStatement2[9];
	}
}

#endif // !defined SEPARATISTA_CAMT_ACCOUNTSTATEMENT_H
