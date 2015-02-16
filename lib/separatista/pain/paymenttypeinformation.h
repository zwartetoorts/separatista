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

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"

#ifndef SEPARATISTA_PAIN_PAYMENTTYPEINFORMATION_H
#define SEPARATISTA_PAIN_PAYMENTTYPEINFORMATION_H

namespace Separatista
{
	namespace pain_008_001
	{
		class SEPARATISTA_EXTERN SvcLvl : public BranchElement
		{
		public:
			SvcLvl();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			LeafElement m_Cd;
		};

		class SEPARATISTA_EXTERN LclInstrm : public BranchElement
		{
		public:
			LclInstrm();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			LeafElement m_Cd;
		};

		class SEPARATISTA_EXTERN PmtTpInf : public BranchElement
		{
		public:
			PmtTpInf();

			DOMElement* toDOMDocument(DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions = ThrowExceptions);

			void fromDOMDocument(DOMDocumentIterator *pElementIterator, const ErrorOptions errorOptions = ThrowExceptions);

			SvcLvl m_SvcLvl;
			LclInstrm m_LclInstrm;
			LeafElement m_SeqTp;
		};
	}
}

#endif // !defined SEPARATISTA_PAIN_PAYMENTTYPEINFORMATION_H
