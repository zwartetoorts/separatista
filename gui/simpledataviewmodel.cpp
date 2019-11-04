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

size_t SimpleDataViewModelNode::m_nElementCounter = 0;

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, Separatista::SeparatistaDocument *pSepaDocument)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaDocument)
{
	m_pParent = NULL;
	m_pAttribute = NULL;
	m_nIndex = m_nElementCounter++;

	if (m_pSepaElement)
		m_pSepaElement->addElementListener(this);

	if(pElement && pSepaDocument)
		buildModelTree(pElement, pSepaDocument);
}

SimpleDataViewModelNode::SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, const SimpleViewData::Element *pAttributeElement, Separatista::Element *pSepaElement, Separatista::Element *pSepaParentElement, SimpleDataViewModelNode *pParent)
	:m_pDataViewModel(pModel), m_pElement(pElement), m_pSepaElement(pSepaElement), m_pParent(pParent), m_pAttribute(pAttributeElement)
{
	m_nIndex = m_nElementCounter++;

	// Receive notifications for element deletion and updates
	if(m_pSepaElement)
		m_pSepaElement->addElementListener(this);
	if (pSepaParentElement)
		addSepaParentElement(pSepaParentElement);
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
	
}

void SimpleDataViewModelNode::elementDeleted(Separatista::Element * pElement)
{
	
	if (pElement == getSepaElement())
	{
		// Check for root element type
		const SimpleViewData::Element *pTypeElement = getSimpleViewDataElement()->getChildByType(SimpleViewData::Element::Type);
		if (!pTypeElement)
			return;
		if (pTypeElement->getValue() == wxT("Root") || pTypeElement->getValue() == wxT("Documentroot"))
		{
			// Remove all children, but keep this element
			for (auto it = m_children.begin(); it != m_children.end(); it++)
			{
				m_pDataViewModel->ItemDeleted(wxDataViewItem(this), wxDataViewItem(*it));
			}
			m_children.clear();

			m_pSepaElement = NULL;
			
			// In case of "Root" element, also remove the element itself
			if (pTypeElement->getValue() == wxT("Root"))
			{
				m_pParent->removeChild(this);
				m_pDataViewModel->ItemDeleted(wxDataViewItem(m_pParent), wxDataViewItem(this));
				delete this;
			}
		}
		else
		{
			m_pSepaElement = NULL;

			// DocumentRoot element has Root as type, wx doesn't like ValueChanged on the root element
			if(getSimpleViewDataElement()->getType() != SimpleViewData::Element::Root)
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
		return m_pParent->createDocumentPath();
	}
	else
	{
		// Create Parent DocumentPath
		pSepaParentElement = m_pParent->createDocumentPath();
		addSepaParentElement(pSepaParentElement);
		// Create this DocumentPath
		for (; pDocPathElement != NULL; pDocPathElement = pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath),
											pSepaParentElement = pSepaElement)
		{
			pSepaElement = pSepaParentElement->createElementByTag(pDocPathElement->getValue(), index);
			// Check for last docpath element
			if (pDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath) == NULL)
			{
				// Is last
				m_pSepaElement = pSepaElement;
				m_pSepaElement->addElementListener(this);
			}
			else
			{
				// Not last
				addSepaParentElement(pSepaElement);
			}
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
			(*it)->setElementValue(defaultValue);
	}
}

void SimpleDataViewModelNode::onCommandSetDefaultvalue(wxCommandEvent & evt)
{
	this->setElementValue(getDefaultValue());
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
			}
			else
			{
				// Has type element, check type for Root
				if (pSimpleTypeElement->getValue() == wxT("Root") ||
					pSimpleTypeElement->getValue() == wxT("Documentroot") || true)
				{
					// Get all sepa elements with this document path
					Separatista::Element::TagKeyRange range;
					Separatista::Element::TagKeyMap::const_iterator it;
					bool cont = true, init = false;

					while (cont)
					{
						pSimpleDocPathElement = pSimpleChildElement;
						pSepaParentElement = pSepaElement;
						pNewNode = new SimpleDataViewModelNode(m_pDataViewModel, pSimpleChildElement, NULL, NULL, pSepaElement, this);
						appendChild(pNewNode);

						// Go to the end of the document path
						while ((pSimpleDocPathElement = pSimpleDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath)) != NULL)
						{
							auto cr = pSepaParentElement->getAllByTagName(pSimpleDocPathElement->getValue());
							auto crit = cr.m_begin;
							if (crit == cr.m_end)
								break;
							pSepaChildElement = crit->second;
							
							if (pSimpleDocPathElement->getChildByType(SimpleViewData::Element::DocumentPath) != NULL)
							{
								// The current document path element is not the last element
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
								}
								if (it != range.m_end)
								{
									pNewNode->m_pSepaElement = it->second;
									pNewNode->buildModelTree(pSimpleChildElement, it->second);
									it++;
								}
								else
								{
									cont = false;
								}

							}
						}
					}
				}
				else
				{
					// Type is not Root
					
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
			menu.Enable(ID_COMMAND_SIMPLE_CREATE, false);
			menu.Enable(ID_COMMAND_SIMPLE_CREATE_DEFAULTS, false);
			menu.Enable(ID_COMMAND_SIMPLE_REMOVE, false);
			
			// Check for set default value
			wxString defaultValue = pNode->getDefaultValue();
			if(defaultValue.Len() == 0)
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


