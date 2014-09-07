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
#include "element.h"

#ifndef SEPARATISTA_PARTYIDENTIFICATION_H
#define SEPARATISTA_PARTYIDENTIFICATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN PersonIdentificationSchemeName : public Element
	{
	public:
		PersonIdentificationSchemeName::PersonIdentificationSchemeName(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Prtry;
	};

	class SEPARATISTA_EXTERN GenericPersonIdentification : public Element
	{
	public:
		GenericPersonIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Id;
		PersonIdentificationSchemeName m_SchmeNm;
	};

	class SEPARATISTA_EXTERN PersonIdentification : public Element
	{
	public:
		PersonIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		GenericPersonIdentification m_Othr;
	};

	class SEPARATISTA_EXTERN PartyChoice : public Element
	{
	public:
		PartyChoice();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		PersonIdentification m_PrvtId;
	};

	class SEPARATISTA_EXTERN PartyIdentification : public Element
	{
	public:
		PartyIdentification(const wchar_t *pTag);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Nm;
		PartyChoice m_Id;
	};
}
#endif // SEPARATISTA_PARTYIDENTIFICATION_H
