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
#include <xercesc/dom/DOMElement.hpp>
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

#include "separatista/separatista.h"
#include "separatista/pain/customerdirectdebitinitiation.h" 
#include "separatista/leafelement.h"
#include "separatista/documentreader.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

const wchar_t* CstmrDrctDbtInitn::NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.04");

CstmrDrctDbtInitn::CstmrDrctDbtInitn() :
BranchElement(TEXT("CstmrDrctDbtInitn")),
m_GrpHdr()
{
	DEBUG_METHOD
}

CstmrDrctDbtInitn::CstmrDrctDbtInitn(Separatista::DOMDocument *pDocument) :
BranchElement(TEXT("CstmrDrctDbtInitn")),
m_GrpHdr()
{
	DEBUG_METHOD
	fromDOMDocument(&DOMDocumentIterator(pDocument));
}

CstmrDrctDbtInitn::~CstmrDrctDbtInitn()
{
	DEBUG_METHOD
	// Delete all PmtInfs
	std::vector<PmtInf*>::iterator it;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
		delete (*it);
}

DOMElement* CstmrDrctDbtInitn::toDOMDocument(Separatista::DOMDocument *pDocument, DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	std::vector<PmtInf*>::iterator it;
	DOMElement *pElement = createElement(pDocument, pParent);

	if (pElement)
	{
		m_GrpHdr.toDOMDocument(pDocument, pElement);

		for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
			(*it)->toDOMDocument(pDocument, pElement, errorOptions);
	}

	return pElement;
}

void CstmrDrctDbtInitn::fromDOMDocument(DOMDocumentIterator *pDocumentIterator, const ErrorOptions errorOptions)
{
	DEBUG_METHOD
	PmtInf *pPmtInf;
	unsigned int pos;
	DOMElement *pElement;

	// First tag should be "document"
	pElement = pDocumentIterator->getCurrentElement();
	if (!pElement || xercesc::XMLString::compareString(pElement->getNodeName(), TEXT("Document")) != 0)
		return;
	pDocumentIterator->nextElement();

	if (compareTag(pDocumentIterator))
	{
		pDocumentIterator->nextElement();
		m_GrpHdr.fromDOMDocument(pDocumentIterator, errorOptions);

		while (pDocumentIterator->getCurrentElement() != NULL &&
			xercesc::XMLString::compareString(pDocumentIterator->getCurrentElement()->getNodeName(), TEXT("PmtInf")) == 0)
		{
			pos = pDocumentIterator->getPosition();
			pPmtInf = new PmtInf();
			if (pPmtInf)
			{
				pPmtInf->fromDOMDocument(pDocumentIterator, errorOptions);
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
	DEBUG_METHOD
	calcSum();
}

void CstmrDrctDbtInitn::elementDeleted(Element *pElement)
{
	DEBUG_METHOD
	calcSum();
}

void CstmrDrctDbtInitn::AddPmtInf(PmtInf *pPmtInf)
{
	DEBUG_METHOD
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
	DEBUG_METHOD
	std::vector<PmtInf*>::iterator it;

	for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
		elementList.addElement(*it);
}

PmtInf* CstmrDrctDbtInitn::getPmtInfById(const wchar_t *pId)
{
	DEBUG_METHOD
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
	DEBUG_METHOD
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
	DEBUG_METHOD
	// Create a DOM Document
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("LS"));
	DOMDocument *pDocument;
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

