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

template<class T>
AutoMagic* autoMagicCreatorFunc(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath)
{
	DEBUG_METHOD;

	return new T(pDocument, pBasePath, pWatchPath, pValuePath);
}

void AutoMagic::installAutoMagic(SeparatistaDocument *pDocument)
{
	DEBUG_METHOD;

	typedef struct
	{
		AutoMagic* (*pfnCreateAutoMagic)(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);
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
						autoMagicCreatorFunc<CountAutoMagic>, TEXT("CstmrDrctDbtInitn/PmtInf"), TEXT("DrctDbtTxInf"), TEXT("NbOfTxs")
					},
					{
						autoMagicCreatorFunc<SumAutoMagic>, TEXT("CstmrDrctDbtInitn"), TEXT("PmtInf/NbOfTxs"), TEXT("GrpHdr/NbOfTxs")
					}
				}
		}
	};

	const std::list<AutoMagicInfo> infoList = autoMagicMap[pDocument->getNamespaceURI()];
	for (auto info = infoList.cbegin(); info != infoList.cend(); info++)
	{
		info->pfnCreateAutoMagic(pDocument, info->pBasePath, info->pWatchPath, info->pValuePath);
	}
}


PathWatcher::PathWatcher(ElementListener *pAutoMagic, Element *pElement, const wchar_t *pPath)
{
	DEBUG_METHOD;

	m_pAutoMagic = pAutoMagic;
	m_pPath = pPath;
	pElement->addElementListener(this);
}

void PathWatcher::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

	// Forward if m_pPath is empty string
	if (*m_pPath == TEXT('\0') && m_pAutoMagic)
		m_pAutoMagic->elementValueChanged(pElement, pNewValue);
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
				new PathWatcher(m_pAutoMagic, pChild, ++pPath);
			}
			else if (*pPath == TEXT('\0'))
			{
				// End of path, call Magic
				m_pAutoMagic->elementCreated(pParent, pChild);
			}
		}
	}
}

void PathWatcher::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	// Forward if m_pPath is empty string
	if (*m_pPath == TEXT('\0') && m_pAutoMagic)
		m_pAutoMagic->elementDeleted(pElement);

	// Kill this element listener
	delete this;
}

AutoMagic::AutoMagic(SeparatistaDocument * pDocument, const wchar_t * pBasePath, const wchar_t * pWatchPath, const wchar_t * pValuePath)
{
	DEBUG_METHOD;

	m_pBaseElement = NULL;
	new PathWatcher(this, pDocument, pBasePath);
	m_pWatchPath = pWatchPath;
	m_pValuePath = pValuePath;
}

Element* AutoMagic::createValueElement()
{
	DEBUG_METHOD;

	const wchar_t *pPath = m_pValuePath;
	wchar_t c;
	std::wstring p;
	Element *pElement;

	// Check for base path element, should be there!
	if (!m_pBaseElement)
		return NULL;

	// Create path
	pElement = m_pBaseElement;
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

void AutoMagic::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;

	// If m_pBaseElement is empty, store it and create new PatchWatcher for m_pWatchPath
	if (!m_pBaseElement)
	{
		m_pBaseElement = pChild;
		new PathWatcher(this, pChild, m_pWatchPath);
	}
}

void AutoMagic::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;

}

void AutoMagic::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	// If the destroyed element is BaseElement, set it to NULL
	if (m_pBaseElement == pElement)
		m_pBaseElement = NULL;

	// If the destroyed element is "Document" delete this
	else if (std::wcscmp(pElement->getTag(), TEXT("Document")) == 0)
		delete this;
}

CountAutoMagic::CountAutoMagic(SeparatistaDocument * pDocument, const wchar_t * pBasePath, const wchar_t * pWatchPath, const wchar_t * pValuePath)
	:AutoMagic(pDocument, pBasePath, pWatchPath, pValuePath)
{
	DEBUG_METHOD;

	m_nCount = 0;
}

void CountAutoMagic::elementCreated(Element *pParent, Element *pChild)
{
	DEBUG_METHOD;

	AutoMagic::elementCreated(pParent, pChild);

	m_nCount++;
	createValueElement()->setValue((int)m_nCount);
}

void CountAutoMagic::elementDeleted(Element *pElement)
{
	DEBUG_METHOD;

	AutoMagic::elementDeleted(pElement);
	m_nCount--;
	createValueElement()->setValue((int)m_nCount);
}

SumAutoMagic::SumAutoMagic(SeparatistaDocument * pDocument, const wchar_t * pBasePath, const wchar_t * pWatchPath, const wchar_t * pValuePath)
	:AutoMagic(pDocument, pBasePath, pWatchPath, pValuePath)
{
	DEBUG_METHOD;

}

void SumAutoMagic::elementValueChanged(Element *pElement, const wchar_t *pNewValue)
{
	DEBUG_METHOD;
	
	AutoMagic::elementValueChanged(pElement, pNewValue);

	// TODO: make sum
	m_sum = pNewValue;
	createValueElement()->setValue(m_sum.c_str());
}
