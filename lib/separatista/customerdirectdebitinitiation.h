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
#include <xercesc/dom/DOMNodeIterator.hpp>

#include "separatista.h"
#include "element.h"
#include "paymentinformation.h"
#include "elementlist.h"

#ifndef SEPARATISTA_CUSTOMERDIRECTDEBITINITIATION_H
#define SEPARATISTA_CUSTOMERDIRECTDEBITINITIATION_H

namespace Separatista
{
	class SEPARATISTA_EXTERN InitgPty : public BranchElement
	{
	public:
		InitgPty();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		LeafElement m_Nm;
	};

	class SEPARATISTA_EXTERN GrpHdr : public BranchElement
	{
	public:
		GrpHdr();

		GrpHdr(const xercesc::DOMElement *pParent);

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent);

		void fromDOMDocument(DOMDocumentIterator *pElementIterator);

		LeafElement m_MsgId;
		LeafElement m_CreDtTm;
		LeafElement m_NbOfTxs;
		LeafElement m_CtrlSum;
		InitgPty m_InitgPty;

	};

	class SEPARATISTA_EXTERN CstmrDrctDbtInitn : public BranchElement, protected ElementListener, public SeparatistaDocument
	{
	public:
		CstmrDrctDbtInitn();

		/**
			Construct from a dom document.
		*/
		CstmrDrctDbtInitn(xercesc::DOMDocument *pDocument);

		/**
		Destructor, will delete all added PmtInf's
		*/
		~CstmrDrctDbtInitn();

		xercesc::DOMElement* toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent = NULL);

		void fromDOMDocument(DOMDocumentIterator *pDocumentIterator);

		void elementValueChanged(Element *pElement, const wchar_t *pNewValue);

		void elementDeleted(Element *pElement);

		GrpHdr m_GrpHdr;

		void AddPmtInf(PmtInf *pPmtInf);

		void getPmtInfs(ElementList &elementList);

		/**
			Writes the DOM document to a local file path
			@param pPath The path to write to
			@return Error code
		*/
		IOErrorCode SaveAs(const wchar_t *pPath);

		/**
			SeparatistaDocument interface
		*/
		DocumentType getDocumentType() const { return DT_CustomerDirectDebitDocument; };

		static const wchar_t *NameSpaceURI;

	private:
		void calcSum();

		std::vector<PmtInf*> m_PmtInfs;
	};

}

#endif // SEPARATISTA_CUSTOMERDIRECTDEBITINITIATION_H
