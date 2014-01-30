/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
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

#ifndef SEPARATISTA_DIRECTDEBITDOCUMENT_H
#define SEPARATISTA_DIRECTDEBITDOCUMENT_H

#include <vector>
#include "element.h"
#include "macro.h"
#include "paymentinstruction.h"
#include "groupheader.h"

namespace SeparatistaPrivate
{
	BEGIN_DECLARE_CLASS(CustomerDirectDebitInitiationV02)
	DECLARE_CHILD(GroupHeader55, GroupHeader, GrpHdr)
	DECLARE_TAG(CustomerDirectDebitInitiation, CstmrDrctDbtInitn)
	DECLARE_TAG(PaymentInformation, PmtInf)
	public:
		~CustomerDirectDebitInitiationV02();
		void addPaymentInstructionInformation(PaymentInstruction10 *pPmtInf);

		PaymentInstruction10* getPaymentInstructionInformation();

		// PaymentInformation methods
		/// True if we are the end of all PaymentInformations
		bool FEOF();
		/// Resets the internal pointer to the first PaymentInformation
		void moveFirst();
		/// Moves the internal pointer to the next PaymentInformation
		void moveNext();
		/// Get the number of PaymentInformations
		size_t getCount();

	private:
		std::vector<PaymentInstruction10*> m_pmtInfs;
		std::vector<PaymentInstruction10*>::iterator m_pmtInfIterator;
	END_DECLARE_CLASS

};

#endif // !defined SEPARATISTA_DIRECTDEBITDOCUMENT_H
