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

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation(IUnknown *pParent)
:SepaControlDispatch<ICustomerDirectDebitInitiation>(pParent)
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
		m_pCstmrDrctDbtInitn = new CstmrDrctDbtInitn(m_pDomDocument);
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

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.GetTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetMessageIdentification(BSTR Value)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.SetTextValue(Value);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetCreationDateTime(DATE *pValue)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	return DateTypeFromStdTime(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.GetDateValue(), pValue);
}

STDMETHODIMP CustomerDirectDebitInitiation::SetCreationDateTime(DATE Value)
{
	if (!m_pDomDocument || !m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.SetDateValue(StdTimeFromDateType(Value));
}