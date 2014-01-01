/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
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

#include "enumvariant.h"
#include "cerrorreport.h"
#include "dispatch.cpp"

CErrorReport::CErrorReport(IUnknown *pParent)
:SepaControlDispatch<IErrorReport>(pParent)
{
	m_pErrorReport = NULL;
}

CErrorReport& CErrorReport::operator=(Separatista::ErrorReport* pErrorReport)
{
	m_pErrorReport = pErrorReport;

	return *this;
}

STDMETHODIMP CErrorReport::Count(long *plCount)
{
	if (!m_pErrorReport)
		return E_UNEXPECTED;

	*plCount = m_pErrorReport->getCount();

	return S_OK;
}

STDMETHODIMP CErrorReport::Item(VARIANT vIndex, BSTR *pErrorMessage)
{
	const Separatista::ErrorMessage *pMessage;
	_variant_t index(vIndex);

	if (!m_pErrorReport)
		return E_UNEXPECTED;

	if ((size_t)index >= m_pErrorReport->getCount())
		return DISP_E_BADINDEX;

	pMessage = m_pErrorReport->getErrorMessage((size_t)index);
	if (!pMessage)
		*pErrorMessage = _bstr_t().Detach();
	else
		*pErrorMessage = _bstr_t(pMessage->getErrorMessage()).Detach();

	return S_OK;
}

STDMETHODIMP CErrorReport::_NewEnum(IUnknown **ppUnk)
{
	EnumVariant *pEnumVariant;
	const Separatista::ErrorMessage *pMessage;

	*ppUnk = NULL;

	if (!m_pErrorReport)
		return E_UNEXPECTED;

	pEnumVariant = new EnumVariant();
	if (!pEnumVariant)
		return E_OUTOFMEMORY;
	pEnumVariant->AddRef();

	// Enum all messages
	while ((pMessage = m_pErrorReport->getErrorMessage()) != NULL)
		pEnumVariant->Add(_variant_t(formatErrorMessage()).Detach());

	*ppUnk = pEnumVariant;

	return S_OK;
}

_bstr_t CErrorReport::formatErrorMessage()
{
	std::wstring s;
	const Separatista::ErrorMessage *pMessage;

	if (m_pErrorReport)
	{
		pMessage = m_pErrorReport->getErrorMessage();
		if (pMessage)
		{
			s = pMessage->getErrorMessage();
		}
	}

	return _bstr_t(s.c_str());
}