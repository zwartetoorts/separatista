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
#include "separatista/pain/paymentinstruction.h"
#include "separatista/leafelement.h"
#include "separatista/branchelement.h"
#include "separatista/documentreader.h"
#include "separatista/debug/debug.h"
#include "separatista/validator.h"
#include "separatista/elementdescriptor.h"

using namespace Separatista;
using namespace Separatista::pain_008_001;

const wchar_t* CustomerDirectDebitInitiationV02::m_NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.02");

const ElementDescriptor CustomerDirectDebitInitiationV02[] =
{
	{
		SEPARATISTA_TAG("GrpHdr"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(GroupHeader39)
	},
	{
		SEPARATISTA_TAG("PmtInf"),
		BranchElement::createElement,
		1,
		0,
		NULL,
		SEPARATISTA_ELEMENTS(PaymentInstruction4)
	}
};

const ElementDescriptor CustomerDirectDebitInitiationV02::m_CustomerDirectDebitInitiationV02[] =
{
	{
		SEPARATISTA_TAG("CstmrDrctDbtInitn"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(::CustomerDirectDebitInitiationV02)
	}
};

const wchar_t* CustomerDirectDebitInitiationV04::m_NameSpaceURI = TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.04");

const ElementDescriptor CustomerDirectDebitInitiationV04[] =
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
		SEPARATISTA_ELEMENTS(PaymentInstruction10)
	}
};

const ElementDescriptor CustomerDirectDebitInitiationV04::m_CustomerDirectDebitInitiationV04[] =
{
	{
		SEPARATISTA_TAG("CstmrDrctDbtInitn"),
		BranchElement::createElement,
		1,
		1,
		NULL,
		SEPARATISTA_ELEMENTS(::CustomerDirectDebitInitiationV04)
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

void CustomerDirectDebitInitiation::calcSum()
{
	DEBUG_METHOD;
	
	double sum = 0, pmtsum;
	int count = 0, pmtcount;

	Element *pGrpHdr = getElementByTag(TEXT("GrpHdr"));
	if (!pGrpHdr)
		return;

	Element *pNbOfTxs = pGrpHdr->createElementByTag(TEXT("NbOfTxs"));
	Element *pCtrlSum = pGrpHdr->createElementByTag(TEXT("CtrlSum"));

	// If both elements aren't present, abort
	if (!pNbOfTxs && !pCtrlSum)
		return;

	// Calc both sum and count of transactions
	Element::TagKeyRange rangePmtInf = getAllByTagName(TEXT("PmtInf"));
	for (auto itPmtInf = rangePmtInf.m_begin; itPmtInf != rangePmtInf.m_end; itPmtInf++)
	{
		pmtsum = 0;
		pmtcount = 0;
		Element::TagKeyRange rangeDrctDbtTxInf = itPmtInf->second->getAllByTagName(TEXT("DrctDbtTxInf"));
		for (auto itDrctDbtTxInf = rangeDrctDbtTxInf.m_begin; itDrctDbtTxInf != rangeDrctDbtTxInf.m_end; itDrctDbtTxInf++)
		{
			++pmtcount;
			Element *pAmount = itDrctDbtTxInf->second->getElementByTag(TEXT("InstdAmt"));
			if (pAmount)
				pmtsum += pAmount->getDoubleValue();
		}
		// Set CtrlSum abd NbOfTxs for PmtInf
		Element *pPmtNbOfTxs = itPmtInf->second->createElementByTag(TEXT("NbOfTxs"));
		if (pPmtNbOfTxs)
			pPmtNbOfTxs->setValue(pmtcount, Element::AcceptValue);
		Element *pPmtCrtlSum = itPmtInf->second->createElementByTag(TEXT("CtrlSum"));
		if (pPmtCrtlSum)
			pPmtCrtlSum->setValue(pmtsum, Element::AcceptValue);
		sum += pmtsum;
		count += pmtcount;
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

	// Call calcSum on the right child elements
	if (std::wcscmp(TEXT("InstdAmt"), pElement->getTag()) == 0)
	{
		calcSum();
	}
}

void CustomerDirectDebitInitiation::elementCreated(Element * pParent, Element * pChild)
{
	DEBUG_METHOD;

	// Set hooks on child elements

	if (std::wcscmp(TEXT("PmtInf"), pChild->getTag()) == 0)
	{
		pChild->addElementListener(this);
	}
	else if (std::wcscmp(TEXT("DrctDbtTxInf"), pChild->getTag()) == 0)
	{
		pChild->addElementListener(this);
	}
	else if (std::wcscmp(TEXT("InstdAmt"), pChild->getTag()) == 0)
	{
		pChild->addElementListener(this);
	}
	else if (std::wcscmp(TEXT("GrpHdr"), pChild->getTag()) == 0)
	{
		calcSum();
	}
}

void CustomerDirectDebitInitiation::elementDeleted(Element * pElement)
{
	DEBUG_METHOD;

	if (std::wcscmp(TEXT("PmtInf"), pElement->getTag()) == 0)
	{
		calcSum();
	}
	else if (std::wcscmp(TEXT("DrctDbtTxInf"), pElement->getTag()) == 0)
	{
		calcSum();
	}
	else if (std::wcscmp(TEXT("InstdAmt"), pElement->getTag()) == 0)
	{
		calcSum();
	}

}

CustomerDirectDebitInitiationV02::CustomerDirectDebitInitiationV02()
	:CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV02)
{
	DEBUG_METHOD;
}

CustomerDirectDebitInitiationV02::CustomerDirectDebitInitiationV02(xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	: CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV02, pDOMDocument, errorOptions)
{
	DEBUG_METHOD;
}

CustomerDirectDebitInitiationV04::CustomerDirectDebitInitiationV04()
	:CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV04)
{
	DEBUG_METHOD;
}


CustomerDirectDebitInitiationV04::CustomerDirectDebitInitiationV04(xercesc::DOMDocument *pDOMDocument, const ErrorOptions errorOptions)
	:CustomerDirectDebitInitiation(m_CustomerDirectDebitInitiationV04, pDOMDocument, errorOptions)
{
	DEBUG_METHOD;
}

