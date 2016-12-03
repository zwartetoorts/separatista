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

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/branchelement.h"
#include "separatista/elementdescriptor.h"
#include "separatista/pain/groupheader.h"
#include "separatista/partyidentification.h"
#include "separatista/elementlist.h"

#ifndef SEPARATISTA_PAIN_CUSTOMERDIRECTDEBITINITIATION_H
#define SEPARATISTA_PAIN_CUSTOMERDIRECTDEBITINITIATION_H

namespace Separatista
{
	namespace pain_008_001
	{

		class SEPARATISTA_EXTERN CustomerDirectDebitInitiation : public BranchElement, public SeparatistaDocument, protected ElementListener
		{
		public:
			
			/**
				Writes the DOM document to a local file path
				@param pPath The path to write to
				@return Error code
				*/
			IOErrorCode saveAs(const wchar_t *pPath);

			/**
				ElementListener interface
			*/
			void elementValueChanged(Element *pElement, const wchar_t *pNewValue);

			void elementCreated(Element *pParent, Element *pChild);

			void elementDeleted(Element *pElement);

			/**
				SeparatistaDocument interface
			*/
			DocumentType getDocumentType() const { return DT_CustomerDirectDebitDocument; };

			virtual const wchar_t* getNamespaceURI() const = 0;
		protected:
			/// Construct an empty element
			CustomerDirectDebitInitiation(const ElementDescriptor *pElementDescriptor);

			/**
			Construct from a dom document.
			*/
			CustomerDirectDebitInitiation(const ElementDescriptor *pElementDescriptor, xercesc::DOMDocument *pDocument, const ErrorOptions errorOptions = ThrowExceptions);

			void calcSum();

			
		};

		class SEPARATISTA_EXTERN CustomerDirectDebitInitiationV02 : public CustomerDirectDebitInitiation
		{
		public:
			CustomerDirectDebitInitiationV02();

			CustomerDirectDebitInitiationV02(xercesc::DOMDocument *pDocument, const ErrorOptions errorOptions = ThrowExceptions);

			static const wchar_t *m_NameSpaceURI;

			static const ElementDescriptor m_CustomerDirectDebitInitiationV02[2];

			const wchar_t* getNamespaceURI() const {
				return m_NameSpaceURI;
			};

		};

		class SEPARATISTA_EXTERN CustomerDirectDebitInitiationV04 : public CustomerDirectDebitInitiation
		{
		public:
			CustomerDirectDebitInitiationV04();

			CustomerDirectDebitInitiationV04(xercesc::DOMDocument *pDocument, const ErrorOptions errorOptions = ThrowExceptions);
			
			static const wchar_t *m_NameSpaceURI;

			static const ElementDescriptor m_CustomerDirectDebitInitiationV04[2];

			const wchar_t* getNamespaceURI() const {
				return m_NameSpaceURI; };

		};
	}
}

#endif // SEPARATISTA_PAIN_CUSTOMERDIRECTDEBITINITIATION_H
