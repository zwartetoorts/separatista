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

#include "separatista.h"
#include "xerces_types.h"
#include "choiceelement.h"
#include "branchelement.h"
#include "leafelement.h"

#ifndef SEPARATISTA_PARTYIDENTIFICATION_H
#define SEPARATISTA_PARTYIDENTIFICATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN PersonIdentificationSchemeName1Choice : public ChoiceElement<2>
	{
	public:
		PersonIdentificationSchemeName1Choice::PersonIdentificationSchemeName1Choice(const wchar_t *pTag);

		LeafElement m_Cd;
		LeafElement m_Prtry;
	};

	class SEPARATISTA_EXTERN GenericPersonIdentification1 : public BranchElement
	{
	public:
		GenericPersonIdentification1(const wchar_t *pTag);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator &documentIterator, const ErrorOptions errorOptions = ThrowExceptions);

		LeafElement m_Id;
		PersonIdentificationSchemeName1Choice m_SchmeNm;
	};

	class SEPARATISTA_EXTERN PersonIdentification5 : public BranchElement
	{
	public:
		PersonIdentification5(const wchar_t *pTag);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions);

		GenericPersonIdentification1 m_Othr;
	};

	class SEPARATISTA_EXTERN Party11Choice : public ChoiceElement<1>
	{
	public:
		Party11Choice();

		PersonIdentification5 m_PrvtId;
	};

	class SEPARATISTA_EXTERN PartyIdentification43 : public BranchElement
	{
	public:
		PartyIdentification43(const wchar_t *pTag);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

		void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions);

		LeafElement m_Nm;
		Party11Choice m_Id;
	};
}
#endif // SEPARATISTA_PARTYIDENTIFICATION_H
