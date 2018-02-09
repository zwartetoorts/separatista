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

#ifndef SEPARATISTA_GUI_EXPERTDATAVIEWMODEL_H
#define SEPARATISTA_GUI_EXPERTDATAVIEWMODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>

#include <wx/dataview.h>

#include "documenteditor.h"

// Forward decl
class LeafElementDataViewModelNode;
class AttributedElementDataViewModelNode;
class AttributeDataViewModelNode;
class ExpertDataViewModel;

class ElementDataViewModelNode : public Separatista::ElementListener
{
public:
	ElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pSepaElement, ElementDataViewModelNode *pParent = NULL);

	virtual ~ElementDataViewModelNode();

	ExpertDataViewModel* getModel() const;

	ElementDataViewModelNode* getParent() const;

	Separatista::Element* getSepaElement() const;

	enum ElementType
	{
		ValueElement,
		BranchElement,
		LeafElement,
		AttributedLeafElement,
		AttributeName,
		AttributeValue
	};

	size_t getIndex() const;

	virtual ElementType getElementType() const = NULL;

	virtual size_t getChildren(wxDataViewItemArray &children) const;

	virtual void removeChild(ElementDataViewModelNode *pChild);

	virtual wxString getLabel() const;

	virtual void setValue(const wxString &value);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);
	void elementCreated(Separatista::Element *pParent, Separatista::Element *pChild);
	void elementDeleted(Separatista::Element *pElement);

	virtual void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt) = NULL;

private:
	ExpertDataViewModel *m_pDataViewModel;
	ElementDataViewModelNode *m_pParent;
	Separatista::Element *m_pSepaElement;
	size_t m_nIndex;
	static size_t m_nElementCounter;
};

class ValueElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	ValueElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, LeafElementDataViewModelNode *pParent);

	ElementType getElementType() const;

	wxString getLabel() const;

	void setValue(const wxString &value);

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);
};

class AttributeValueDataViewModelNode : public ElementDataViewModelNode
{
public:
	AttributeValueDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, AttributeDataViewModelNode *pParent);

	ElementType getElementType() const;

	wxString getLabel() const;

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);

	void setValue(const wxString &value);

};

class AttributeDataViewModelNode : public ElementDataViewModelNode
{
public:
	AttributeDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, AttributedElementDataViewModelNode *pParent);
	
	~AttributeDataViewModelNode();

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;

	void removeChild(ElementDataViewModelNode *pChild);

	wxString getLabel() const;

	wxString getValue() const;

	void setValue(const wxString &value);

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);

private:
	wxString m_attributeName;
	AttributeValueDataViewModelNode *m_pValueNode;
};

class LeafElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	LeafElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, ElementDataViewModelNode *pParent = NULL);

	~LeafElementDataViewModelNode();

	size_t getChildren(wxDataViewItemArray &children) const;

	void removeChild(ElementDataViewModelNode *pChild);

	ElementType getElementType() const;

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);

private:
	ValueElementDataViewModelNode *m_pValueNode;
};

/**
	This is a very poor implementation of an Attributed element. It only supports having one single
	attribute, but that's all I've encountered in all the sepa documents so far. Why waste effort to
	support more if this is enough?
	TODO: better implementation :-)
*/
class AttributedElementDataViewModelNode : public LeafElementDataViewModelNode
{
public:
	AttributedElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, const wxString &attributeName, ElementDataViewModelNode *pParent = NULL);

	~AttributedElementDataViewModelNode();

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void elementValueChanged(Separatista::Element *pElement, const wchar_t *pNewValue);

private:
	AttributeDataViewModelNode *m_pAttributeNode;
};

class BranchElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	BranchElementDataViewModelNode(ExpertDataViewModel *pDataViewModel, Separatista::Element *pElement, ElementDataViewModelNode *pParent = NULL);

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;

	void removeChild(ElementDataViewModelNode *pChild);

	void addChild(ElementDataViewModelNode *pChild);

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);

	void OnCommandCreate(wxCommandEvent &evt);

	void OnCommandRemove(wxCommandEvent &evt);

	void elementCreated(Separatista::Element *pParent, Separatista::Element *pChild);

private:
	std::vector<ElementDataViewModelNode*> m_children;
};

class ExpertDataViewModel : public wxDataViewModel
{
public:
	ExpertDataViewModel(DocumentEditor *pDocumentEditor);

	bool IsContainer(const wxDataViewItem &item) const;

	wxDataViewItem GetParent(const wxDataViewItem &item) const;

	unsigned int GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const;

	unsigned int GetColumnCount() const;

	wxString GetColumnType(unsigned int col) const;

	void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const;

	bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);

	bool HasDefaultCompare() const;

	int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const;

	void OnContextMenu(wxWindow *pWindow, wxDataViewEvent &evt);
private:
	BranchElementDataViewModelNode *m_pDocumentNode;
	DocumentEditor* m_pDocumentEditor;
};

#endif // !defined SEPARATISTA_GUI_EXPERTDATAVIEWMODEL_H
