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

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/pain/directdebittransactioninformation.h"
#include "separatista/branchandfinancialinstitutionidentification.h"
#include "separatista/partyidentification.h"
#include "separatista/cashaccount.h"
#include "separatista/pain/paymenttypeinformation.h"

#ifndef SEPARATISTA_PAIN_PAYMENTINFORMATION_H
#define SEPARATISTA_PAIN_PAYMENTINFORMATION_H

namespace Separatista
{
	namespace pain_008_001
	{
		class SEPARATISTA_EXTERN PmtInf : public BranchElement, ElementListener
		{
		public:
			PmtInf();

			/**
			Destructor, will delete all added DrctDbtTxInf's
			*/
			~PmtInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator &DocumentIterator, const ErrorOptions errorOptions = ThrowExceptions);

			void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
			void elementDeleted(Element *pElement);

			void AddDrctDbtTxInf(DrctDbtTxInf *pDrctDbtTxInf);

			LeafElement m_PmtInfId;
			LeafElement m_PmtMtd;
			LeafElement m_NbOfTxs;
			LeafElement m_CtrlSum;
			PmtTpInf m_PmtTpInf;
			LeafElement m_ReqdColltnDt;
			PartyIdentification43 m_Cdtr;
			CashAccount24 m_CdtrAcct;
			BranchAndFinancialInstitutionIdentification5 m_CdtrAgt;
			LeafElement m_ChrgBr;
			PartyIdentification43 m_CdtrSchmeId;

		private:
			void calcSums();

			std::vector<DrctDbtTxInf*> m_DrctDbtTxInfs;
		};
	}
}

#endif // SEPARATISTA_PAIN_PAYMENTINFORMATION_H