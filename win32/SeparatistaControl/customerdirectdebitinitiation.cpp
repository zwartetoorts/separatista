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
#include <separatista/elementlist.h>

#include "dispatch.cpp"
#include "util.h"
#include "customerdirectdebitinitiation.h"
#include "documentreader.h"
#include "enumvariant.h"

CustomerDirectDebitInitiation::CustomerDirectDebitInitiation()
:SepaControlDispatch<ICustomerDirectDebitInitiation>(NULL)
{
	m_pCstmrDrctDbtInitn = new Separatista::CstmrDrctDbtInitn();
	m_bOwnCstmrDrctDbtInitn = true;
}

CustomerDirectDebitInitiation::~CustomerDirectDebitInitiation()
{
	if (m_bOwnCstmrDrctDbtInitn && m_pCstmrDrctDbtInitn)
		delete m_pCstmrDrctDbtInitn;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetMessageIdentification(BSTR *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.getTextValue()).Detach();

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetMessageIdentification(BSTR Value)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_MsgId.setValue(Value);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetCreationDateTime(DATE *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	return DateTypeFromStdTime(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.getDateValue(), pValue);
}

STDMETHODIMP CustomerDirectDebitInitiation::SetCreationDateTime(DATE Value)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	m_pCstmrDrctDbtInitn->m_GrpHdr.m_CreDtTm.setValue(StdTimeFromDateType(Value), true);

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetNumberOfTransactions(INT *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = m_pCstmrDrctDbtInitn->m_GrpHdr.m_NbOfTxs.getIntValue();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetControlSum(VARIANT *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL; 
	
	*pValue = _variant_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_CtrlSum.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::GetInititiatingPartyName(BSTR *pValue)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_FAIL;

	*pValue = _bstr_t(m_pCstmrDrctDbtInitn->m_GrpHdr.m_InitgPty.m_Nm.getTextValue()).Detach();
	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::SetInititiatingPartyName(BSTR Value)
{
	if (!m_pCstmrDrctDbtInitn)
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

STDMETHODIMP CustomerDirectDebitInitiation::Save(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

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
	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	if ((*pErrorCode = m_pCstmrDrctDbtInitn->SaveAs(Path)) == Separatista::IOErrorCode::Success)
		return S_OK;

	return E_FAIL;
}

STDMETHODIMP CustomerDirectDebitInitiation::Open(LONG hWnd, Separatista::IOErrorCode *pErrorCode)
{
	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

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
	Separatista::SeparatistaDocument *pDocument;

	*pErrorCode = Separatista::Unknown;

	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	reader.loadSchema(Separatista::CstmrDrctDbtInitn::NameSpaceURI);
	if ((*pErrorCode = reader.parseFile(Path)) == Separatista::IOErrorCode::Success)
	{
		pDocument = reader.getDocument();
		if (pDocument)
		{
			if (pDocument->getDocumentType() == Separatista::DocumentType::DT_CustomerDirectDebitDocument)
			{
				if (m_bOwnCstmrDrctDbtInitn && m_pCstmrDrctDbtInitn)
					delete m_pCstmrDrctDbtInitn;
				m_bOwnCstmrDrctDbtInitn = true;
				m_pCstmrDrctDbtInitn = (Separatista::CstmrDrctDbtInitn*)pDocument;
				return S_OK;
			}
			*pErrorCode = Separatista::Document_Invalid;
			delete pDocument;
		}
	}

	return E_FAIL;
}

STDMETHODIMP CustomerDirectDebitInitiation::PaymentInformationById(BSTR PaymentInformationIdentification, PaymentInformation **ppPaymentInformation)
{
	Separatista::PmtInf *pPmtInf;

	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	pPmtInf = m_pCstmrDrctDbtInitn->getPmtInfById(PaymentInformationIdentification);
	if (pPmtInf)
	{
		*ppPaymentInformation = new PaymentInformation(pPmtInf, this);
		(*ppPaymentInformation)->AddRef();
	}
	else
		*ppPaymentInformation = NULL;

	return S_OK;
}

STDMETHODIMP CustomerDirectDebitInitiation::_NewEnum(IUnknown **ppUnk)
{
	EnumVariant *pEnumVariant;
	PaymentInformation *pPaymentInformation;
	Separatista::ElementList list;

	if (!m_pCstmrDrctDbtInitn)
		return E_UNEXPECTED;

	pEnumVariant = new EnumVariant();
	if (!pEnumVariant)
		return E_OUTOFMEMORY;
	pEnumVariant->AddRef();

	// Add all PaymentInformations to the enumvariant
	m_pCstmrDrctDbtInitn->getPmtInfs(list);
	for (unsigned int i = 0; i < list.getElementCount(); i++)
	{
		pPaymentInformation = new PaymentInformation((Separatista::PmtInf*)list.getElement(i), this);
		pEnumVariant->Add(_variant_t(pPaymentInformation).Detach());
	}

	*ppUnk = pEnumVariant;
	return S_OK;
}
