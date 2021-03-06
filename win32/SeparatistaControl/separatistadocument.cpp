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

#include <sstream>
#include <comutil.h>

#include "dispatch.cpp"
#include "util.h"
#include "separatistadocument.h"
#include "separatista/documentreader.h"
#include "enumvariant.h"
#include "supporterrorinfo.h"
#include "separatista/camt/camt.053.001.02.h"
#include "separatista/pain/pain.001.001.03.h"
#include "separatista/pain/pain.008.001.02.h"

const wchar_t *SeparatistaDocument::m_pNamespaceTable[] =
{
	Separatista::camt_053_001_02::Namespace,
	Separatista::pain_001_001_03::Namespace,
	Separatista::pain_008_001_02::Namespace
};

SeparatistaDocument::SeparatistaDocument()
{
	m_pSeparatistaDocument = NULL;
	m_bEnableAutoMagic = TRUE;
	m_nDocumentNamespace = INVALID;
}

SeparatistaDocument::~SeparatistaDocument()
{
	if (m_pSeparatistaDocument)
		delete m_pSeparatistaDocument;
}

STDMETHODIMP SeparatistaDocument::QueryInterface(REFIID riid, void** ppvObject)
{
	SepaControlSupportErrorInfo *pSupportErrorInfo;
	
	*ppvObject = NULL;
	if (IsEqualIID(riid, IID_ISupportErrorInfo))
	{
		pSupportErrorInfo = new SepaControlSupportErrorInfo();
		if (!pSupportErrorInfo)
			return E_OUTOFMEMORY;
		pSupportErrorInfo->AddRef();
		*ppvObject = pSupportErrorInfo;
		return S_OK;
	}
	return SepaControlDispatch<ISeparatistaDocument>::QueryInterface(riid, ppvObject);
}

STDMETHODIMP SeparatistaDocument::Save(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
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
	ofn.lpstrFileTitle = TEXT("Save SEPA document as");
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.pvReserved = NULL;
	ofn.dwReserved = 0;
	ofn.FlagsEx = 0;

	if (GetSaveFileName(&ofn))
		return SaveAs(filename, pErrorCode);
	else
		*pErrorCode = Separatista::User;

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::SaveAs(BSTR Path, Separatista::IOErrorCode *pErrorCode)
{
	if (!m_pSeparatistaDocument)
		return E_INVALIDARG;

	if ((*pErrorCode = m_pSeparatistaDocument->saveAs(Path)) == Separatista::IOErrorCode::Success)
			return S_OK;
	
	return E_FAIL;
}

STDMETHODIMP SeparatistaDocument::Open(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
	OPENFILENAME ofn = { 0 };
	WCHAR filename[MAX_PATH + 1];
	std::wcscpy(filename, TEXT("sepa.xml"));

	if (!m_pSeparatistaDocument)
		return E_INVALIDARG;

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
	ofn.lpstrFileTitle = TEXT("Open a SEPA document from");
	ofn.Flags = OFN_FILEMUSTEXIST;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.pvReserved = NULL;
	ofn.dwReserved = 0;
	ofn.FlagsEx = 0;

	if (GetOpenFileName(&ofn))
		return OpenFrom(filename, pErrorCode);
	else
		*pErrorCode = Separatista::User;

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::OpenFrom(BSTR Path, Separatista::IOErrorCode *pErrorCode)
{
	Separatista::DocumentReader reader;
	Separatista::SeparatistaDocument *pDocument = NULL;
	std::wostringstream wos;
	int i;
	
	*pErrorCode = Separatista::Unknown;

	if (!m_pSeparatistaDocument)
		return E_INVALIDARG;

	if ((*pErrorCode = reader.loadSchema(m_pSeparatistaDocument->getNamespaceURI())) !=
		Separatista::IOErrorCode::Success)
		return E_FAIL;

	if ((*pErrorCode = reader.parseFile(Path)) == Separatista::IOErrorCode::Success)
	{
		try
		{
			pDocument = reader.getDocument();
			if (pDocument)
			{
				if (std::wcscmp(pDocument->getNamespaceURI(), m_pSeparatistaDocument->getNamespaceURI()) == 0)
				{
					if (m_pSeparatistaDocument)
						delete m_pSeparatistaDocument;
					m_pSeparatistaDocument = pDocument;
					return S_OK;
				}
				delete pDocument;
			}
		}
		catch (const Separatista::Exception &e)
		{
			if (pDocument)
				delete pDocument;
			*pErrorCode = Separatista::Separatista;
			return SepaControlDispatch<ISeparatistaDocument>::SetErrorInfo(e);
		}
		*pErrorCode = Separatista::Document_Invalid;
	}

	// Format first 10 errors, and report how many more
	for (i = 0; i < reader.getErrorCount() && i < 10; i++)
	{
		switch (reader.getErrorCode(i))
		{
		case Separatista::ErrorType::ETC_ERROR:
			wos << TEXT("Error: ");
			break;
		case Separatista::ErrorType::ETC_WARNING:
			wos << TEXT("Warning: ");
			break;
		case Separatista::ErrorType::ETC_FATALERROR:
			wos << TEXT("Fatal: ");
		default:
			wos << TEXT("Unknown: ");
		}
		wos << reader.getErrorMessage(i) << TEXT("\r\n");
	}
	// ... and xxx more
	i = reader.getErrorCount() - i;
	if (i > 0)
	{
		wos
			<< TEXT("... and ")
			<< i
			<< TEXT(" more");
	}

	return SepaControlDispatch<ISeparatistaDocument>::SetErrorInfo(wos.str().data());
}

STDMETHODIMP SeparatistaDocument::GetNamespaceText(BSTR *pNamespaceText)
{
	if (m_nDocumentNamespace >= 0 && m_nDocumentNamespace < MAX)
	{
		*pNamespaceText = _bstr_t(m_pNamespaceTable[m_nDocumentNamespace]).Detach();
	}
	else
	{
		*pNamespaceText = _bstr_t(TEXT("Unknown")).Detach();
	}

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::GetNamespace(DocumentNamespace *pNamespace)
{
	*pNamespace = m_nDocumentNamespace;
	return S_OK;
}

STDMETHODIMP SeparatistaDocument::SetNamespace(DocumentNamespace Namespace)
{
	if (m_nDocumentNamespace != Namespace)
	{
		m_nDocumentNamespace = INVALID;

		if (m_pSeparatistaDocument)
		{
			delete m_pSeparatistaDocument;
			m_pSeparatistaDocument = NULL;
		}

		return CreateDocument(Namespace);
	}

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::GetEnableAutoMagic(VARIANT_BOOL *pEnableAutoMagic)
{
	*pEnableAutoMagic = m_bEnableAutoMagic ? -1 : FALSE;

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::SetEnableAutoMagic(VARIANT_BOOL bEnableAutoMagic)
{
	// Create new document if automagics don't match
	// Comparing VARIANT_BOOl and bool primitive leads to compiler warnings
	if (bEnableAutoMagic && !m_bEnableAutoMagic || !bEnableAutoMagic && m_bEnableAutoMagic)
	{
		if (m_pSeparatistaDocument)
			delete m_pSeparatistaDocument;

		m_bEnableAutoMagic = bEnableAutoMagic ? true : false;
		return CreateDocument(m_nDocumentNamespace);
	}

	return S_OK;
}

STDMETHODIMP SeparatistaDocument::GetRootElement(IElement **ppElement)
{
	if (!m_pSeparatistaDocument)
		return E_NOT_VALID_STATE;

	*ppElement = new Element(m_pSeparatistaDocument);
	(*ppElement)->AddRef();
	return S_OK;
}

HRESULT SeparatistaDocument::CreateDocument(DocumentNamespace documentNamespace)
{
	if (documentNamespace >= 0 && documentNamespace <= MAX)
	{
		m_pSeparatistaDocument = new Separatista::SeparatistaDocument(m_pNamespaceTable[documentNamespace], m_bEnableAutoMagic);
		if (m_pSeparatistaDocument)
			m_nDocumentNamespace = documentNamespace;
	}
	else
	{
		m_pSeparatistaDocument = NULL;
		return E_FAIL;
	}
	return S_OK;
}
