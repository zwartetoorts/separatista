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

#include "ciban.h"
#include "dispatch.cpp"

CIBAN::CIBAN(IUnknown *pParent)
:SepaControlDispatch<IIBAN>(pParent)
{
	m_pIBAN = NULL;
	m_bOwnIBAN = false;
}

CIBAN::~CIBAN()
{
	if (m_pIBAN && m_bOwnIBAN)
		delete m_pIBAN;
}

CIBAN& CIBAN::operator = (Separatista::IBAN *pIBAN)
{
	// Free old iban if neccecary
	if (m_pIBAN && m_bOwnIBAN)
		delete m_pIBAN;

	m_pIBAN = pIBAN;
	m_bOwnIBAN = false;

	return *this;
}

STDMETHODIMP CIBAN::GetIBAN(BSTR *pIBAN)
{
	if (!m_pIBAN)
		return E_NOT_VALID_STATE;

	*pIBAN = _bstr_t(m_pIBAN->getIBAN()).Detach();

	return S_OK;
}

STDMETHODIMP CIBAN::SetIBAN(BSTR iban)
{
	if (!m_pIBAN)
	{
		m_pIBAN = new Separatista::IBAN();
		if (!m_pIBAN)
			return E_OUTOFMEMORY;
		m_bOwnIBAN = true;
	}

	*m_pIBAN = _bstr_t(iban);
	return S_OK;
}

STDMETHODIMP CIBAN::Check(VARIANT_BOOL *pValid)
{
	if (!m_pIBAN)
		*pValid = FALSE;
	else
		*pValid = (m_pIBAN->Check() ? TRUE : FALSE);
	return S_OK;
}