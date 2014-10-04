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

#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "separatista.h"
#include "customerdirectdebitinitiation.h"
#include "leafelement.h"
#include "documentreader.h"

using namespace Separatista;

const wchar_t* CstmrDrctDbtInitn::NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.02");

InitgPty::InitgPty() :
BranchElement(TEXT("InitgPty")),
m_Nm(TEXT("Nm"))
{

}

xercesc::DOMElement* InitgPty::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
		m_Nm.toDOMDocument(pDocument, pElement);

	return pElement;
}

void InitgPty::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_Nm.fromDOMDocument(pElementIterator);
	}
}

GrpHdr::GrpHdr() :
BranchElement(TEXT("GrpHdr")),
m_MsgId(TEXT("MsgId")),
m_CreDtTm(TEXT("CreDtTm")),
m_NbOfTxs(TEXT("NbOfTxs")),
m_CtrlSum(TEXT("CtrlSum")),
m_InitgPty()
{

}

xercesc::DOMElement* GrpHdr::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_MsgId.toDOMDocument(pDocument, pElement);
		m_CreDtTm.toDOMDocument(pDocument, pElement);
		m_NbOfTxs.toDOMDocument(pDocument, pElement);
		m_CtrlSum.toDOMDocument(pDocument, pElement);
		m_InitgPty.toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void GrpHdr::fromDOMDocument(DOMDocumentIterator *pElementIterator)
{
	if (compareTag(pElementIterator))
	{
		pElementIterator->nextElement();
		m_MsgId.fromDOMDocument(pElementIterator);
		m_CreDtTm.fromDOMDocument(pElementIterator);
		m_NbOfTxs.fromDOMDocument(pElementIterator);
		m_CtrlSum.fromDOMDocument(pElementIterator);
		m_InitgPty.fromDOMDocument(pElementIterator);
	}
}

CstmrDrctDbtInitn::CstmrDrctDbtInitn() :
BranchElement(TEXT("CstmrDrctDbtInitn")),
m_GrpHdr()
{

}

CstmrDrctDbtInitn::CstmrDrctDbtInitn(xercesc::DOMDocument *pDocument) :
BranchElement(TEXT("CstmrDrctDbtInitn")),
m_GrpHdr()
{
	fromDOMDocument(&DOMDocumentIterator(pDocument));
}

CstmrDrctDbtInitn::~CstmrDrctDbtInitn()
{
	// Delete all PmtInfs
	std::vector<PmtInf*>::iterator it;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
		delete (*it);
}

xercesc::DOMElement* CstmrDrctDbtInitn::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	std::vector<PmtInf*>::iterator it;
	xercesc::DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_GrpHdr.toDOMDocument(pDocument, pElement);

		for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
			(*it)->toDOMDocument(pDocument, pElement);
	}

	return pElement;
}

void CstmrDrctDbtInitn::fromDOMDocument(DOMDocumentIterator *pDocumentIterator)
{
	PmtInf *pPmtInf;
	unsigned int pos;
	xercesc::DOMElement *pElement;

	// First tag should be "document"
	pElement = pDocumentIterator->getCurrentElement();
	if (!pElement || xercesc::XMLString::compareString(pElement->getNodeName(), TEXT("Document")) != 0)
		return;
	pDocumentIterator->nextElement();

	if (compareTag(pDocumentIterator))
	{
		pDocumentIterator->nextElement();
		m_GrpHdr.fromDOMDocument(pDocumentIterator);

		while (pDocumentIterator->getCurrentElement() != NULL &&
			xercesc::XMLString::compareString(pDocumentIterator->getCurrentElement()->getNodeName(), TEXT("PmtInf")) == 0)
		{
			pos = pDocumentIterator->getPosition();
			pPmtInf = new PmtInf();
			if (pPmtInf)
			{
				pPmtInf->fromDOMDocument(pDocumentIterator);
				AddPmtInf(pPmtInf);
			}
			// Check for dead loop
			if (pos == pDocumentIterator->getPosition())
				break;
		}
	}
}

void CstmrDrctDbtInitn::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	calcSum();
}

void CstmrDrctDbtInitn::elementDeleted(Element *pElement)
{
	calcSum();
}

void CstmrDrctDbtInitn::AddPmtInf(PmtInf *pPmtInf)
{
	// Set listeners
	pPmtInf->m_NbOfTxs.setElementListener(this);
	pPmtInf->m_CtrlSum.setElementListener(this);

	// Set default value(s) for DirectDebit
	pPmtInf->m_PmtMtd.setValue(TEXT("DD"));

	m_PmtInfs.push_back(pPmtInf);

	calcSum();
}

void CstmrDrctDbtInitn::getPmtInfs(ElementList &elementList)
{
	std::vector<PmtInf*>::iterator it;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
		elementList.addElement(*it);
}

PmtInf* CstmrDrctDbtInitn::getPmtInfById(const wchar_t *pId)
{
	std::vector<PmtInf*>::iterator it;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
	{
		if (xercesc::XMLString::compareString(pId, (*it)->m_PmtInfId.getTextValue()) == 0)
			return (*it);
	}

	return NULL;
}

void CstmrDrctDbtInitn::calcSum()
{
	// Calc both sum and count of transactions
	std::vector<PmtInf*>::iterator it;
	int ntx = 0;
	double sum = 0.0;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
	{
		ntx += (*it)->m_NbOfTxs.getIntValue();
		sum += (*it)->m_CtrlSum.getDoubleValue();
	}

	m_GrpHdr.m_NbOfTxs.setValue(ntx);
	m_GrpHdr.m_CtrlSum.setValue(sum);
}

IOErrorCode CstmrDrctDbtInitn::SaveAs(const wchar_t *pPath)
{
	// Create a DOM Document
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("LS"));
	xercesc::DOMDocument *pDocument;
	IOErrorCode ret;

	if (!pDomImpl)
		return IOErrorCode::Xerces;

	try
	{
		pDocument = pDomImpl->createDocument(
			CstmrDrctDbtInitn::NameSpaceURI,
			TEXT("Document"),
			NULL);

		if (toDOMDocument(pDocument, pDocument->getDocumentElement()))
		{
			xercesc::DOMLSSerializer *pSerializer = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSSerializer();
			xercesc::DOMLSOutput *pOutput = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSOutput();
			xercesc::LocalFileFormatTarget *pTarget = new xercesc::LocalFileFormatTarget(pPath);

			pOutput->setByteStream(pTarget);
			pOutput->setEncoding(TEXT("UTF-8"));
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMXMLDeclaration, true);
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
			pSerializer->write(pDocument, pOutput);
			pTarget->flush();

			delete pTarget;
			pOutput->release();
			pSerializer->release();

			ret = IOErrorCode::Success;
		}
		else
			ret = IOErrorCode::Separatista;

	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		return IOErrorCode::Xerces;
	}

	return ret;
}

