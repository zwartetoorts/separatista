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

#include "mainframe.h"
#include "expertdataviewmodel.h"

ElementDataViewModelNode::ElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pSepaElement, ElementDataViewModelNode *pParent)
	:m_pDataViewModel(pDataViewModel),
	m_pSepaElement(pSepaElement),
	m_pParent(pParent)
{
}

ElementDataViewModelNode::~ElementDataViewModelNode()
{
}

ExpertDataViewModel * ElementDataViewModelNode::getModel() const
{
	return m_pDataViewModel;
}

Separatista::Element* ElementDataViewModelNode::getSepaElement() const
{
	return m_pSepaElement;
}

ElementDataViewModelNode* ElementDataViewModelNode::getParent() const
{
	return m_pParent;
}

size_t ElementDataViewModelNode::getChildren(wxDataViewItemArray & children) const
{
	return 0;
}

void ElementDataViewModelNode::removeChild(ElementDataViewModelNode * pChild)
{
}

wxString ElementDataViewModelNode::getLabel() const
{
	return getSepaElement()->getTag();
}

void ElementDataViewModelNode::setValue(const wxString & value)
{
}

void ElementDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
}

void ElementDataViewModelNode::elementCreated(Separatista::Element * pParent, Separatista::Element * pChild)
{
}

void ElementDataViewModelNode::elementDeleted(Separatista::Element * pElement)
{
	if (m_pParent)
	{
		m_pParent->removeChild(this);
		m_pDataViewModel->ItemDeleted(wxDataViewItem(m_pParent), wxDataViewItem(this));
	}
	delete this;
}

ValueElementDataViewModelNode::ValueElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, LeafElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent)
{
}

ElementDataViewModelNode::ElementType ValueElementDataViewModelNode::getElementType() const
{
	return ValueElement;
}

wxString ValueElementDataViewModelNode::getLabel() const
{
	return getSepaElement()->getTextValue();
}

void ValueElementDataViewModelNode::setValue(const wxString &value)
{
	getSepaElement()->setValue(value);
}

void ValueElementDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
}

void ValueElementDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	getModel()->ValueChanged(wxDataViewItem(this), 0);
}

AttributeValueDataViewModelNode::AttributeValueDataViewModelNode(ExpertDataViewModel * pDataViewModel, Separatista::Element * pElement, AttributeDataViewModelNode * pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent)
{
}

ElementDataViewModelNode::ElementType AttributeValueDataViewModelNode::getElementType() const
{
	return AttributeValue;
}

wxString AttributeValueDataViewModelNode::getLabel() const
{
	AttributeDataViewModelNode *pParent = (AttributeDataViewModelNode*)getParent();

	return getSepaElement()->getAttributeValue(pParent->getValue());
}

void AttributeValueDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
}

void AttributeValueDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	getModel()->ValueChanged(wxDataViewItem(this), 0);
}

void AttributeValueDataViewModelNode::setValue(const wxString & value)
{
	AttributeDataViewModelNode *pParent = (AttributeDataViewModelNode*)getParent();
	getSepaElement()->setAttributeValue(pParent->getValue(), value);
}

AttributeDataViewModelNode::AttributeDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, AttributedElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent),
	m_attributeName(attributeName)
{
	m_pValueNode = new AttributeValueDataViewModelNode(pDataViewModel, pElement, this);
}

AttributeDataViewModelNode::~AttributeDataViewModelNode()
{
	delete m_pValueNode;
}

ElementDataViewModelNode::ElementType AttributeDataViewModelNode::getElementType() const
{
	return AttributeName;
}

size_t AttributeDataViewModelNode::getChildren(wxDataViewItemArray & children) const
{
	size_t count = 1;
	children.push_back(wxDataViewItem(m_pValueNode));
	return count + m_pValueNode->getChildren(children);
}

void AttributeDataViewModelNode::removeChild(ElementDataViewModelNode * pChild)
{
}

wxString AttributeDataViewModelNode::getLabel() const
{
	return m_attributeName;
}

wxString AttributeDataViewModelNode::getValue() const
{
	return getLabel();
}

void AttributeDataViewModelNode::setValue(const wxString &value)
{
}

void AttributeDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
}

void AttributeDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	m_pValueNode->elementValueChanged(pElement, pNewValue);
}

LeafElementDataViewModelNode::LeafElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, ElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent)
{
	m_pValueNode = new ValueElementDataViewModelNode(pDataViewModel, pElement, this);

	// Set listeners on element
	if (pElement)
		pElement->addElementListener(this);
}

LeafElementDataViewModelNode::~LeafElementDataViewModelNode()
{
	delete m_pValueNode;
}

ElementDataViewModelNode::ElementType LeafElementDataViewModelNode::getElementType() const
{
	return LeafElement;
}

size_t LeafElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	children.push_back(wxDataViewItem((void*)m_pValueNode));
	return 1;
}

void LeafElementDataViewModelNode::removeChild(ElementDataViewModelNode * pChild)
{
}

void LeafElementDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
}

void LeafElementDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	m_pValueNode->elementValueChanged(pElement, pNewValue);
}

AttributedElementDataViewModelNode::AttributedElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, ElementDataViewModelNode *pParent)
	:LeafElementDataViewModelNode(pDataViewModel, pElement, pParent)
{
	m_pAttributeNode = new AttributeDataViewModelNode(pDataViewModel, pElement, attributeName, this);
}

AttributedElementDataViewModelNode::~AttributedElementDataViewModelNode()
{
	delete m_pAttributeNode;
}

ElementDataViewModelNode::ElementType AttributedElementDataViewModelNode::getElementType() const
{
	return AttributedLeafElement;
}

size_t AttributedElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	size_t count = 1;
	children.push_back(wxDataViewItem(m_pAttributeNode));
	return count + LeafElementDataViewModelNode::getChildren(children);
}

void AttributedElementDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
}

void AttributedElementDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	// Notify both super and child
	m_pAttributeNode->elementValueChanged(pElement, pNewValue);
	LeafElementDataViewModelNode::elementValueChanged(pElement, pNewValue);
}

BranchElementDataViewModelNode::BranchElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, ElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent)
{
	// Add all child elements
	const Separatista::ElementDescriptor *pElementDescriptor;
	Separatista::Element *pSepaElement = getSepaElement();

	pElementDescriptor = pElement->getElementDescriptor();
	for (size_t i = 0; i < pElementDescriptor->m_nElementCount; i++)
	{
		Separatista::Element::TagKeyRange range = pSepaElement->getAllByTagName(pElementDescriptor->m_pChildren[i].m_pTag);
		if (pElementDescriptor->m_pChildren[i].m_pElementDescriptor->m_nElementCount > 0)
		{
			// BranchElement
			for (auto it = range.m_begin; it != range.m_end; it++)
			{
				addChild(new BranchElementDataViewModelNode(
					pDataViewModel,
					it->second,
					this
				));
			}
		}
		else if (pElementDescriptor->m_pChildren[i].m_pElementDescriptor->m_pTypeParent != NULL)
		{
			// AttributedLeafElement
			// This is ugly, assuming only types with a parent type have attributes
			// But hey, in all sepa documents covered so far it works and current implementation saves memory
			for (auto it = range.m_begin; it != range.m_end; it++)
			{
				addChild(new AttributedElementDataViewModelNode(
					pDataViewModel,
					it->second,
					wxT("Ccy"),
					this
				));
			}
		}
		else
		{
			// LeafElement
			for (auto it = range.m_begin; it != range.m_end; it++)
			{
				addChild(new LeafElementDataViewModelNode(
					pDataViewModel,
					it->second,
					this
				));
			}
		}
	}

	// Set listeners on element
	if (pElement)
		pElement->addElementListener(this);
}

void BranchElementDataViewModelNode::addChild(ElementDataViewModelNode *pChild)
{
	m_children.push_back(pChild);
}

void BranchElementDataViewModelNode::OnContextMenu(wxWindow * pWindow, wxDataViewEvent & evt)
{
	wxMenu menu;
	wxMenu *pCreateMenu = new wxMenu();

	// Create a menu to remove this element, check for top level
	menu.Append(ID_COMMAND_EXPERT_REMOVE, wxT("Remove"));
	if (getParent() == NULL)
		menu.Enable(ID_COMMAND_EXPERT_REMOVE, false);
	
	// Create a menu to create all child elements, but those who already have reached their max
	Separatista::Element *pElement = getSepaElement();
	const Separatista::ElementDescriptor *pDescriptor = pElement->getElementDescriptor();
	
	size_t i;
	for (i = 0; i < pDescriptor->m_nElementCount; i++)
	{
		// Pass index through command id
		pCreateMenu->Append(ID_COMMAND_EXPERT_CREATE + i, pDescriptor->m_pChildren[i].m_pTag, wxEmptyString);

		// Check max
		Separatista::Element::TagKeyRange range;
		range = pElement->getAllByTagName(pDescriptor->m_pChildren[i].m_pTag);
		size_t count = 0;
		for (auto it = range.m_begin; it != range.m_end; it++)
		{
			++count;
		}
		if (pDescriptor->m_pChildren[i].m_nMax > 0 &&
			pDescriptor->m_pChildren[i].m_nMax <= count)
		{
			pCreateMenu->Enable(ID_COMMAND_EXPERT_CREATE + i, false);
		}
	}

	// Bind member functions to commands
	pWindow->Bind(
		wxEVT_COMMAND_MENU_SELECTED,
		[this](wxCommandEvent &evt)
	{
		OnCommandRemove(evt);
	},
		ID_COMMAND_EXPERT_REMOVE);
	pWindow->Bind(
		wxEVT_COMMAND_MENU_SELECTED,
		[this](wxCommandEvent &evt)
	{
		OnCommandCreate(evt);
	},
		ID_COMMAND_EXPERT_CREATE,
		ID_COMMAND_EXPERT_CREATE + i);
	menu.AppendSubMenu(pCreateMenu, wxT("Create"));
	pWindow->PopupMenu(&menu);
}

void BranchElementDataViewModelNode::OnCommandCreate(wxCommandEvent & evt)
{
	Separatista::Element *pNewSepaElement, *pSepaElement = getSepaElement();
	const Separatista::ElementDescriptor *pDescriptor = pSepaElement->getElementDescriptor();
	
	size_t index = evt.GetId() - ID_COMMAND_EXPERT_CREATE;
	// Find empty index
	size_t i, max = pDescriptor->m_pChildren[index].m_nMax;
	for (i = 0; max == 0 || i < max; i++)
	{
		if (pSepaElement->getElementByTag(pDescriptor->m_pChildren[index].m_pTag, i) == NULL)
			break;
	}
	pNewSepaElement = pSepaElement->createElementByTag(pDescriptor->m_pChildren[index].m_pTag, i);
}

void BranchElementDataViewModelNode::OnCommandRemove(wxCommandEvent & evt)
{
	// Remove this element
	if (!getParent())
		return;

	Separatista::Element *pParent = getParent()->getSepaElement();
	pParent->destroyElement(getSepaElement());
}

void BranchElementDataViewModelNode::elementCreated(Separatista::Element * pParent, Separatista::Element *pChild)
{
	ElementDataViewModelNode *pNewNode = NULL;
	if (pChild->getElementDescriptor()->m_nElementCount > 0)
	{
		// BranchElement
		pNewNode = new BranchElementDataViewModelNode(getModel(), pChild, this);
		addChild(pNewNode);
	}
	else if (pChild->getElementDescriptor()->m_pTypeParent != NULL)
	{
		// AttributedLeafElement
		pNewNode = new AttributedElementDataViewModelNode(getModel(), pChild, wxT("Ccy"), this);
		addChild(pNewNode);
	}
	else
	{
		// LeafElement
		pNewNode = new LeafElementDataViewModelNode(getModel(), pChild, this);
		addChild(pNewNode);
	}
	getModel()->ItemAdded(wxDataViewItem(this), wxDataViewItem(pNewNode));
}


size_t BranchElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	size_t c = 0;
	for (auto it = m_children.begin(); it != m_children.end(); it++, c++)
	{
		children.push_back(wxDataViewItem(*it));
	}
	return c;
}

void BranchElementDataViewModelNode::removeChild(ElementDataViewModelNode * pChild)
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

ElementDataViewModelNode::ElementType BranchElementDataViewModelNode::getElementType() const
{
	return BranchElement;
}

ExpertDataViewModel::ExpertDataViewModel(DocumentEditor *pDocumentEditor)
	:m_pDocumentEditor(pDocumentEditor)
{
	m_pDocumentNode = new BranchElementDataViewModelNode(this, pDocumentEditor->getDocument());
}

bool ExpertDataViewModel::IsContainer(const wxDataViewItem &item) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode)
		return true;

	switch (pNode->getElementType())
	{
	case ElementDataViewModelNode::ValueElement:
	case ElementDataViewModelNode::AttributeValue:
		return false;
	default:
		return true;
	}
}

wxDataViewItem ExpertDataViewModel::GetParent(const wxDataViewItem &item) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode || pNode == m_pDocumentNode)
		return wxDataViewItem(NULL);

	return wxDataViewItem(pNode->getParent());
}

unsigned int ExpertDataViewModel::GetChildren(const wxDataViewItem & item, wxDataViewItemArray & children) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode)
	{
		pNode = m_pDocumentNode;
		children.push_back(wxDataViewItem((void*)(pNode)));
		return 1;
	}

	return pNode->getChildren(children);
}

unsigned int ExpertDataViewModel::GetColumnCount() const
{
	return 1;
}

wxString ExpertDataViewModel::GetColumnType(unsigned int col) const
{
	return wxString(wxT("void*"));
}

void ExpertDataViewModel::GetValue(wxVariant & variant, const wxDataViewItem & item, unsigned int col) const
{
	ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	variant = pNode;
}

bool ExpertDataViewModel::SetValue(const wxVariant & variant, const wxDataViewItem & item, unsigned int col)
{
	m_pDocumentEditor->changed();

	return false;
}

bool ExpertDataViewModel::HasDefaultCompare() const
{
	return true;
}

int ExpertDataViewModel::Compare(const wxDataViewItem & item1, const wxDataViewItem & item2, unsigned int column, bool ascending) const
{
	ElementDataViewModelNode *pNode1 = (ElementDataViewModelNode*)item1.GetID();
	ElementDataViewModelNode *pNode2 = (ElementDataViewModelNode*)item2.GetID();

	// Sort by type, attributes come first
	if (pNode1->getElementType() == ElementDataViewModelNode::AttributeName)
	{
		if (pNode2->getElementType() == ElementDataViewModelNode::ValueElement)
			return 1;
	}
	else if (pNode2->getElementType() == ElementDataViewModelNode::AttributeName)
	{
		if (pNode2->getElementType() == ElementDataViewModelNode::ValueElement)
			return -1;
	}

	ElementDataViewModelNode *pParentNode = pNode1->getParent();
	Separatista::Element *pParentElement = pParentNode->getSepaElement();
	const Separatista::ElementDescriptor *pParentDescriptor = pParentElement->getElementDescriptor();
	
	// Walk over all child element descriptors and try to match tags
	wxString tag1 = pNode1->getSepaElement()->getTag();
	wxString tag2 = pNode2->getSepaElement()->getTag();
	// Speedup
	if (tag1 == tag2)
		return 0;

	for (size_t i = 0; i < pParentDescriptor->m_nElementCount; i++)
	{
		if (tag1 == pParentDescriptor->m_pChildren[i].m_pTag)
			return -1;
		else if (tag2 == pParentDescriptor->m_pChildren[i].m_pTag)
			return 1;
	}

	// Sort alphabetically
	return wxStrcmp_String(pNode1->getLabel(), pNode2->getLabel());
}

void ExpertDataViewModel::OnContextMenu(wxWindow *pWindow, wxDataViewEvent & evt)
{
	wxDataViewItem item = evt.GetItem();
	
	if (item.IsOk())
	{
		ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();
		pNode->OnContextMenu(pWindow, evt);
	}
}

