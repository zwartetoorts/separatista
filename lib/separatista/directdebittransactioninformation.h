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
#include "element.h"
#include "branchandfinancialinstitutionidentification.h"
#include "partyidentification.h"
#include "cashaccount.h"

#ifndef SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H
#define SEPARATISTA_DIRECTDEBITTRANSACTIONINFORMATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN PmtId : public Element
	{
	public:
		PmtId();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_EndToEndId;
	};

	class SEPARATISTA_EXTERN MndtRltdInf : public Element
	{
	public:
		MndtRltdInf();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_MndtId;
		Element m_DtOfSgntr;
	};

	class SEPARATISTA_EXTERN DrctDbtTx : public Element
	{
	public:
		DrctDbtTx();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		MndtRltdInf m_MndtRltdInf;
	};

	class SEPARATISTA_EXTERN RmtInf : public Element
	{
	public:
		RmtInf();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		Element m_Ustrd;
	};

	class SEPARATISTA_EXTERN DrctDbtTxInf : public Element
	{
	public:
		DrctDbtTxInf();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		PmtId m_PmtId;
		Element m_InstdAmt;
		DrctDbtTx m_DrctDbtTx;
		BranchAndFinancialInstitutionIdentification m_DbtrAgt;
		PartyIdentification m_Dbtr;
		CashAccount m_DbtrAcct;
		RmtInf m_RmtInf;
	};

}

#endif