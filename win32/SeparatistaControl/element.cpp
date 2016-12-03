/***************************************************************************
*   Copyright (C) 2016 by Okkel Klaver   *
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

#include "dispatch.cpp"
#include "util.h"
#include "element.h"
#include "separatista/element.h"
#include "enumvariant.h"
#include "supporterrorinfo.h"

Element::Element(Separatista::Element *pElement)
{
	m_pElement = pElement;
	pElement->addElementListener(this);
}

Element::~Element()
{
	if(m_pElement)
		m_pElement->removeElementListener(this);
}

Separatista::Element* Element::getElement() const
{
	return m_pElement;
}

void Element::setElement(Separatista::Element *pElement)
{
	m_pElement = pElement;
}

void Element::elementCreated(Separatista::Element *pParent, Separatista::Element *pChildElement)
{

}

void Element::elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue)
{

}

void Element::elementDeleted(Separatista::Element *pElement)
{
	// Check if the deleted element is mine and release it if it is
	if (pElement == m_pElement)
		m_pElement = NULL;
}

STDMETHODIMP Element::QueryInterface(REFIID riid, void** ppvObject)
{
	SepaControlSupportErrorInfo *pSupportErrorInfo;

	if (IsEqualIID(riid, IID_ISupportErrorInfo))
	{
		pSupportErrorInfo = new SepaControlSupportErrorInfo();
		if (!pSupportErrorInfo)
			return E_OUTOFMEMORY;
		pSupportErrorInfo->AddRef();
		*ppvObject = pSupportErrorInfo;
		return S_OK;
	}
	return SepaControlDispatch<IElement>::QueryInterface(riid, ppvObject);
}

STDMETHODIMP Element::GetTagName(BSTR *pTagName)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		*pTagName = _bstr_t(m_pElement->getTag()).Detach();
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::GetValue(BSTR *pValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		*pValue = _bstr_t(m_pElement->getTextValue()).Detach();
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::SetValue(BSTR Value)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->setValue(Value);
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	catch (const Separatista::InvalidValueException & iv)
	{
		return SetErrorInfo(iv);
	}
	return S_OK;
}

STDMETHODIMP Element::GetCurrencyValue(VARIANT *pValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		*pValue = _variant_t(m_pElement->getDoubleValue()).Detach();
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::SetCurrencyValue(VARIANT Value)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->setValue((double)_variant_t(Value));
	}
	catch (const Separatista::InvalidValueException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::GetDateValue(DATE *pDateValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		return DateTypeFromStdTime(m_pElement->getDateValue(), pDateValue);
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::SetDateValue(DATE DateValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->setValue(StdTimeFromDateType(DateValue));
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	catch (const Separatista::InvalidValueException &iv)
	{
		return SetErrorInfo(iv);
	}
	return S_OK;
}

STDMETHODIMP Element::SetDateTimeValue(DATE DateTimeValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->setValue(StdTimeFromDateType(DateTimeValue), true);
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	catch (const Separatista::InvalidValueException &iv)
	{
		return SetErrorInfo(iv);
	}
	return S_OK;
}

STDMETHODIMP Element::GetElementByTagName(BSTR TagName, UINT index, IElement **ppElement)
{
	*ppElement = NULL;

	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		Separatista::Element *pElement = m_pElement->getElementByTag(TagName, index);
		if (!pElement)
			return S_OK;
		*ppElement = new Element(pElement);
		(*ppElement)->AddRef();
		return S_OK;
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::CreateElementByTagName(BSTR TagName, UINT index, IElement **ppElement)
{
	*ppElement = NULL;

	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		Separatista::Element *pElement = m_pElement->createElementByTag(TagName, index);
		if (!pElement)
			return S_OK;
		*ppElement = new Element(pElement);
		(*ppElement)->AddRef();
		return S_OK;
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::DestroyElement(IElement *pElement)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->destroyElement(((Element*)pElement)->m_pElement);
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::GetAttributeValue(BSTR AttributeName, BSTR *pValue)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		*pValue = _bstr_t(m_pElement->getAttributeValue(AttributeName)).Detach();
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	return S_OK;
}

STDMETHODIMP Element::SetAttributeValue(BSTR AttributeName, BSTR Value)
{
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	try
	{
		m_pElement->setAttributeValue(AttributeName, Value);
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}
	catch (const Separatista::InvalidValueException &iv)
	{
		return SetErrorInfo(iv);
	}
	return S_OK;
}

STDMETHODIMP Element::GetAllByTagName(BSTR TagName, IEnumVARIANT **ppEnumVariant)
{
	EnumVariant *pEnumVariant;
	
	if (!m_pElement)
		return E_NOT_VALID_STATE;

	pEnumVariant = new EnumVariant();
	if (!pEnumVariant)
	{
		*ppEnumVariant = NULL;
		return E_OUTOFMEMORY;
	}
	pEnumVariant->AddRef();

	try
	{
		Separatista::Element::TagKeyRange range = m_pElement->getAllByTagName(TagName);
		for (auto p = range.m_begin; p != range.m_end; p++)
		{
			pEnumVariant->Add(_variant_t(new Element(p->second)).Detach());
		}
	}
	catch (const Separatista::ElementException &e)
	{
		return SetErrorInfo(e);
	}

	*ppEnumVariant = pEnumVariant;
	return S_OK;
}