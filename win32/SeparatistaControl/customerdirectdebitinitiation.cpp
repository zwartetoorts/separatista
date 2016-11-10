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
:Element(new Separatista::pain_008_001::CustomerDirectDebitInitiationV04())
{

}

CustomerDirectDebitInitiation::~CustomerDirectDebitInitiation()
{
	delete (Separatista::pain_008_001::CustomerDirectDebitInitiation*)getElement();
}

STDMETHODIMP CustomerDirectDebitInitiation::QueryInterface(REFIID riid, void** ppvObject)
{
	SepaControlSupportErrorInfo *pSupportErrorInfo;
	
	*ppvObject = NULL;
	if (IsEqualIID(riid, __uuidof(ICustomerDirectDebitInitiation)))
	{
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
	else if (IsEqualIID(riid, IID_ISupportErrorInfo))
	{
		{
			pSupportErrorInfo = new SepaControlSupportErrorInfo();
			if (!pSupportErrorInfo)
				return E_OUTOFMEMORY;
			pSupportErrorInfo->AddRef();
			*ppvObject = pSupportErrorInfo;
			return S_OK;
		}
	}
	return Element::QueryInterface(riid, ppvObject);
}

STDMETHODIMP CustomerDirectDebitInitiation::Save(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
	if (!getElement())
		return E_NOT_VALID_STATE;

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
	Separatista::pain_008_001::CustomerDirectDebitInitiation *pCstmrDrctDbtInitn =
		(Separatista::pain_008_001::CustomerDirectDebitInitiation*)getElement();

	if (!pCstmrDrctDbtInitn)
		return E_NOT_VALID_STATE;

	if ((*pErrorCode = pCstmrDrctDbtInitn->saveAs(Path)) == Separatista::IOErrorCode::Success)
			return S_OK;
	
	return E_FAIL;
}

STDMETHODIMP CustomerDirectDebitInitiation::Open(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
	Separatista::pain_008_001::CustomerDirectDebitInitiation *pCstmrDrctDbtInitn =
		(Separatista::pain_008_001::CustomerDirectDebitInitiation*)getElement();

	if (!pCstmrDrctDbtInitn)
		return E_NOT_VALID_STATE;

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
	
	Separatista::pain_008_001::CustomerDirectDebitInitiation *pCstmrDrctDbtInitn =
		(Separatista::pain_008_001::CustomerDirectDebitInitiation*)getElement();

	*pErrorCode = Separatista::Unknown;

	if (!pCstmrDrctDbtInitn)
		return E_NOT_VALID_STATE;

	if ((*pErrorCode = reader.loadSchema(Separatista::pain_008_001::CustomerDirectDebitInitiationV04::m_NameSpaceURI)) !=
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
					delete pCstmrDrctDbtInitn;
					setElement((Separatista::pain_008_001::CustomerDirectDebitInitiation*)pDocument);
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
			return SetErrorInfo(e);
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

	return SetErrorInfo(wos.str().data());
}

STDMETHODIMP CustomerDirectDebitInitiation::GetNamespace(BSTR *pNamespace)
{
	Separatista::pain_008_001::CustomerDirectDebitInitiation *pCstmrDrctDbtInitn =
		(Separatista::pain_008_001::CustomerDirectDebitInitiation*)getElement();

	if (!pCstmrDrctDbtInitn)
		return E_NOT_VALID_STATE;

	*pNamespace = _bstr_t(pCstmrDrctDbtInitn->getNamespaceURI()).Detach();
	return S_OK;
}
