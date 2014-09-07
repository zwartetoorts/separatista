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
#include <xercesc/dom/DOMDocument.hpp>

#include "separatista.h"
#include "directdebittransactioninformation.h"
#include "branchandfinancialinstitutionidentification.h"
#include "partyidentification.h"
#include "cashaccount.h"

#ifndef SEPARATISTA_PAYMENTINFORMATION_H
#define SEPARATISTA_PAYMENTINFORMATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN SvcLvl : public Element
	{
	public:
		SvcLvl();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Cd;
	};

	class SEPARATISTA_EXTERN LclInstrm : public Element
	{
	public:
		LclInstrm();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Cd;
	};

	class SEPARATISTA_EXTERN PmtTpInf : public Element
	{
	public:
		PmtTpInf();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		SvcLvl m_SvcLvl;
		LclInstrm m_LclInstrm;
		Element m_SeqTp;
	};

	class SEPARATISTA_EXTERN PmtInf : public Element, ElementListener
	{
	public:
		PmtInf();

		/**
		Destructor, will delete all added DrctDbtTxInf's
		*/
		~PmtInf();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
		void elementDeleted(Element *pElement);

		void AddDrctDbtTxInf(DrctDbtTxInf *pDrctDbtTxInf);

		Element m_PmtInfId;
		Element m_PmtMtd;
		Element m_NbOfTxs;
		Element m_CtrlSum;
		PmtTpInf m_PmtTpInf;
		Element m_ReqdColltnDt;
		PartyIdentification m_Cdtr;
		CashAccount m_CdtrAcct;
		BranchAndFinancialInstitutionIdentification m_CdtrAgt;
		Element m_ChrgBr;
		PartyIdentification m_CdtrSchmeId;

	private:
		void calcSums();

		std::vector<DrctDbtTxInf*> m_DrctDbtTxInfs;
	};

}

#endif // SEPARATISTA_PAYMENTINFORMATION_H