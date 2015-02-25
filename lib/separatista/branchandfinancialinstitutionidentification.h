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

#include <windows.h>

#include "xerces_types.h"
#include "branchelement.h"
#include "leafelement.h"

#ifndef SEPARATISTA_BRANCHANDFINANCIALINSTITUTIONIDENTIFICATION_H
#define SEPARATISTA_BRANCHANDFINANCIALINSTITUTIONIDENTIFICATION_H

namespace Separatista
{

	class SEPARATISTA_EXTERN FinancialInstitutionIdentification8 : public BranchElement
	{
	public:
		FinancialInstitutionIdentification8(const ElementOptions options);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions);

		LeafElement m_BICFI;
	};

	class SEPARATISTA_EXTERN BranchAndFinancialInstitutionIdentification5 : public BranchElement
	{
	public:
		BranchAndFinancialInstitutionIdentification5(const wchar_t *pTag, const ElementOptions options);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions);

		FinancialInstitutionIdentification8 m_FinancialInstitutionIdentification;
	};

}
#endif // SEPARATISTA_BRANCHANDFINANCIALINSTITUTIONIDENTIFICATION_H
