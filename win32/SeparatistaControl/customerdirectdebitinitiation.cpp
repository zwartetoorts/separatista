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

#include <comutil.h>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "customerdirectdebitinitiation.h"
#include "dispatch.cpp"
#include "util.h"

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation()
:SepaControlDispatch<ICustomerDirectDebitInitiation>(NULL)
{
	m_pCstmrDrctDbtInitn = new CstmrDrctDbtInitn();
	m_bOwnCstmrDrctDbtInitn = true;
}

CustomerDirectDebitInitiation::~CustomerDirectDebitInitiation()
{
	if (m_bOwnCstmrDrctDbtInitn && m_pCstmrDrctDbtInitn)
		delete m_pCstmrDrctDbtInitn;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetMessageIdentification(BSTR *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetMessageIdentification(BSTR Value)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.setValue(Value);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetCreationDateTime(DATE *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	return DateTypeFromStdTime(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.getDateValue(), pValue);
}

STDMETHODIMP CustomerDirectDebitInitiation::SetCreationDateTime(DATE Value)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.setValue(StdTimeFromDateType(Value), true);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetNumberOfTransactions(INT *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = m_pCstmrDrctDbtInitn->m_GrpHdr.m_NbOfTxs.getIntValue();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetControlSum(VARIANT *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL; 
	
	*pValue = _variant_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CtrlSum.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetInititiatingPartyName(BSTR *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_InitgPty.m_Nm.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetInititiatingPartyName(BSTR Value)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_InitgPty.m_Nm.setValue(Value);
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::AddPaymentInformation(PaymentInformation *pPaymentInformation)
{
	if (!m_pCstmrDrctDbtInitn)
		return S_FALSE;

	m_pCstmrDrctDbtInitn->AddPmtInf(pPaymentInformation->GetPmtInf());
	pPaymentInformation->Detach();
	return S_OK;
}

InitgPty::InitgPty() :
Element(TEXT("InitgPty")),
m_Nm(TEXT("Nm"))
{

}

xercesc::DOMElement* InitgPty::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_Nm.toDOMDocument(pDocument, pElement);

	return pElement;
}

GrpHdr::GrpHdr() :
Element(TEXT("GrpHdr")),
m_MsgId(TEXT("MsgId")),
m_CreDtTm(TEXT("CreDtTm")),
m_NbOfTxs(TEXT("NbOfTxs")),
m_CtrlSum(TEXT("CtrlSum")),
m_InitgPty()
{

}

xercesc::DOMElement* GrpHdr::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

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

CstmrDrctDbtInitn::CstmrDrctDbtInitn() :
Element(TEXT("CstmrDrctDbtInitn")),
m_GrpHdr()
{

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
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
	{
		m_GrpHdr.toDOMDocument(pDocument, pElement);

		for (it = m_PmtInfs.begin(); it != m_PmtInfs.end(); it++)
			(*it)->toDOMDocument(pDocument, pElement);
	}

	return pElement;
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

STDMETHODIMP CustomerDirectDebitInitiation::Save(LONG hWnd)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	OPENFILENAME ofn = { 0 };
	WCHAR filename[MAX_PATH + 1];
	std::wcscpy(filename, TEXT("sepa.xml"));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = (HWND)hWnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = TEXT("All files\0*.*\0");
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = TEXT("Save SEPA DirectDebit document as");
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.pvReserved = NULL;
	ofn.dwReserved = 0;
	ofn.FlagsEx = 0;

	if (GetSaveFileName(&ofn))
		return SaveAs(filename);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SaveAs(BSTR Path)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	// Create a DOM Document
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("LS"));
	xercesc::DOMDocument *pDocument;
	HRESULT ret;

	if (!pDomImpl)
		return E_FAIL;

	try
	{
		pDocument = pDomImpl->createDocument(
			TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.02"),
			TEXT("Document"),
			NULL);

		if (m_pCstmrDrctDbtInitn->toDOMDocument(pDocument, pDocument->getDocumentElement()))
		{
			xercesc::DOMLSSerializer *pSerializer = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSSerializer();
			xercesc::DOMLSOutput *pOutput = ((xercesc::DOMImplementationLS*)pDomImpl)->createLSOutput();
			xercesc::LocalFileFormatTarget *pTarget = new xercesc::LocalFileFormatTarget(Path);

			pOutput->setByteStream(pTarget);
			pOutput->setEncoding(TEXT("UTF-8"));
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMXMLDeclaration, true);
			pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
			pSerializer->write(pDocument, pOutput);
			pTarget->flush();

			delete pTarget;
			pOutput->release();
			pSerializer->release();

			ret = S_OK;
		}
		else
			ret = E_FAIL;

	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		return E_FAIL;
	}

	return ret;
}
