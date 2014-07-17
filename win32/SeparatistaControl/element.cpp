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

#include <windows.h>
#include <olectl.h>

#include <xercesc/util/XMLDateTime.hpp>
#include <xercesc/framework/psvi/XSValue.hpp>

#include "element.h"

Element::Element(xercesc::DOMDocument *pDocument, const wchar_t *pName)
{
	xercesc::DOMElement *pRootElement = pDocument->getDocumentElement();

	try
	{
		m_pElement = pDocument->createElement(pName);
		if (m_pElement)
			pRootElement->appendChild(m_pElement);
	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		m_pElement = NULL;
	}

}

Element::Element(xercesc::DOMDocument *pDocument, Element *pParent, const wchar_t *pName)
{
	try
	{
		m_pElement = pDocument->createElement(pName);
		if (m_pElement && pParent->m_pElement)
			pParent->m_pElement->appendChild(m_pElement);
		else
			m_pElement = NULL;
	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		m_pElement = NULL;
	}
}

Element::~Element()
{
}

const XMLCh* Element::GetTextValue() const
{
	try
	{
		return m_pElement->getTextContent();
	}
	catch (const xercesc::DOMException &e)
	{
		OutputDebugString(e.getMessage());
		return NULL;
	}
}

void Element::SetTextValue(const XMLCh *pValue)
{
	try
	{
		m_pElement->setTextContent(pValue);
	}
	catch (const xercesc::XMLException &e)
	{
		OutputDebugString(e.getMessage());
	}
}

time_t Element::GetDateValue() const
{
	xercesc::XSValue::Status status;
	xercesc::XSValue *pValue;
	std::tm tm;

	const XMLCh *pText = GetTextValue();

	if (!pText)
		return -1;

	pValue = xercesc::XSValue::getActualValue(pText, xercesc::XSValue::DataType::dt_dateTime, status);
	if (!pValue || status != xercesc::XSValue::st_Init)
		return -1;

	tm.tm_year = pValue->fData.fValue.f_datetime.f_year - 1900;
	tm.tm_mon = pValue->fData.fValue.f_datetime.f_month - 1;
	tm.tm_mday = pValue->fData.fValue.f_datetime.f_day;
	tm.tm_hour = pValue->fData.fValue.f_datetime.f_hour;
	tm.tm_min = pValue->fData.fValue.f_datetime.f_min;
	tm.tm_sec = pValue->fData.fValue.f_datetime.f_milisec / 1000;

	return std::mktime(&tm);
}

void Element::SetDateValue(time_t Value)
{
	tm *ptm;
	char buffer[64];

	ptm = std::localtime(&Value);
	strftime(buffer, 64, "%Y-%m-%dT%H:%M:%S", ptm);

	XMLCh *xmlch = xercesc::XMLString::transcode(buffer);
	if (xmlch)
	{
		SetTextValue(xmlch);
		xercesc::XMLString::release(&xmlch);
	}

}

InitgPty::InitgPty(xercesc::DOMDocument *pDocument, Element *pParent) :
Element(pDocument, pParent, TEXT("InitgPty")),
m_Nm(pDocument, this, TEXT("Nm"))
{

}

GrpHdr::GrpHdr(xercesc::DOMDocument *pDocument, Element *pParent) : 
Element(pDocument, pParent, TEXT("GrpHdr")),
m_MsgId(pDocument, this, TEXT("MsgId")),
m_CreDtTm(pDocument, this, TEXT("CreDtTm")),
m_NbOfTxs(pDocument, this, TEXT("NbOfTxs")),
m_CtrlSum(pDocument, this, TEXT("CtrlSum"))
{

}

CstmrDrctDbtInitn::CstmrDrctDbtInitn(xercesc::DOMDocument *pDocument) :
Element(pDocument, TEXT("CstmrDrctDbtInitn")),
m_GrpHdr(pDocument, this)
{

}
