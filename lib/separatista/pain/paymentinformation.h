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

#include <vector>

#include "separatista.h"
#include "xerces_types.h"
#include "directdebittransactioninformation.h"
#include "branchandfinancialinstitutionidentification.h"
#include "partyidentification.h"
#include "cashaccount.h"

#ifndef SEPARATISTA_PAYMENTINFORMATION_H
#define SEPARATISTA_PAYMENTINFORMATION_H

namespace Separatista
{
	namespace pain_008_001
	{
		class SEPARATISTA_EXTERN SvcLvl : public BranchElement
		{
		public:
			SvcLvl();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator);

			LeafElement m_Cd;
		};

		class SEPARATISTA_EXTERN LclInstrm : public BranchElement
		{
		public:
			LclInstrm();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator);

			LeafElement m_Cd;
		};

		class SEPARATISTA_EXTERN PmtTpInf : public BranchElement
		{
		public:
			PmtTpInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator);

			SvcLvl m_SvcLvl;
			LclInstrm m_LclInstrm;
			LeafElement m_SeqTp;
		};

		class SEPARATISTA_EXTERN PmtInf : public BranchElement, ElementListener
		{
		public:
			PmtInf();

			/**
			Destructor, will delete all added DrctDbtTxInf's
			*/
			~PmtInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator);

			void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
			void elementDeleted(Element *pElement);

			void AddDrctDbtTxInf(DrctDbtTxInf *pDrctDbtTxInf);

			LeafElement m_PmtInfId;
			LeafElement m_PmtMtd;
			LeafElement m_NbOfTxs;
			LeafElement m_CtrlSum;
			PmtTpInf m_PmtTpInf;
			LeafElement m_ReqdColltnDt;
			PartyIdentification m_Cdtr;
			CashAccount m_CdtrAcct;
			BranchAndFinancialInstitutionIdentification m_CdtrAgt;
			LeafElement m_ChrgBr;
			PartyIdentification m_CdtrSchmeId;

		private:
			void calcSums();

			std::vector<DrctDbtTxInf*> m_DrctDbtTxInfs;
		};
	}
}

#endif // SEPARATISTA_PAYMENTINFORMATION_H