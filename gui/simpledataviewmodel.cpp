/***************************************************************************
*   Copyright (C) 2018 by Okkel Klaver                                    *
*   info@vanhetland.nl                                                    *
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

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <separatista/debug/debug.h>

#include "simpledataviewmodel.h"

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, Separatista::SeparatistaDocument *pSepaDocument)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaDocument)
{
	m_pParent = NULL;
	m_pAttribute = NULL;
	m_pSepaParentElement = NULL;

	buildModelTree(pElement, pSepaDocument);
}

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, const SimpleViewData::Element *pAttributeElement, Separatista::Element *pSepaElement, Separatista::Element *pSepaParentElement, SimpleDataViewModelNode *pParent)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaElement), m_pSepaParentElement(pSepaParentElement), m_pParent(pParent), m_pAttribute(pAttributeElement)
{
	// Receive notifications for element deletion and updates
	if(m_pSepaElement)
		m_pSepaElement->addElementListener(this);
}

SimpleDataViewModelNode::~SimpleDataViewModelNode()
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
		delete *it;
}

const SimpleViewData::Element* SimpleDataViewModelNode::getSimpleViewDataElement() const
{
	return m_pElement;
}

const SimpleViewData::Element* SimpleDataViewModelNode::getSimpleViewDataAttributeElement() const
{
	return m_pAttribute;
}

Separatista::Element* SimpleDataViewModelNode::getSepaElement() const
{
	return m_pSepaElement;
}

SimpleDataViewModelNode * SimpleDataViewModelNode::getParent() const
{
	return m_pParent;
}

void SimpleDataViewModelNode::setParent(SimpleDataViewModelNode * pParent)
{
	m_pParent = pParent;
}

size_t SimpleDataViewModelNode::getChildCount() const
{
	return m_children.size();
}

SimpleDataViewModelNode * SimpleDataViewModelNode::getChild(size_t index) const
{
	try
	{
		return m_children.at(index);
	}
	catch (std::out_of_range)
	{
		return NULL;
	}
}

void SimpleDataViewModelNode::appendChild(SimpleDataViewModelNode * pChild)
{
	m_children.push_back(pChild);
}

void SimpleDataViewModelNode::removeChild(SimpleDataViewModelNode * pChild)
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
	{
		if (*it == pChild)
		{
			m_children.erase(it);
			return;
		}
	}
}

void SimpleDataViewModelNode::elementCreated(Separatista::Element * pParent, Separatista::Element * pElement)
{
}

void SimpleDataViewModelNode::elementDeleted(Separatista::Element * pElement)
{
	if (pElement == getSepaElement())
	{
		// Check for root element type
		const SimpleViewData::Element *pTypeElement = getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::Type);
		if (pTypeElement && pTypeElement->getValue() == wxT("Root"))
		{
			m_pParent->removeChild(this);
			m_pDataViewModel->ItemDeleted(wxDataViewItem(m_pParent), wxDataViewItem(this));

			// Remove listeners from Sepa Document
			if (m_pSepaElement)
				m_pSepaElement->removeElementListener(this);

			delete this;
		}
		else
		{
			m_pSepaElement = NULL;
			m_pDataViewModel->ValueChanged(wxDataViewItem(this), 1);
		}
	}
}

void SimpleDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	if (pElement == m_pSepaElement)
	{
		m_pDataViewModel->ValueChanged(wxDataViewItem(this), 1);
	}
}

const wxString SimpleDataViewModelNode::getElementValue() const
{
	if (m_pSepaElement)
		return m_pSepaElement->getTextValue();
	else
		return wxEmptyString;
}

void SimpleDataViewModelNode::setElementValue(const wxString & value)
{
	// Check for sepa element
	if (!m_pSepaElement)
	{
		m_pSepaElement = createDocumentPath();
		if (!m_pSepaElement)
			return;
	}

	// Check for attribute
	if (getSimpleViewDataAttributeElement())
	{
		m_pSepaElement->setAttributeValue(getSimpleViewDataAttributeElement()->getValue(), value);
	}
	else
	{
		m_pSepaElement->setValue(value);
	}
}

void SimpleDataViewModelNode::setElementValue(const wxDateTime & dt, bool bWithTime)
{
	// Check for sepa element
	if (!m_pSepaElement)
	{
		createDocumentPath();
		if (!m_pSepaElement)
			return;
	}

	// Check for attribute
	if (getSimpleViewDataAttributeElement())
	{
		if (bWithTime)
			m_pSepaElement->setAttributeValue(getSimpleViewDataAttributeElement()->getValue(), dt.FormatISOCombined());
		else
			m_pSepaElement->setAttributeValue(getSimpleViewDataAttributeElement()->getValue(), dt.FormatISODate());
	}
	else
	{
		m_pSepaElement->setValue(dt.GetTicks(), bWithTime);
	}

}

Separatista::Element * SimpleDataViewModelNode::createDocumentPath(size_t index)
{
	const SimpleViewData::Element *pDocPathElement;
	
	if (m_pSepaElement)
		return m_pSepaElement;
	// No Sepa Element present, check for DocumentPath element
	if ((pDocPathElement = m_pElement->getChildByType(SimpleViewData::Element::DocumentPath)) == NULL)
	{
		// No Documentpath element present, try parent
		return m_pParent->createDocumentPath();
	}
	else
	{
		// Create Parent DocumentPath
		m_pSepaParentElement = m_pParent->createDocumentPath();
		// Create this DocumentPath
		for (; pDocPathElement != NULL; pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath),
											m_pSepaParentElement = m_pSepaElement)
		{
			m_pSepaElement = m_pSepaParentElement->createElementByTag(pDocPathElement->getValue(), index);
		}
	}

	// Set listener
	m_pSepaElement->addElementListener(this);
	return m_pSepaElement;
}


void SimpleDataViewModelNode::buildModelTree(const SimpleViewData::Element *pSimpleElement, Separatista::Element *pSepaElement)
{
	const SimpleViewData::Element *pSimpleChildElement, *pTypeChildElement, *pDocPathElement, *pAttrElement;
	SimpleDataViewModelNode *pNewNode;
	Separatista::Element *pSepaChildElement, *pSepaParentElement = NULL;

	// Enum all children
	for (size_t i = 0; i < pSimpleElement->getChildCount(); i++)
	{
		pSimpleChildElement = pSimpleElement->getChild(i);
		switch (pSimpleChildElement->getType())
		{
		case SimpleViewData::Element::SimplePath:
			// Associate documentpath with this element
			pTypeChildElement = pSimpleChildElement->getChildByType(SimpleViewData::Element::Type);
			if (pTypeChildElement)
			{
				pSepaChildElement = pSepaElement;
				pDocPathElement = pSimpleChildElement;
				pAttrElement = NULL;
				// Get sepa children by document path
				while ((pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL)
				{
					pAttrElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPathAttribute);
					pSepaParentElement = pSepaChildElement;
					pSepaChildElement = pSepaParentElement->getElementByTag(pDocPathElement->getValue());
					if (!pSepaChildElement)
						break;
				}

				// Get all sepa parent child nodes by tag
				if (pSepaChildElement && pSepaParentElement)
				{
					Separatista::Element::TagKeyRange range = pSepaParentElement->getAllByTagName(pSepaChildElement->getTag());
					for (auto it = range.m_begin; it != range.m_end; it++)
					{
						pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, pAttrElement, it->second, pSepaParentElement, this);
						// Recurse if type == Root
						if(pTypeChildElement->getValue() == wxT("Root") || pTypeChildElement->getValue() == wxT("Documentroot"))
							pNewNode->buildModelTree(pSimpleChildElement, it->second);
						appendChild(pNewNode);
					}
				}
			}
			else
			{
				pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, NULL, NULL, NULL, this);
				// Recurse 
				pNewNode->buildModelTree(pSimpleChildElement, pSepaElement);
				appendChild(pNewNode);
			}
		}
	}
}

SimpleDataViewModel::SimpleDataViewModel(DocumentEditor *pDocumentEditor)
	:m_rootNode(this, (pDocumentEditor->getSimpleViewData() ? pDocumentEditor->getSimpleViewData()->getRootElement() : NULL), pDocumentEditor->getDocument())
{
	m_pDocumentEditor = pDocumentEditor;
	m_bLocked = false;
}

bool SimpleDataViewModel::IsContainer(const wxDataViewItem &item) const
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)item.GetID();

	// Check for root
	if (!pNode)
		return true;

	const SimpleViewData::Element *pElement = pNode->getSimpleViewDataElement();
	switch (pElement->getType())
	{
	case SimpleViewData::Element::Root:
		return true;
	case SimpleViewData::Element::SimplePath:
		if (pElement->getChildByType(SimpleViewData::Element::SimplePath) != NULL)
		{
			return true;
		}
	default:
		return false;
	}
}

wxDataViewItem SimpleDataViewModel::GetParent(const wxDataViewItem & item) const
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)item.GetID();

	pNode = pNode->getParent();
	// Check for Root element
	if (pNode == NULL || pNode->getParent() == NULL)
		return wxDataViewItem(NULL);
	return wxDataViewItem(pNode);
}

unsigned int SimpleDataViewModel::GetChildren(const wxDataViewItem & item, wxDataViewItemArray & children) const
{
	const SimpleDataViewModelNode *pNode = (const SimpleDataViewModelNode*)item.GetID();

	if (!pNode)
		pNode = &m_rootNode;
	
	for (size_t i = 0; i < pNode->getChildCount(); i++)
	{
		children.push_back(wxDataViewItem(pNode->getChild(i)));
	}

	return pNode->getChildCount();
}

unsigned int SimpleDataViewModel::GetColumnCount() const
{
	return 2;
}

wxString SimpleDataViewModel::GetColumnType(unsigned int col) const
{
	switch (col)
	{
	case 1:
		return wxT("void*");
	default:
		return wxT("string");
	}
}

void SimpleDataViewModel::GetValue(wxVariant & variant, const wxDataViewItem & item, unsigned int col) const
{
	const SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)item.GetID();

	switch (col)
	{
	case 0:
		variant = pNode->getSimpleViewDataElement()->getValue();
		break;
	case 1:
		variant = (void*)pNode;
	}
}

bool SimpleDataViewModel::SetValue(const wxVariant & variant, const wxDataViewItem & item, unsigned int col)
{
	m_pDocumentEditor->changed();
	return false;
}

void SimpleDataViewModel::OnContextMenu(wxWindow *pWindow, wxDataViewEvent & evt)
{
}


