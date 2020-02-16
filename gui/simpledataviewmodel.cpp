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
#include "documenteditor.h"
#include "simpledataviewmodel.h"

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, Separatista::SeparatistaDocument *pSepaDocument)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaDocument)
{
	m_pParent = NULL;
	m_pAttribute = NULL;
	m_nIndex = 0;

	if (m_pSepaElement)
		m_pSepaElement->addElementListener(this);

	if(pElement && pSepaDocument)
		buildModelTree(pElement, pSepaDocument);
}

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, const SimpleViewData::Element *pAttributeElement, Separatista::Element *pSepaElement, Separatista::Element *pSepaParentElement, SimpleDataViewModelNode *pParent, size_t nIndex)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaElement), m_pParent(pParent), m_pAttribute(pAttributeElement), m_nIndex(nIndex)
{
	// Receive notifications for element deletion and updates
	if(m_pSepaElement)
		m_pSepaElement->addElementListener(this);
	if (pSepaParentElement)
		addSepaParentElement(pSepaParentElement);
}

SimpleDataViewModelNode::SimpleDataViewModelNode(const SimpleDataViewModelNode& OtherNode)
	:m_nIndex(OtherNode.m_nIndex + 1),
	m_parents(OtherNode.m_parents),
	m_pAttribute(OtherNode.m_pAttribute),
	m_pElement(OtherNode.m_pElement),
	m_pDataViewModel(OtherNode.m_pDataViewModel),
	m_pParent(OtherNode.m_pParent),
	m_pSepaElement(NULL)
{
	// Add elementlisteners to all parents
	auto parents = m_parents;
	while (!parents.empty())
	{
		parents.top()->addElementListener(this);
		parents.pop();
	}
}

SimpleDataViewModelNode::~SimpleDataViewModelNode()
{
	for (auto it = m_children.begin(); it != m_children.end(); it++)
		delete *it;

	while (!m_parents.empty())
	{
		m_parents.top()->removeElementListener(this);
		m_parents.pop();
	}
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

void SimpleDataViewModelNode::setSepaElement(Separatista::Element * pSepaElement)
{
	m_pSepaElement = pSepaElement;
	if (pSepaElement)
		pSepaElement->addElementListener(this);
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
	const SimpleViewData::Element *pDocPathElement;

	if (m_pSepaElement)
		return;

	// Match parent
	if (!m_parents.empty() && m_parents.top() == pParent)
	{
		pDocPathElement = m_pElement;
		for (size_t c = m_parents.size(); c > 0; --c)
		{
			if (pDocPathElement)
				pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath);
		}
		if (pDocPathElement && pDocPathElement->getValue() == pElement->getTag())
		{
			// Match
			// Is the created element the last element in my document path
			if (pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath) != NULL)
			{
				// Not the last
				addSepaParentElement(pElement);
			}
			else
			{
				// It is the final element
				setSepaElement(pElement);
				buildModelTree(m_pElement, pElement);

				// Check if a new sibbling node should be added
				size_t count = 0;
				Separatista::Element::TagKeyRange range = pParent->getAllByTagName(pElement->getTag());
				for (auto it = range.m_begin; it != range.m_end; it++)
					count++;

				if (pElement->getMaxOccurs() == 0 || pElement->getMaxOccurs() > count)
				{
					// Create new node
					Separatista::Element* pSepaParentElement = m_pParent->m_pSepaElement;
					//SimpleDataViewModelNode* pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, m_pElement, m_pAttribute, NULL, NULL, m_pParent, count);
					SimpleDataViewModelNode* pNewNode = new SimpleDataViewModelNode(*this);
										
					// Insert the new node to our parent
					m_pParent->appendChild(pNewNode);
					m_pDataViewModel->ItemAdded(wxDataViewItem(m_pParent), wxDataViewItem(pNewNode));
				}
			}
		}
	}
}

void SimpleDataViewModelNode::elementDeleted(Separatista::Element * pElement)
{
	// Match parent
	if (m_parents.empty())
		return;

	if (m_parents.top() == pElement)
	{
		m_parents.pop();
	}
	else if (pElement == m_pSepaElement)
	{
		// Decrease sibbling elements index if needed
		bool found = false;
		for (size_t i = 0; i < m_pParent->getChildCount(); i++)
		{
			if (!found)
			{
				if (m_pParent->getChild(i)->m_pSepaElement == pElement)
				{
					found = true;
				}
			}
			else
			{
				// Match element
				SimpleDataViewModelNode* pOthernode = m_pParent->getChild(i);
				if (pOthernode->getSimpleViewDataAttributeElement() != NULL ? 
					pOthernode->getSimpleViewDataAttributeElement() == getSimpleViewDataAttributeElement() :
					pOthernode->getSimpleViewDataElement() == getSimpleViewDataElement())
				{
					if (pOthernode->m_nIndex > m_nIndex)
						pOthernode->m_nIndex--;
				}
				else
					break;
			}
		}

		// Check for element count, don't remove element if it's still needed
		size_t max = m_pSepaElement->getMaxOccurs();
		if (max != 0 && max == m_nIndex - 1)
		{
			m_pSepaElement = NULL;
			m_pDataViewModel->ItemChanged(wxDataViewItem(this));
		}
		else
		{
			// Destroy all children and notify DataViewModel
			for (auto it = m_children.begin(); it != m_children.end(); it++)
			{
				m_pDataViewModel->ItemDeleted(wxDataViewItem(this), wxDataViewItem(*it));
			}
			m_children.clear();

			// Remove self
			m_pParent->removeChild(this);
			m_pDataViewModel->ItemDeleted(wxDataViewItem(m_pParent), wxDataViewItem(this));

			delete this;
			return;
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
		m_pSepaElement = createDocumentPath(m_nIndex);
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

bool SimpleDataViewModelNode::hasDefaultValue() const
{
	// Find the last DocumentPathElement
	const SimpleViewData::Element* pDocElement = m_pElement;
	const SimpleViewData::Element* pElement;
	while ((pElement = pDocElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL ||
		(pElement = pDocElement->getChildByType(SimpleViewData::Element::DocumentPathAttribute)) != NULL)
	{
		pDocElement = pElement;
	}

	return pDocElement->getChildByType(SimpleViewData::Element::DefaultValue) ? true : false;
}

wxString SimpleDataViewModelNode::getDefaultValue() const
{
	wxString defaultValue;

	// Find the last DocumentPathElement
	const SimpleViewData::Element *pDocElement = m_pElement;
	const SimpleViewData::Element *pElement;
	while ((pElement = pDocElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL ||
		(pElement = pDocElement->getChildByType(SimpleViewData::Element::DocumentPathAttribute)) != NULL)
	{
		pDocElement = pElement;
	}

	const SimpleViewData::Element *pValueElement = pDocElement->getChildByType(SimpleViewData::Element::DefaultValue);
	if(pValueElement)
		defaultValue = translateDefaultValue(pValueElement->getValue());

	return defaultValue;
}

void SimpleDataViewModelNode::addSepaParentElement(Separatista::Element * pSepaParentElement)
{
	m_parents.push(pSepaParentElement);
	pSepaParentElement->addElementListener(this);
}

Separatista::Element * SimpleDataViewModelNode::createDocumentPath(size_t index)
{
	const SimpleViewData::Element *pDocPathElement;
	Separatista::Element *pSepaElement, *pSepaParentElement;
	
	if (m_pSepaElement)
		return m_pSepaElement;
	// No Sepa Element present, check for DocumentPath element
	if ((pDocPathElement = m_pElement->getChildByType(SimpleViewData::Element::DocumentPath)) == NULL)
	{
		// No Documentpath element present, try parent
		return m_pParent->createDocumentPath(index);
	}
	else
	{
		// Create Parent DocumentPath
		pSepaParentElement = m_pParent->createDocumentPath(index);
		
		// Create this DocumentPath
		for (; pDocPathElement != NULL; pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath),
											pSepaParentElement = pSepaElement)
		{
			pSepaElement = pSepaParentElement->createElementByTag(pDocPathElement->getValue(), index);
		}
	}
	return m_pSepaElement;
}

int SimpleDataViewModelNode::compareTo(const SimpleDataViewModelNode * pOtherNode) const
{
	// Do both elements have the same value?
	if (m_pElement->getValue() == pOtherNode->getSimpleViewDataElement()->getValue())
	{
		if (m_nIndex < pOtherNode->m_nIndex)
			return -1;
		else
			return 1;
	}
	else
	{
		// Sort by SimpleViewData order
		SimpleDataViewModelNode *pParentNode = getParent();
		if (!pParentNode)
			return 0;

		return pParentNode->getSimpleViewDataElement()->compare(m_pElement, pOtherNode->getSimpleViewDataElement());
	}
	return 0;
}

void SimpleDataViewModelNode::onCommandRemove(wxCommandEvent & evt)
{
	if (m_pSepaElement && !m_parents.empty())
		m_parents.top()->destroyElement(m_pSepaElement);
}

void SimpleDataViewModelNode::onCommandCreate(wxCommandEvent & evt)
{
	const SimpleViewData::Element *pDocPathElement = m_pElement;
	Separatista::Element *pSepaParent = m_parents.top();

	while ((pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL)
	{
		Separatista::Element::TagKeyRange range = pSepaParent->getAllByTagName(pDocPathElement->getValue());
		size_t count = 0;
		for (auto it = range.m_begin; it != range.m_end; it++)
			count++;

		pSepaParent = pSepaParent->createElementByTag(pDocPathElement->getValue(), count);
	}
}

void SimpleDataViewModelNode::onCommandCreateDefaults(wxCommandEvent & evt)
{
	// Create nodes
	onCommandCreate(evt);

	// Set default values if any
	for (auto it = m_children.begin(); it != m_children.end(); it++)
	{
		wxString defaultValue = (*it)->getDefaultValue();
		if (defaultValue.Len() > 0)
		{
			try
			{
				(*it)->setElementValue(defaultValue);
			}
			catch (Separatista::Exception& e)
			{
				wxLogError(e.getMessage());
			}
		}
	}
}

void SimpleDataViewModelNode::onCommandSetDefaultvalue(wxCommandEvent & evt)
{
	try
	{
		this->setElementValue(getDefaultValue());
	}
	catch (Separatista::Exception & e)
	{
		wxLogError(e.getMessage());
	}
}

void SimpleDataViewModelNode::buildModelTree(const SimpleViewData::Element *pSimpleElement, Separatista::Element *pSepaElement)
{
	// Enum over all child SimpleElements and try to find a matching Sepa Element or continue with NULL
	const SimpleViewData::Element *pSimpleChildElement, *pSimpleDocPathElement, *pSimpleTypeElement, *pSimpleAttrElement;
	Separatista::Element *pSepaChildElement, *pSepaParentElement;
	SimpleDataViewModelNode *pNewNode;

	for (size_t i = 0; i < pSimpleElement->getChildCount(); i++)
	{
		pSimpleChildElement = pSimpleElement->getChild(i);
		// Only handle SimplePath elements
		if (pSimpleChildElement->getType() == SimpleViewData::Element::SimplePath)
		{
			// Check for type element
			if ((pSimpleTypeElement = pSimpleChildElement->getChildByType(SimpleViewData::Element::Type)) == NULL)
			{
				// Create new node
				pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, NULL, NULL, NULL, this);

				// No type element, recurse because this node has no use
				pNewNode->buildModelTree(pSimpleChildElement, pSepaElement);
				appendChild(pNewNode);
				m_pDataViewModel->ItemAdded(wxDataViewItem(this), wxDataViewItem(pNewNode));
			}
			else
			{
				// Has type element
				// Get all sepa elements with this document path
				Separatista::Element::TagKeyRange range;
				Separatista::Element::TagKeyMap::const_iterator it;
				bool cont = true, init = false;
				size_t count = 0;

				while (cont)
				{
					pSimpleDocPathElement = pSimpleChildElement;
					pSepaParentElement = pSepaElement;
					
					pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, NULL, NULL, pSepaElement, this, count);
					appendChild(pNewNode);
					m_pDataViewModel->ItemAdded(wxDataViewItem(this), wxDataViewItem(pNewNode));

					// Go to the end of the document path
					while ((pSimpleDocPathElement = pSimpleDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL)
					{
						if ((pSimpleAttrElement = pSimpleDocPathElement->getChildByType(SimpleViewData::Element::DocumentPathAttribute)) != NULL)
						{
							// The element has a attribute element
							pNewNode->m_pAttribute = pSimpleAttrElement;
						}

						if (pSepaParentElement)
						{
							auto cr = pSepaParentElement->getAllByTagName(pSimpleDocPathElement->getValue());
							auto crit = cr.m_begin;
							if (crit == cr.m_end)
							{
								cont = false;
								break;
							}
							pSepaChildElement = crit->second;
						}
						else
							pSepaChildElement = NULL;

						if (pSimpleDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath) != NULL)
						{
							// The current document path element is not the last element
							if (pSepaChildElement)
								pNewNode->addSepaParentElement(pSepaChildElement);
							pSepaParentElement = pSepaChildElement;
						}
						else
						{
							// The current document path element is the last element
							if (!init)
							{
								// Do init if not initialized yet
								init = true;
								range = pSepaParentElement->getAllByTagName(pSimpleDocPathElement->getValue());
								it = range.m_begin;
								count = 0;
							}
							if (it != range.m_end)
							{
								count++;
								pNewNode->setSepaElement(it->second);

								// Check for root or documentroot type
								if (pSimpleTypeElement->getValue() == wxT("Root") ||
									pSimpleTypeElement->getValue() == wxT("Documentroot"))
								{
									pNewNode->buildModelTree(pSimpleChildElement, it->second);
								}

								// Goto next
								pSepaChildElement = it->second;
								if (++it == range.m_end)
								{
									cont = false;

									// If aproprate, create an empty node for creation
									if (pSepaChildElement->getMaxOccurs() == 0 ||
										pSepaChildElement->getMaxOccurs() > count)
									{
										pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, NULL, NULL, pSepaParentElement, this, count);
										appendChild(pNewNode);
										m_pDataViewModel->ItemAdded(wxDataViewItem(this), wxDataViewItem(pNewNode));
									}
								}
							}
							else
							{
								cont = false;
							}
						}
					}
				}
			}
			
		}
	}
}

wxString SimpleDataViewModelNode::translateDefaultValue(const wxString &value) const
{
	wxString defaultValue;

	size_t len = value.Len();

	if(value[0] == wxT('"') && value[len - 1] == wxT('"'))
	{
		defaultValue = value.Mid(1, len - 2);
	}
	else
	{
		// It's a function
		if (value == wxT("Now"))
		{
			wxDateTime dt = wxDateTime::Now();
			defaultValue = dt.FormatISOCombined();
		}
		// It's a variable
		else if (value[0] == wxT('%') && value[len - 1] == wxT('%'))
		{
			defaultValue = m_pDataViewModel->getVariable(value.Mid(1, len - 2));
		}
	}

	return defaultValue;
}

SimpleDataViewModel::SimpleDataViewModel(DocumentEditor *pDocumentEditor)
	:m_rootNode(this, (pDocumentEditor->getSimpleViewData() ? pDocumentEditor->getSimpleViewData()->getRootElement() : NULL), pDocumentEditor->getDocument())
{
	m_pDocumentEditor = pDocumentEditor;
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
	case 0:
		return wxT("string");
	default:
		return wxT("void*");
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
	default:
		variant = (void*)pNode;
	}
}

bool SimpleDataViewModel::SetValue(const wxVariant & variant, const wxDataViewItem & item, unsigned int col)
{
	m_pDocumentEditor->changed();
	return false;
}

bool SimpleDataViewModel::HasDefaultCompare() const
{
	return true;
}

int SimpleDataViewModel::Compare(const wxDataViewItem & item1, const wxDataViewItem & item2, unsigned int column, bool ascending) const
{
	if (column == 0)
		return 0;
	
	// Get the SimpleDataViewModelNodes
	SimpleDataViewModelNode *pNode1 = (SimpleDataViewModelNode*)item1.GetID();
	SimpleDataViewModelNode *pNode2 = (SimpleDataViewModelNode*)item2.GetID();

	return pNode1->compareTo(pNode2);
}

bool SimpleDataViewModel::GetAttr(const wxDataViewItem & item, unsigned int col, wxDataViewItemAttr & attr) const
{
	SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)item.GetID();

	if (!pNode->getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::DocumentPath))
	{
		// Has no DocumentPath, let children do the formatting
		for (size_t i = 0; i < pNode->getChildCount(); i++)
		{
			GetAttr(wxDataViewItem(pNode->getChild(i)), col, attr);
		}
	}
	else if (!pNode->getSepaElement())
	{
		attr.SetItalic(true);
		attr.SetColour(*wxRED);
	}
	
	return true;
}

void SimpleDataViewModel::OnContextMenu(wxWindow *pWindow, wxDataViewEvent & evt)
{
	wxDataViewItem item = evt.GetItem();

	if (item.IsOk())
	{
		SimpleDataViewModelNode *pNode = (SimpleDataViewModelNode*)item.GetID();

		// Create context menu
		wxMenu menu;

		menu.Append(ID_COMMAND_SIMPLE_CREATE, wxT("Create"));
		menu.Append(ID_COMMAND_SIMPLE_CREATE_DEFAULTS, wxT("Create with default values"));
		menu.Append(ID_COMMAND_SIMPLE_REMOVE, wxT("Remove"));
		menu.Append(ID_COMMAND_SIMPLE_SET_DEFAULTVALUE, wxT("Set default value"));

		// Disable menu options
		const SimpleViewData::Element *pTypeElement = pNode->getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::Type);
		if (!pTypeElement)
			return;

		if (pTypeElement->getValue() == wxT("Documentroot") || pTypeElement->getValue() == wxT("Root"))
		{
			// Check if the element already exists
			if (pNode->getSepaElement())
			{
				// Exists
				menu.Enable(ID_COMMAND_SIMPLE_CREATE, false);
				menu.Enable(ID_COMMAND_SIMPLE_CREATE_DEFAULTS, false);
			}
			else
			{
				// Doesn't exist
				menu.Enable(ID_COMMAND_SIMPLE_REMOVE, false);
			}
			menu.Enable(ID_COMMAND_SIMPLE_SET_DEFAULTVALUE, false);
		}
		else 
		{
			// Check if the element already exists
			if (pNode->getSepaElement())
			{
				// Exists
				menu.Enable(ID_COMMAND_SIMPLE_CREATE, false);
				menu.Enable(ID_COMMAND_SIMPLE_CREATE_DEFAULTS, false);
			}
			else
			{
				// Doesn't exist
				menu.Enable(ID_COMMAND_SIMPLE_REMOVE, false);
			}
			
			// Check for default value
			if (!pNode->hasDefaultValue())
				menu.Enable(ID_COMMAND_SIMPLE_SET_DEFAULTVALUE, false);
		}

		pWindow->Bind(
			wxEVT_COMMAND_MENU_SELECTED,
			[pNode](wxCommandEvent &evt)
		{
			pNode->onCommandRemove(evt);
		},
			ID_COMMAND_SIMPLE_REMOVE);

		pWindow->Bind(
			wxEVT_COMMAND_MENU_SELECTED,
			[pNode](wxCommandEvent &evt)
		{
			pNode->onCommandCreate(evt);
		},
			ID_COMMAND_SIMPLE_CREATE);

		pWindow->Bind(
			wxEVT_COMMAND_MENU_SELECTED,
			[pNode](wxCommandEvent &evt)
		{
			pNode->onCommandCreateDefaults(evt);
		},
			ID_COMMAND_SIMPLE_CREATE_DEFAULTS);

		pWindow->Bind(
			wxEVT_COMMAND_MENU_SELECTED,
			[pNode](wxCommandEvent &evt)
		{
			pNode->onCommandSetDefaultvalue(evt);
		},
			ID_COMMAND_SIMPLE_SET_DEFAULTVALUE);

		pWindow->PopupMenu(&menu);

	}
}

wxString SimpleDataViewModel::getVariable(const wxString& variable)
{
	return m_pDocumentEditor->getVariable(variable);
}


