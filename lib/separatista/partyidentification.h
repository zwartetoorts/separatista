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

#include <xercesc/dom/DOMDocument.hpp>

#include "separatista.h"
#include "branchelement.h"
#include "leafelement.h"

#ifndef SEPARATISTA_PARTYIDENTIFICATION_H
#define SEPARATISTA_PARTYIDENTIFICATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN PersonIdentificationSchemeName : public BranchElement
	{
	public:
		PersonIdentificationSchemeName::PersonIdentificationSchemeName(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		LeafElement m_Prtry;
	};

	class SEPARATISTA_EXTERN GenericPersonIdentification : public BranchElement
	{
	public:
		GenericPersonIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		LeafElement m_Id;
		PersonIdentificationSchemeName m_SchmeNm;
	};

	class SEPARATISTA_EXTERN PersonIdentification : public BranchElement
	{
	public:
		PersonIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		GenericPersonIdentification m_Othr;
	};

	class SEPARATISTA_EXTERN PartyChoice : public BranchElement
	{
	public:
		PartyChoice();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		PersonIdentification m_PrvtId;
	};

	class SEPARATISTA_EXTERN PartyIdentification : public BranchElement
	{
	public:
		PartyIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		LeafElement m_Nm;
		PartyChoice m_Id;
	};
}
#endif // SEPARATISTA_PARTYIDENTIFICATION_H
