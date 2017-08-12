/***************************************************************************
*   Copyright (C) 2017 by Okkel Klaver   *
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

#include <cwchar>
#include <string>
#include <unordered_map>
#include <initializer_list>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/automagic.h"
#include "separatista/separatistadocument.h"
#include "separatista/debug/debug.h"
#include "separatista/pain/pain.008.001.02.h"

using namespace Separatista;

void AutoMagic::installAutoMagic(SeparatistaDocument *pDocument)
{
	DEBUG_METHOD;

	typedef struct
	{
		void (*pfnCreateAutoMagicFactory)(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);
		const wchar_t *pBasePath;
		const wchar_t *pWatchPath;
		const wchar_t *pValuePath;
	} AutoMagicInfo;

	// Insert new automagic here
	std::unordered_map<std::wstring, const std::initializer_list<AutoMagicInfo>> autoMagicMap =
	{
		{
			Separatista::pain_008_001_02::Namespace, 
				{
					{
						AutoMagicFactory<CountAutoMagic>::Create, TEXT("CstmrDrctDbtInitn/PmtInf"), TEXT("DrctDbtTxInf"), TEXT("NbOfTxs")
					},
					{
						AutoMagicFactory<SumAutoMagic>::Create, TEXT("CstmrDrctDbtInitn/PmtInf"), TEXT("DrctDbtTxInf/InstdAmt"), TEXT("CtrlSum")
					},
					{
						AutoMagicFactory<SumAutoMagic>::Create, TEXT("CstmrDrctDbtInitn"), TEXT("PmtInf/NbOfTxs"), TEXT("GrpHdr/NbOfTxs")
					},
					{
						AutoMagicFactory<SumAutoMagic>::Create, TEXT("CstmrDrctDbtInitn"), TEXT("PmtInf/CtrlSum"), TEXT("GrpHdr/CtrlSum")
					}
				}
		}
	};

	const std::list<AutoMagicInfo> infoList = autoMagicMap[pDocument->getNamespaceURI()];
	for (auto info = infoList.cbegin(); info != infoList.cend(); info++)
	{
		info->pfnCreateAutoMagicFactory(pDocument, info->pBasePath, info->pWatchPath, info->pValuePath);
	}
}


PathWatcher::PathWatcher(ElementListener *pFinalListener, Element *pElement, const wchar_t *pPath)
{
	DEBUG_METHOD;

	m_pFinalListener = pFinalListener;
	m_pPath = pPath;
	pElement->addElementListener(this);
}

void PathWatcher::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

	// Forward if m_pPath matches element tag
	if (std::wcscmp(pElement->getTag(), m_pPath) == 0 && m_pFinalListener)
		m_pFinalListener->elementValueChanged(pElement, pNewValue);
}

void PathWatcher::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;

	// Match pChild tag with m_pPath and install next PathWatcher if it does
	const wchar_t *pPath = m_pPath;
	const wchar_t *pTag = pChild->getTag();
	wchar_t c;

	while ((c = *pPath++) != TEXT('\0'))
	{
		if (*pTag++ != c)
			return;
		// Check for next char
		if (*pTag == TEXT('\0'))
		{
			// End of tag, check path
			if (*pPath == TEXT('/'))
			{
				// Not the end of path, install new PathWatcher to Child element
				new PathWatcher(m_pFinalListener, pChild, ++pPath);
			}
			else if (*pPath == TEXT('\0'))
			{
				// End of path, call Magic
				m_pFinalListener->elementCreated(pParent, pChild);
			}
			return;
		}
	}
}

void PathWatcher::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	// Forward if m_pPath and Element tag match
	if (std::wcscmp(pElement->getTag(), m_pPath) == 0 && m_pFinalListener)
		m_pFinalListener->elementDeleted(pElement);

	// Kill this element listener
	delete this;
}

AutoMagic::AutoMagic(Element *pBaseElement, const wchar_t * pWatchPath, const wchar_t * pValuePath)
{
	DEBUG_METHOD;

	// Store base element
	m_pBaseElement = pBaseElement;

	// Create value element
	m_pValueElement = createValueElement(pBaseElement, pValuePath);
	if (m_pValueElement)
	{
		// Keep an eye on the value element
		m_pValueElement->addElementListener(this);

		// Install PathWatchers
		new PathWatcher(this, pBaseElement, pWatchPath);
	}
}

Element* AutoMagic::createValueElement(Element *pBaseElement, const wchar_t *pValuePath)
{
	DEBUG_METHOD;

	const wchar_t *pPath = pValuePath;
	wchar_t c;
	std::wstring p;
	Element *pElement;

	// Create path
	pElement = pBaseElement;
	while ((c = *pPath++) != TEXT('\0'))
	{
		p += c;
		switch (*pPath)
		{
		case TEXT('/'):
			pPath++;
		case TEXT('\0'):
			// p contains the Tagname
			try
			{
				pElement = pElement->createElementByTag(p.c_str());
			}
			catch (const Separatista::ElementException& e)
			{
				// Internal error!
				LOG(e.getMessage());
				throw(e);
			}
			// Restart with empty string
			p.clear();
		}
	}
	return pElement;
}

Element* AutoMagic::getValueElement()
{
	DEBUG_METHOD;

	return m_pValueElement;
}

void AutoMagic::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;

}

void AutoMagic::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

}

void AutoMagic::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	if (pElement == m_pValueElement)
		m_pValueElement = NULL;
	else if (pElement == m_pBaseElement)
		delete this;
}

CountAutoMagic::CountAutoMagic(Element *pBaseElement, const wchar_t *pWatchPath, const wchar_t *pValuePath)
	:AutoMagic(pBaseElement, pWatchPath, pValuePath)
{
	DEBUG_METHOD;

	m_nCount = 0;
}

void CountAutoMagic::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;
	Element *pValueElement;

	m_nCount++;
	pValueElement = getValueElement();
	if(pValueElement)
		pValueElement->setValue((int)m_nCount);

	AutoMagic::elementCreated(pParent, pChild);
}

void CountAutoMagic::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;
	Element *pValueElement;

	pValueElement = getValueElement();
	if (pElement != pValueElement)
	{
		m_nCount--;

		if (pValueElement)
			pValueElement->setValue((int)m_nCount);
	}
	AutoMagic::elementDeleted(pElement);
}

void CountAutoMagic::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

	AutoMagic::elementValueChanged(pElement, pNewValue);
}

SumAutoMagic::SumAutoMagic(Element *pBaseElement, const wchar_t * pWatchPath, const wchar_t * pValuePath)
	:AutoMagic(pBaseElement, pWatchPath, pValuePath)
{
	DEBUG_METHOD;

	sum();
}

void SumAutoMagic::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

	// Check for loops
	if(pElement != getValueElement())
		sum();
	AutoMagic::elementValueChanged(pElement, pNewValue);
}

void SumAutoMagic::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;
	
	pChild->addElementListener(this);
	m_elements.push_back(pChild);
	AutoMagic::elementCreated(pParent, pChild);
}

void SumAutoMagic::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	Element *pValueElement = getValueElement();
	if (pElement != pValueElement)
	{
		m_elements.remove(pElement);
		sum();
	}
	AutoMagic::elementDeleted(pElement);
}

const wchar_t *_num = TEXT("0123456789");

unsigned int SumAutoMagic::atoi(const wchar_t c)
{
	DEBUG_METHOD;

	for (unsigned int i = 0; i < 10; i++)
	{
		if (_num[i] == c)
			return i;
	}

	return 0;
}

wchar_t SumAutoMagic::itoa(unsigned int i)
{
	DEBUG_METHOD;

	return _num[i];
}

size_t SumAutoMagic::findCh(const wchar_t *pValue, const wchar_t ch)
{
	DEBUG_METHOD;

	size_t i = 0;
	while (pValue[i] != ch)
	{
		if (pValue[++i] == TEXT('\0'))
			break;
	}
	return i;
}

void SumAutoMagic::sum()
{
	DEBUG_METHOD;
	Element *pValueElement = getValueElement();
	if (!pValueElement)
		return;

	std::wstring sum(TEXT("0"));
	const wchar_t *pValue1 = sum.c_str();
	const wchar_t *pValue2;
	unsigned int v = 0;

	for (auto it = m_elements.begin(); it != m_elements.end(); it++)
	{
		std::wstring nsum;

		pValue2 = (*it)->getTextValue();

		size_t len1 = std::wcslen(pValue1);
		size_t len2 = std::wcslen(pValue2);

		// Make value1 always the longest in size
/*		if (len2 > len1)
		{
			size_t tlen = len2;
			len2 = len1;
			len1 = tlen;

			const wchar_t *pTemp = pValue2;
			pValue2 = pValue1;
			pValue1 = pTemp;
		}
*/
		// Get dot positions and calc decimal count including dot
		size_t dc1 = len1 - findCh(pValue1, TEXT('.'));
		size_t dc2 = len2 - findCh(pValue2, TEXT('.'));

		while (len1 > 0 || len2 > 0)
		{
			bool dot = false;
			unsigned int v1 = 0;
			unsigned int v2 = 0;

			// Get value for v1
			// Are we in decimals?
			if (dc1 > 0 || dc2 > 0)
			{
				if (dc1 > dc2)
				{
					if (len1 > 0)
						v1 = atoi(pValue1[--len1]);
					dc1--;
				}
				else if (dc2 > dc1)
				{
					if (len2 > 0)
						v2 = atoi(pValue2[--len2]);
					dc2--;
				}
				else if (dc1 == dc2)
				{
					if (len1 > 0)
						v1 = atoi(pValue1[--len1]);
					if (len2 > 0)
						v2 = atoi(pValue2[--len2]);
					dc1--;
					dc2--;
				}
				// Test for dot copy
				if (dc1 == 0 && dc2 == 0)
					dot = true;
			}
			else
			{
				if (len1 > 0)
					v1 = atoi(pValue1[--len1]);
				if (len2 > 0)
					v2 = atoi(pValue2[--len2]);
			}

			// v1 and v2 should hold values now
			v += v1 + v2;
			unsigned int d = v % 10;
			v -= d;
			nsum += itoa(d);

			if (dot)
			{
				nsum += TEXT('.');
				dot = false;

				if (len1 > 0)
					--len1;
				if (len2 > 0)
					--len2;
			}
			
			// nsum is the reverse of sum
			sum = nsum;
			std::reverse(sum.begin(), sum.end());
		}
	}
	// Set values
	pValueElement->setValue(sum.c_str());
}

template <class T>
AutoMagicFactory<T>::AutoMagicFactory(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath)
{
	DEBUG_METHOD;

	m_pDocument = pDocument;
	m_pWatchPath = pWatchPath;
	m_pValuePath = pValuePath;

	// Create PathWatcher
	new PathWatcher(this, pDocument, pBasePath);

	// Set elementlistener for document for destruction
	pDocument->addElementListener(this);
}

template <class T>
void AutoMagicFactory<T>::elementValueChanged(Element* pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

}

template <class T>
void AutoMagicFactory<T>::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;

	if(pParent != m_pDocument)
		new T(pChild, m_pWatchPath, m_pValuePath);
}

template <class T>
void AutoMagicFactory<T>::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	// Destroy self if pElement is pDocument
	if (pElement == m_pDocument)
		delete this;
}
