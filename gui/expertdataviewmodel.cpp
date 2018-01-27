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

#include "expertdataviewmodel.h"

ElementDataViewModelNode::ElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pSepaElement, ElementDataViewModelNode *pParent)
	:m_pDataViewModel(pDataViewModel),
	m_pSepaElement(pSepaElement),
	m_pParent(pParent)
{
	// Set listeners on elements
	if (pSepaElement)
		pSepaElement->addElementListener(this);
	if (pParent)
		pParent->getSepaElement()->addElementListener(this);
}

Separatista::Element* ElementDataViewModelNode::getSepaElement() const
{
	return m_pSepaElement;
}

ElementDataViewModelNode* ElementDataViewModelNode::getParent() const
{
	return m_pParent;
}

wxString ElementDataViewModelNode::getLabel() const
{
	return getSepaElement()->getTag();
}

void ElementDataViewModelNode::elementValueChanged(Separatista::Element * pElement, const wchar_t * pNewValue)
{
	m_pDataViewModel->ValueChanged(wxDataViewItem(this), 0);
}

void ElementDataViewModelNode::elementCreated(Separatista::Element * pParent, Separatista::Element * pChild)
{
}

void ElementDataViewModelNode::elementDeleted(Separatista::Element * pElement)
{
}

ValueElementDataViewModelNode::ValueElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, LeafElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent)
{

}

ElementDataViewModelNode::ElementType ValueElementDataViewModelNode::getElementType() const
{
	return ValueElement;
}

size_t ValueElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	return 0;
}

wxString ValueElementDataViewModelNode::getLabel() const
{
	return getSepaElement()->getTextValue();
}

wxString ValueElementDataViewModelNode::getValue() const
{
	return getLabel();
}

void ValueElementDataViewModelNode::setValue(const wxString &value)
{
	getSepaElement()->setValue(value);
}

AttributeValueElementDataViewModelNode::AttributeValueElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, AttributedElementDataViewModelNode *pParent)
	:ValueElementDataViewModelNode(pDataViewModel, pElement, pParent),
	m_attributeName(attributeName)
{

}

wxString AttributeValueElementDataViewModelNode::getLabel() const
{
	return m_attributeName;
}

wxString AttributeValueElementDataViewModelNode::getValue() const
{
	return getSepaElement()->getAttributeValue(m_attributeName);
}

void AttributeValueElementDataViewModelNode::setValue(const wxString &value)
{
	getSepaElement()->setValue(value);
}


LeafElementDataViewModelNode::LeafElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, ElementDataViewModelNode *pParent)
	:ElementDataViewModelNode(pDataViewModel, pElement, pParent),
	m_valueNode(pDataViewModel, pElement, this)
{

}

ElementDataViewModelNode::ElementType LeafElementDataViewModelNode::getElementType() const
{
	return LeafElement;
}

size_t LeafElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	children.push_back(wxDataViewItem((void*)&m_valueNode));
	return 1;
}

wxString LeafElementDataViewModelNode::getValue() const
{
	return m_valueNode.getValue();
}

void LeafElementDataViewModelNode::setValue(const wxString value)
{
	m_valueNode.setValue(value);
}

AttributedElementDataViewModelNode::AttributedElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, ElementDataViewModelNode *pParent)
	:LeafElementDataViewModelNode(pDataViewModel, pElement, pParent),
	m_attributeValue(pDataViewModel, pElement, attributeName, this)
{

}

ElementDataViewModelNode::ElementType AttributedElementDataViewModelNode::getElementType() const
{
	return AttributedLeafElement;
}

size_t AttributedElementDataViewModelNode::getChildren(wxDataViewItemArray &children) const
{
	size_t count = m_attributeValue.getChildren(children);
	
	return count + LeafElementDataViewModelNode::getChildren(children);
}

wxString AttributedElementDataViewModelNode::getAttributeValue() const
{
	return m_attributeValue.getValue();
}

void AttributedElementDataViewModelNode::setAttributeValue(const wxString &value)
{
	m_attributeValue.setValue(value);
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
					wxT("EUR"),
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
}

void BranchElementDataViewModelNode::addChild(ElementDataViewModelNode *pChild)
{
	m_children.push_back(pChild);
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

ElementDataViewModelNode::ElementType BranchElementDataViewModelNode::getElementType() const
{
	return BranchElement;
}

ExpertDataViewModel::ExpertDataViewModel(DocumentEditor *pDocumentEditor)
	:m_pDocumentEditor(pDocumentEditor),
	m_documentNode(this, pDocumentEditor->getDocument())
{

}

bool ExpertDataViewModel::IsContainer(const wxDataViewItem &item) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode)
		return true;

	switch (pNode->getElementType())
	{
	case ElementDataViewModelNode::ValueElement:
		return false;
	default:
		return true;
	}
}

wxDataViewItem ExpertDataViewModel::GetParent(const wxDataViewItem &item) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode || pNode == &m_documentNode)
		return wxDataViewItem(NULL);

	return wxDataViewItem(pNode->getParent());
}

unsigned int ExpertDataViewModel::GetChildren(const wxDataViewItem & item, wxDataViewItemArray & children) const
{
	const ElementDataViewModelNode *pNode = (ElementDataViewModelNode*)item.GetID();

	if (!pNode)
	{
		pNode = &m_documentNode;
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

