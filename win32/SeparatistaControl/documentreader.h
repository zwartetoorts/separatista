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

#include "windows.h"

#include "cdirectdebitdocument.h"
#include "cerrorreport.h"
#include "separatista.h"
#include "dispatch.h"

#ifndef SEPARATISTA_DOCUMENTREADER_H
#define SEPARATISTA_DOCUMENTREADER_H

// {6A9512FC-19BF-4F95-83D9-A8A36B1DF018}
DEFINE_GUID(IID_DocumentReader ,
	0x6a9512fc, 0x19bf, 0x4f95, 0x83, 0xd9, 0xa8, 0xa3, 0x6b, 0x1d, 0xf0, 0x18);

// {3FF1D4F5-2C70-4A78-ADCB-88C218E23C91}
DEFINE_GUID(CLSID_DOCUMENTREADER ,
	0x3ff1d4f5, 0x2c70, 0x4a78, 0xad, 0xcb, 0x88, 0xc2, 0x18, 0xe2, 0x3c, 0x91);

struct IDocumentReader : public IDispatch
{
	// IDispatch
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) PURE;
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo) PURE;
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) PURE;
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) PURE;
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) PURE;
	STDMETHOD(ReadDocument)(BSTR path, Separatista::SeparatistaFileReader::DocumentStatus *pStatus) PURE;
	STDMETHOD(getStatus)(Separatista::SeparatistaFileReader::DocumentStatus *pStatus) PURE;
	STDMETHOD(getErrorMessage)(BSTR *pErrorMessage) PURE;
	STDMETHOD(getPath)(BSTR *pPath) PURE;
	STDMETHOD(getValidate)(VARIANT_BOOL *pValue) PURE;
	STDMETHOD(setValidate)(VARIANT_BOOL value) PURE;
	STDMETHOD(getErrorReport)(IErrorReport **ppIErrorReport) PURE;
	STDMETHOD(getDocumentType)(Separatista::SeparatistaDocument::DocumentType *pDocumentType) PURE;
	STDMETHOD(getDirectDebitDocument)(CDirectDebitDocument **ppDirectDebitDocument) PURE;
};

struct __declspec(uuid("{6A9512FC-19BF-4F95-83D9-A8A36B1DF018}")) IDocumentReader;

/**
COM representation of an DocumentReader class.
Memory management takes 2 strategies. The CMT940SDocument will persist until all references are released.
Other classes like CMT940SRecordset will come and go on-the-fly and hold only references to the child
objects in the parent CMT940SDocument.
*/
class DocumentReader : public SepaControlDispatch<IDocumentReader>
{
public:
	/**
	@see SepaControllDispatch
	*/
	DocumentReader(IUnknown *pParent = NULL);

	virtual ~DocumentReader();

	STDMETHOD(ReadDocument)(BSTR path, Separatista::SeparatistaFileReader::DocumentStatus *pStatus);
	STDMETHOD(getStatus)(Separatista::SeparatistaFileReader::DocumentStatus *pStatus);
	STDMETHOD(getErrorMessage)(BSTR *pErrorMessage);
	STDMETHOD(getPath)(BSTR *pPath);
	STDMETHOD(getValidate)(VARIANT_BOOL *pValue);
	STDMETHOD(setValidate)(VARIANT_BOOL value);
	STDMETHOD(getErrorReport)(IErrorReport **ppIErrorReport);
	STDMETHOD(getDocumentType)(Separatista::SeparatistaDocument::DocumentType *pDocumentType);
	STDMETHOD(getDirectDebitDocument)(CDirectDebitDocument **ppDirectDebitDocument);
private:
	Separatista::SeparatistaFileReader *m_pDocumentReader;
};

class __declspec(uuid("{3FF1D4F5-2C70-4A78-ADCB-88C218E23C91}")) DocumentReader;



#endif // SEPARATISTA_DOCUMENTREADER_H