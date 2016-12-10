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
#include "separatista/xerces_types.h"
#include "separatista/branchelement.h"
#include "separatista/documentreader.h"
#include "separatista/elementdescriptor.h"

#ifndef SEPARATISTA_CAMT_BANKTOCUSTOMERSTATEMENT_H
#define SEPARATISTA_CAMT_BANKTOCUSTOMERSTATEMENT_H

namespace Separatista
{
	namespace camt_053_001
	{
		class SEPARATISTA_EXTERN BankToCustomerStatement : public BranchElement, public SeparatistaDocument, protected ElementListener
		{
		public:
			/**
			ElementListener interface
			*/
			void elementValueChanged(Element *pElement, const wchar_t *pNewValue);

			void elementCreated(Element *pParent, Element *pChild);

			void elementDeleted(Element *pElement);

			/**
			SeparatistaDocument interface
			*/
			DocumentType getDocumentType() const { return DT_BankToCustomerStatement; };

		protected:
			/// Construct an empty element
			BankToCustomerStatement(const ElementDescriptor *pElementDescriptor);

			/**
			Construct from a dom document.
			*/
			BankToCustomerStatement(const ElementDescriptor *pElementDescriptor, xercesc::DOMDocument *pDocument, const ErrorOptions errorOptions = ThrowExceptions);

			void calcSum();
		};

		class SEPARATISTA_EXTERN BankToCustomerStatementV02 : public BankToCustomerStatement
		{
		public:
			BankToCustomerStatementV02();

			BankToCustomerStatementV02(xercesc::DOMDocument *pDocument, const ErrorOptions errorOptions = ThrowExceptions);

			static const wchar_t *m_NameSpaceURI;

			static const ElementDescriptor m_BankToCustomerStatementV02[2];

			const wchar_t* getNamespaceURI() const {
				return m_NameSpaceURI;
			};

		};
	}
}

#endif // !defined SEPARATISTA_CAMT_BANKTOCUSTOMERSTATEMENT_H
