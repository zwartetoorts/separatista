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

#include <windows.h>
#include <comutil.h>

#include "cdirectdebitdocument.h"
#include "dispatch.cpp"
#include "util.h"

CPartyIdentification::CPartyIdentification(Separatista::PartyIdentification *pPartyIdentification, IUnknown *pParent)
:SepaControlDispatch<IPartyIdentification>(pParent)
{
	m_pPartyIdentification = pPartyIdentification;
}

STDMETHODIMP CPartyIdentification::getName(BSTR *pName)
{
	if (!m_pPartyIdentification)
		return E_UNEXPECTED;

	*pName = _bstr_t(m_pPartyIdentification->getName()).Detach();
	return S_OK;
}

STDMETHODIMP CPartyIdentification::setName(BSTR Name)
{
	if (m_pPartyIdentification)
		return E_UNEXPECTED;

	m_pPartyIdentification->setName(_bstr_t(Name).Detach());
	return S_OK;
}

STDMETHODIMP CPartyIdentification::getPostalAddress(BSTR *pPostalAddress)
{
	if (!m_pPartyIdentification)
		return E_UNEXPECTED;

	*pPostalAddress = _bstr_t(m_pPartyIdentification->getPostalAddress()).Detach();
	return S_OK;
}

STDMETHODIMP CPartyIdentification::setPostalAddress(BSTR PostalAddress)
{
	if (m_pPartyIdentification)
		return E_UNEXPECTED;

	m_pPartyIdentification->setPostalAddress(_bstr_t(PostalAddress).Detach());
	return S_OK;
}

STDMETHODIMP CPartyIdentification::getIdentification(BSTR *pIdentification)
{
	if (!m_pPartyIdentification)
		return E_UNEXPECTED;

	*pIdentification = _bstr_t(m_pPartyIdentification->getIdentification()).Detach();
	return S_OK;
}

STDMETHODIMP CPartyIdentification::setIdentification(BSTR Identification)
{
	if (m_pPartyIdentification)
		return E_UNEXPECTED;

	m_pPartyIdentification->setIdentification(_bstr_t(Identification).Detach());
	return S_OK;
}

STDMETHODIMP CPartyIdentification::getCountryOfResidence(BSTR *pCountryOfResidence)
{
	if (!m_pPartyIdentification)
		return E_UNEXPECTED;

	*pCountryOfResidence = _bstr_t(m_pPartyIdentification->getCountryOfResidence()).Detach();
	return S_OK;
}

STDMETHODIMP CPartyIdentification::setCountryOfResidence(BSTR CountryOfResidence)
{
	if (m_pPartyIdentification)
		return E_UNEXPECTED;

	m_pPartyIdentification->setCountryOfResidence(_bstr_t(CountryOfResidence).Detach());
	return S_OK;
}

STDMETHODIMP CPartyIdentification::getContactDetails(BSTR *pContactDetails)
{
	if (!m_pPartyIdentification)
		return E_UNEXPECTED;

	*pContactDetails = _bstr_t(m_pPartyIdentification->getContactDetails()).Detach();
	return S_OK;
}

STDMETHODIMP CPartyIdentification::setContactDetails(BSTR ContactDetails)
{
	if (m_pPartyIdentification)
		return E_UNEXPECTED;

	m_pPartyIdentification->setContactDetails(_bstr_t(ContactDetails).Detach());
	return S_OK;
}

CDirectDebitDocument::CDirectDebitDocument(IUnknown* pUnknown)
:SepaControlDispatch<IDirectDebitDocument>(pUnknown)
{
	m_pDocument = new Separatista::DirectDebitDocument();
}

CDirectDebitDocument::CDirectDebitDocument(Separatista::DirectDebitDocument *pDocument, IUnknown *pUnknown)
: SepaControlDispatch<IDirectDebitDocument>(pUnknown)
{
	*this = pDocument;
}

CDirectDebitDocument& CDirectDebitDocument::operator = (Separatista::DirectDebitDocument *pDocument)
{
	m_pDocument = pDocument;

	return *this;
}

STDMETHODIMP CDirectDebitDocument::getMessageIdentification(BSTR *pMessageIdentification)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pMessageIdentification = _bstr_t(m_pDocument->getMessageIdentification()).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::setMessageIdentification(BSTR messageIdentification)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->setMessageIdentification(_bstr_t(messageIdentification).Detach());

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getCreationDateTime(DATE *pCreationDateTime)
{
	time_t t;

	if (!m_pDocument)
		return E_UNEXPECTED;

	t = m_pDocument->getCreationDateTime();
	if (t == -1)
		return E_FAIL;

	return DateTypeFromStdTime(t, pCreationDateTime);
}

STDMETHODIMP CDirectDebitDocument::setCreationDateTime(DATE creationDateTime)
{
	_variant_t v(creationDateTime);

	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->setCreationDateTime(((_bstr_t)v).Detach());

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getAuthorisation1(BSTR *pAuthorisation)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pAuthorisation = _bstr_t(m_pDocument->getAuthorisation(0)).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::setAuthorisation1(BSTR authorisation)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->setAuthorisation(0, _bstr_t(authorisation).Detach());

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getAuthorisation2(BSTR *pAuthorisation)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pAuthorisation = _bstr_t(m_pDocument->getAuthorisation(1)).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::setAuthorisation2(BSTR authorisation)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->setAuthorisation(1, _bstr_t(authorisation).Detach());

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getNumberOfTransactions(VARIANT *pNumberOfTransactions)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pNumberOfTransactions = _variant_t(m_pDocument->getNumberOfTransactions()).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getControlSum(VARIANT *pControlSum)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pControlSum = _variant_t(m_pDocument->getControlSum()).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getForwardingAgent(BSTR *pForwardingAgent)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	*pForwardingAgent = _bstr_t(m_pDocument->getForwardingAgent()).Detach();

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::setForwardingAgent(BSTR ForwardingAgent)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->setForwardingAgent(_bstr_t(ForwardingAgent).Detach());

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::getInitiatingParty(IPartyIdentification **ppPartyIdentification)
{
	Separatista::PartyIdentification *pSPId;

	if (!m_pDocument)
		return E_UNEXPECTED;

	pSPId = m_pDocument->getInitiatingParty();
	if (!pSPId)
		*ppPartyIdentification = NULL;
	else
	{
		*ppPartyIdentification = new CPartyIdentification(pSPId, this);
		if (*ppPartyIdentification == NULL)
			return E_OUTOFMEMORY;
	}

	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::FEOF(VARIANT_BOOL *pFEOF)
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	if (m_pDocument->FEOF())
		*pFEOF = -1;
	else
		*pFEOF = 0;
	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::moveFirst()
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->moveFirst();
	return S_OK;
}

STDMETHODIMP CDirectDebitDocument::moveNext()
{
	if (!m_pDocument)
		return E_UNEXPECTED;

	m_pDocument->moveNext();
	return S_OK;
}
