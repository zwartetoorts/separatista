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

#ifndef SEPARATISTA_GUI_SIMPLEDATAVIEWMODEL_H
#define SEPARATISTA_GUI_SIMPLEDATAVIEWMODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>

#include <wx/dataview.h>

#include <separatista/separatistadocument.h>
#include <separatista/element.h>

#include "simpleviewdata.h"

// Forward decl
class SimpleDataViewModel;
class DocumentEditor;

class SimpleDataViewModelNode : public Separatista::ElementListener
{
public:
	/// C'tor, builds the tree from the SepaDocument
	SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, Separatista::SeparatistaDocument *pSepaDocument);

	/// C'tor for a simpele element
	SimpleDataViewModelNode(SimpleDataViewModel *pModel, const SimpleViewData::Element *pElement, const SimpleViewData::Element *pAttributeElement, Separatista::Element *pSepaElement, Separatista::Element *pSepaParentElement, SimpleDataViewModelNode *pParent = NULL);

	/// D'tor destroys all children
	~SimpleDataViewModelNode();

	/// Returns the SimpleViewData Element
	const SimpleViewData::Element* getSimpleViewDataElement() const;

	/// Returns the SimpleViewData Attribute Element
	const SimpleViewData::Element* getSimpleViewDataAttributeElement() const;
	
	/// Returns the Separatista Element pointed to by the SimpleViewElement DocumentPath element
	Separatista::Element* getSepaElement() const;

	/// Set the Separatista Element, also sets an elementlistener on this element branch
	void setSepaElement(Separatista::Element *pSepaElement);

	/// Returns the parent node
	SimpleDataViewModelNode* getParent() const;

	/// Set the parent node
	void setParent(SimpleDataViewModelNode* pParent);

	/// Get the Child element count
	size_t getChildCount() const;

	/// Get the Child SimpleDataViewModelNode at index
	SimpleDataViewModelNode* getChild(size_t index) const;

	/// Append the Child SimpelDataViewModelNode
	void appendChild(SimpleDataViewModelNode *pChild);

	/// Removes the Child SimpleDataViewModelNode
	void removeChild(SimpleDataViewModelNode *pChild);

	// Separatista::ElementListener methods
	void elementCreated(Separatista::Element *pParent, Separatista::Element *pElement);
	void elementDeleted(Separatista::Element *pElement);
	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);

	// Getter and setters
	const wxString getElementValue() const;
	void setElementValue(const wxString &value);
	void setElementValue(const wxDateTime &dt, bool bWithTime);

	Separatista::Element* createDocumentPath(size_t index = 0);

	// Compare
	int compareTo(const SimpleDataViewModelNode *pOtherNode) const;

	// Menu events
	void onCommandRemove(wxCommandEvent &evt);
	void onCommandCreate(wxCommandEvent &evt);
	void onCommandCreateDefaults(wxCommandEvent &evt);

protected:
	/// Builds the internal tree recursively
	void buildModelTree(const SimpleViewData::Element *pElement, Separatista::Element *pSepaElement);

private:
	SimpleDataViewModel *m_pDataViewModel;
	const SimpleViewData::Element *m_pElement;
	const SimpleViewData::Element *m_pAttribute;
	Separatista::Element *m_pSepaElement;
	Separatista::Element *m_pSepaParentElement;
	SimpleDataViewModelNode *m_pParent;
	std::vector<SimpleDataViewModelNode*> m_children;
	size_t m_nIndex;

	/// Global counter for sorting elements in order of creation
	static size_t m_nElementCounter;
};

class SimpleDataViewModel : public wxDataViewModel
{
public:
	SimpleDataViewModel(DocumentEditor *pDocumentEditor);

	bool IsContainer(const wxDataViewItem &item) const;

	wxDataViewItem GetParent(const wxDataViewItem &item) const;

	unsigned int GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const;

	unsigned int GetColumnCount() const;

	wxString GetColumnType(unsigned int col) const;

	void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const;

	bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);

	bool HasDefaultCompare() const;

	int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const;

	bool GetAttr(const wxDataViewItem &item, unsigned int col, wxDataViewItemAttr &attr) const;

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

private:
	DocumentEditor *m_pDocumentEditor;
	SimpleDataViewModelNode m_rootNode;
};

#endif // !defined SEPARATISTA_GUI_SIMPLEDATAVIEWMODEL_H
