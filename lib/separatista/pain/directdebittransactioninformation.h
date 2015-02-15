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

#include "separatista/xerces_types.h"
#include "separatista/branchelement.h"
#include "separatista/leafelement.h"
#include "separatista/branchandfinancialinstitutionidentification.h"
#include "separatista/partyidentification.h"
#include "separatista/cashaccount.h"

#ifndef SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H
#define SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H

namespace Separatista
{
	namespace pain_008_001
	{
		class SEPARATISTA_EXTERN PmtId : public BranchElement
		{
		public:
			PmtId();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			LeafElement m_EndToEndId;
		};

		class SEPARATISTA_EXTERN MndtRltdInf : public BranchElement
		{
		public:
			MndtRltdInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			LeafElement m_MndtId;
			LeafElement m_DtOfSgntr;
		};

		class SEPARATISTA_EXTERN DrctDbtTx : public BranchElement
		{
		public:
			DrctDbtTx();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			MndtRltdInf m_MndtRltdInf;
		};

		class SEPARATISTA_EXTERN RmtInf : public BranchElement
		{
		public:
			RmtInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			LeafElement m_Ustrd;
		};

		class SEPARATISTA_EXTERN DrctDbtTxInf : public BranchElement
		{
		public:
			DrctDbtTxInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			PmtId m_PmtId;
			LeafElement m_InstdAmt;
			DrctDbtTx m_DrctDbtTx;
			BranchAndFinancialInstitutionIdentification5 m_DbtrAgt;
			PartyIdentification43 m_Dbtr;
			CashAccount24 m_DbtrAcct;
			RmtInf m_RmtInf;
		};
	}
}

#endif