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
#include "customerdirectdebitinitiation.h"
#include "separatista/documentreader.h"
#include "enumvariant.h"
#include "supporterrorinfo.h"

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation()
{
	m_nVersion = V2;
	m_pCustomerDirectDebitInitiation = new Separatista::pain_008_001::CustomerDirectDebitInitiationV02();
}

CustomerDirectDebitInitiation::~CustomerDirectDebitInitiation()
{
	if (m_pCustomerDirectDebitInitiation)
		delete m_pCustomerDirectDebitInitiation;
}

STDMETHODIMP CustomerDirectDebitInitiation::QueryInterface(REFIID riid, void** ppvObject)
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
	return SepaControlDispatch<ICustomerDirectDebitInitiation>::QueryInterface(riid, ppvObject);
}

STDMETHODIMP CustomerDirectDebitInitiation::Save(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
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
	ofn.lpstrFileTitle = TEXT("Save SEPA DirectDebit document as");
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

STDMETHODIMP CustomerDirectDebitInitiation::SaveAs(BSTR Path, Separatista::IOErrorCode *pErrorCode)
{
	if ((*pErrorCode = m_pCustomerDirectDebitInitiation->saveAs(Path)) == Separatista::IOErrorCode::Success)
			return S_OK;
	
	return E_FAIL;
}

STDMETHODIMP CustomerDirectDebitInitiation::Open(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
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
	ofn.lpstrFileTitle = TEXT("Open a SEPA DirectDebit document from");
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

STDMETHODIMP CustomerDirectDebitInitiation::OpenFrom(BSTR Path, Separatista::IOErrorCode *pErrorCode)
{
	Separatista::DocumentReader reader;
	Separatista::SeparatistaDocument *pDocument = NULL;
	std::wostringstream wos;
	int i;
	
	*pErrorCode = Separatista::Unknown;

	if ((*pErrorCode = reader.loadSchema(m_pCustomerDirectDebitInitiation->getNamespaceURI())) !=
		Separatista::IOErrorCode::Success)
		return E_FAIL;

	if ((*pErrorCode = reader.parseFile(Path)) == Separatista::IOErrorCode::Success)
	{
		try
		{
			pDocument = reader.getDocument();
			if (pDocument)
			{
				if (pDocument->getDocumentType() == Separatista::DocumentType::DT_CustomerDirectDebitDocument)
				{
					if (m_pCustomerDirectDebitInitiation)
						delete m_pCustomerDirectDebitInitiation;
					m_pCustomerDirectDebitInitiation = (Separatista::pain_008_001::CustomerDirectDebitInitiation*)pDocument;
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
			return SepaControlDispatch<ICustomerDirectDebitInitiation>::SetErrorInfo(e);
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

	return SepaControlDispatch<ICustomerDirectDebitInitiation>::SetErrorInfo(wos.str().data());
}

STDMETHODIMP CustomerDirectDebitInitiation::GetVersion(CustomerDirectDebitInitiation::DocumentVersion *pVersion)
{
	*pVersion = m_nVersion;
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetVersion(CustomerDirectDebitInitiation::DocumentVersion Version)
{
	Separatista::pain_008_001::CustomerDirectDebitInitiation *pCustomerDirectDebitInitiation;

	if (Version == m_nVersion)
		return S_OK;

	switch (Version)
	{
	case V2:
		pCustomerDirectDebitInitiation = new Separatista::pain_008_001::CustomerDirectDebitInitiationV02();
		break;
	case V4:
		pCustomerDirectDebitInitiation = new Separatista::pain_008_001::CustomerDirectDebitInitiationV04();
		break;
	default:
		return E_INVALIDARG;
	}

	if (pCustomerDirectDebitInitiation)
	{
		m_nVersion = Version;
		delete m_pCustomerDirectDebitInitiation;
		m_pCustomerDirectDebitInitiation = pCustomerDirectDebitInitiation;
		return S_OK;
	}

	return E_OUTOFMEMORY;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetNamespace(BSTR *pNamespace)
{
	*pNamespace = _bstr_t(m_pCustomerDirectDebitInitiation->getNamespaceURI()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetRootElement(IElement **ppElement)
{
	*ppElement = new Element(m_pCustomerDirectDebitInitiation);
	(*ppElement)->AddRef();
	return S_OK;
}