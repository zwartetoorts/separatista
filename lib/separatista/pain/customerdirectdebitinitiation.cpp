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
#include "separatista/xerces_types.h"
#include "separatista/pain/customerdirectdebitinitiation.h" 
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/documentreader.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"
#include "separatista/documentiterator.h"
#include "separatista/elementdescriptor.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

const wchar_t* CustomerDirectDebitInitiationV04::m_NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.04");

const ElementDescriptor CustomerDirectDebitInitiationV04::m_CustomerDirectDebitInitiationV04[] =
{
	{
		SEPARATISTA_TAG("GrpHdr"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(GroupHeader55)
	},
	{
		SEPARATISTA_TAG("PmtInf"),
		BranchElement::createElement,
		1,
		0,
		NULL,
		0,
		NULL
	}
};

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation(const ElementDescriptor *pElementDescriptor)
	:BranchElement(pElementDescriptor)
{
	DEBUG_METHOD;

	addElementListener(this);
}

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation(const ElementDescriptor *pElementDescriptor, xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	:BranchElement(pElementDescriptor)
{
	DEBUG_METHOD;
	
	fromDOMDocument(pDOMDocument->getDocumentElement()->getFirstElementChild(), errorOptions);
	addElementListener(this);
}

xercesc::DOMElement* CustomerDirectDebitInitiation::toDOMDocument(xercesc::DOMDocument *pDOMDocument, xercesc::DOMElement *pParent, const ErrorOptions errorOptions)
{
	DEBUG_METHOD;

	calcSum();
	return BranchElement::toDOMDocument(pDOMDocument, pParent, errorOptions);
}

void CustomerDirectDebitInitiation::calcSum()
{
	DEBUG_METHOD;

	double sum = 0;
	int count = 0;

	Element *pNbOfTxs = getElementByTag(TEXT("NbOfTxs"));
	Element *pCtrlSum = getElementByTag(TEXT("CtrlSum"));

	// If both elements aren't present, abort
	if (!pNbOfTxs && !pCtrlSum)
		return;

	// Calc both sum and count of transactions
	Element::TagKeyRange rangePmtInf = getAllByTagName(TEXT("PmtInf"));
	for (auto itPmtInf = rangePmtInf.m_begin; itPmtInf != rangePmtInf.m_end; itPmtInf++)
	{
		Element::TagKeyRange rangeDrctDbtTxInf = itPmtInf->second->getAllByTagName(TEXT("DrctDbtTxInf"));
		for (auto itDrctDbtTxInf = rangeDrctDbtTxInf.m_begin; itDrctDbtTxInf != rangeDrctDbtTxInf.m_end; itDrctDbtTxInf++)
		{
			++count;
			Element *pAmount = itDrctDbtTxInf->second->getElementByTag(TEXT("InstdAmt"));
			if (pAmount)
				sum += pAmount->getDoubleValue();
		}
	}

	pNbOfTxs->setValue(count, Element::AcceptValue);
	pCtrlSum->setValue(sum, Element::AcceptValue);
}

IOErrorCode CustomerDirectDebitInitiation::saveAs(const wchar_t *pPath)
{
	DEBUG_METHOD;

	// Create a DOM Document
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("LS"));
	xercesc::DOMDocument *pDocument;
	IOErrorCode ret;

	if (!pDomImpl)
		return IOErrorCode::Xerces;

	try
	{
		pDocument = pDomImpl->createDocument(
			getNamespaceURI(),
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
		LOG(e.getMessage());
		return IOErrorCode::Xerces;
	}
	
	return ret;
}

void CustomerDirectDebitInitiation::elementValueChanged(Element * pElement, const wchar_t * pNewValue)
{
	DEBUG_METHOD;

	calcSum();
}

void CustomerDirectDebitInitiation::elementCreated(Element * pParent, Element * pChild)
{
	DEBUG_METHOD;

	pChild->addElementListener(this);
}

void CustomerDirectDebitInitiation::elementDeleted(Element * pParent, Element * pChild)
{
	DEBUG_METHOD;

	calcSum();
}


CustomerDirectDebitInitiationV04::CustomerDirectDebitInitiationV04()
	:CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV04)
{

}

CustomerDirectDebitInitiationV04::CustomerDirectDebitInitiationV04(xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	:CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV04, pDOMDocument, errorOptions)
{

}

