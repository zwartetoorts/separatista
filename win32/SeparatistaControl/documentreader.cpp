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
#include <oleauto.h>
#include <comutil.h>

#include "documentreader.h"
#include "dispatch.cpp"

using namespace Separatista;

DocumentReader::DocumentReader(IUnknown* pUnknown)
:SepaControlDispatch<IDocumentReader>(pUnknown)
{
	m_pDocumentReader = new SeparatistaFileReader();
}

DocumentReader::~DocumentReader()
{
	if (m_pDocumentReader)
		delete m_pDocumentReader;
}

STDMETHODIMP DocumentReader::ReadDocument(BSTR path, SeparatistaFileReader::DocumentStatus *pStatus)
{
	if (!m_pDocumentReader)
		return E_UNEXPECTED;

	*pStatus = m_pDocumentReader->readDocument(path);

	return S_OK;
}

STDMETHODIMP DocumentReader::getStatus(SeparatistaFileReader::DocumentStatus *pStatus)
{
	if (!m_pDocumentReader)
		return E_UNEXPECTED;

	*pStatus = m_pDocumentReader->getStatus();

	return S_OK;
}

STDMETHODIMP DocumentReader::getErrorMessage(BSTR *pErrorMessage)
{
	if (!m_pDocumentReader)
		return E_UNEXPECTED;

	*pErrorMessage = _bstr_t(m_pDocumentReader->getErrorMessage()).Detach();

	return S_OK;
}

STDMETHODIMP DocumentReader::getPath(BSTR *pPath)
{
	if (!m_pDocumentReader)
		return E_UNEXPECTED;

	*pPath = _bstr_t(m_pDocumentReader->getPath()).Detach();

	return S_OK;
}