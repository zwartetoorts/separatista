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

#include "customerdirectdebitinitiation.h"
#include "dispatch.cpp"
#include "util.h"

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation()
:SepaControlDispatch<ICustomerDirectDebitInitiation>(NULL)
{
	xercesc::DOMImplementation *pDomImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(TEXT("XML 1.0"));

	if (!pDomImpl)
	{
		m_pDomDocument = NULL;
		return;
	}

	try
	{
		m_pDomDocument = pDomImpl->createDocument(
			TEXT("urn:iso:std:iso:20022:tech:xsd:pain.008.001.02"),
			TEXT("Document"),
			NULL);
		m_pCstmrDrctDbtInitn = new CstmrDrctDbtInitn();
		if (m_pCstmrDrctDbtInitn)
		{
			// Set default values
			m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.setValue(std::time(NULL));
		}
	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		m_pDomDocument = NULL;
	}
}

CustomerDirectDebitInitiation::~CustomerDirectDebitInitiation()
{
	if (m_pDomDocument)
		m_pDomDocument->release();

	if (m_pCstmrDrctDbtInitn)
		delete m_pCstmrDrctDbtInitn;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetMessageIdentification(BSTR *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetMessageIdentification(BSTR Value)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.setValue(Value);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetCreationDateTime(DATE *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	return DateTypeFromStdTime(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.getDateValue(), pValue);
}

STDMETHODIMP CustomerDirectDebitInitiation::SetCreationDateTime(DATE Value)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.setValue(StdTimeFromDateType(Value));

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetNumberOfTransactions(INT *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = m_pCstmrDrctDbtInitn->m_GrpHdr.m_NbOfTxs.getIntValue();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetControlSum(VARIANT *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL; 
	
	*pValue = _variant_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CtrlSum.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetInititiatingPartyName(BSTR *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_InitgPty.m_Nm.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetInititiatingPartyName(BSTR Value)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
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

xercesc::DOMElement* CstmrDrctDbtInitn::toDOMDocument(xercesc::DOMDocument *pDocument, xercesc::DOMElement *pParent)
{
	xercesc::DOMElement *pElement = Element::toDOMDocument(pDocument, pParent, true);

	if (pElement)
		m_GrpHdr.toDOMDocument(pDocument, pElement);

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