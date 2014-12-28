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
#include "choiceelement.h" 

#ifndef SEPARATISTA_CASHACCOUNT_H
#define SEPARATISTA_CASHACCOUNT_H

namespace Separatista
{
	class SEPARATISTA_EXTERN AccountIdentification4Choice : public ChoiceElement<1>
	{
	public:
		AccountIdentification4Choice();

		LeafElement m_IBAN;
	};

	class SEPARATISTA_EXTERN CashAccount24 : public BranchElement
	{
	public:
		CashAccount24(const wchar_t *pTag);

		DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);
		
		AccountIdentification4Choice m_Id;
	};

}

#endif // SEPARATISTA_CONTROL_CASHACCOUNT_H
