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

#include "element.h"
#include <vector>

namespace Separatista
{

class GroupHeader39 : public Element
{
public:
	static const wchar_t *GrpHdr;
	static const wchar_t *MsgId;
	static const wchar_t *CreDtTm;
	static const wchar_t *NbOfTxs;
	static const wchar_t *CtrlSum;

	GroupHeader39(DOMDocument *pDocument, DOMElement *pElement);
};

typedef GroupHeader39 GroupHeader;

class PaymentInstructionInformation4 : public Element
{
public:
	static const wchar_t *PmtInf;

	PaymentInstructionInformation4(DOMDocument *pDocument, DOMElement *pElement);

};

typedef PaymentInstructionInformation4 PaymentInstructionInformation;

class CustomerDirectDebitInitiationV02 : public Element
{
public:
	static const wchar_t *CstmrDrctDbtInitn;

	CustomerDirectDebitInitiationV02(DOMDocument *pDocument);

	GroupHeader& getGroupHeader();

private:
	std::vector<PaymentInstructionInformation*> m_pPmtInfs;
	std::vector<PaymentInstructionInformation*>::iterator m_iterator;
	GroupHeader m_GrpHdr;
};

typedef CustomerDirectDebitInitiationV02 CustomerDirectDebitInitiation;

};

#endif // !defined SEPARATISTA_DIRECTDEBITDOCUMENT_H
