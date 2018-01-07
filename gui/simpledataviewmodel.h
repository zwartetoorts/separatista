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

#include "documenteditor.h"

class SimpleDataViewModelNode
{
public:
	/// C'tor, builds the tree from the SepaDocument
	SimpleDataViewModelNode(const SimpleViewData::Element *pElement, Separatista::SeparatistaDocument *pSepaDocument);

	/// C'tor for a simpele element
	SimpleDataViewModelNode(const SimpleViewData::Element *pElement, Separatista::Element *pSepaElement, SimpleDataViewModelNode *pParent = NULL);

	/// Returns the SimpleViewData Element
	const SimpleViewData::Element* getSimpleViewDataElement() const;
	
	/// Returns the Separatista Element pointed to by the SimpleViewElement DocumentPath element
	Separatista::Element* getSepaElement() const;

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

protected:
	/// 
	void buildModelTree(const SimpleViewData::Element *pElement, Separatista::Element *pSepaElement);

	
private:
	const SimpleViewData::Element *m_pElement;
	Separatista::Element *m_pSepaElement;
	SimpleDataViewModelNode *m_pParent;
	std::vector<SimpleDataViewModelNode*> m_children;
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

private:
	DocumentEditor *m_pDocumentEditor;
	SimpleDataViewModelNode m_rootNode;
};

#endif // !defined SEPARATISTA_GUI_SIMPLEDATAVIEWMODEL_H
