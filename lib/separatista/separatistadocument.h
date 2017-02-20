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

#include <vector>
#include <string>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/elementdescriptor.h"
#include "separatista/branchelement.h"

#ifndef SEPARATISTA_SEPARATISTADOCUMENT_H
#define SEPARATISTA_SEPARATISTADOCUMENT_H

namespace Separatista
{
	class SEPARATISTA_EXTERN SeparatistaDocument : public BranchElement
	{
	public:
		SeparatistaDocument(const wchar_t *pNamespace);

		/// Destructor
		~SeparatistaDocument();

		const wchar_t* getNamespaceURI() const;

		/**
		Writes the DOM document to a local file path
		@param pRootElement The element to create the document from
		@param pPath The path to write to
		@return Error code
		*/
		IOErrorCode saveAs(const wchar_t *pPath);

	private:
		std::wstring m_NamespaceURI;
		const ElementDescriptor *m_pElementDescriptor;
	};
}

#endif // !defined SEPARATISTA_SEPARATISTADOCUMENT_H
