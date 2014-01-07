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

