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

class ElementDataViewModelNode
{
public:
	ElementDataViewModelNode(Separatista::Element *pElement, ElementDataViewModelNode *pParent = NULL);

	ElementDataViewModelNode* getParent() const;

	Separatista::Element* getSepaElement() const;

	enum ElementType
	{
		ValueElement,
		BranchElement,
		LeafElement,
		AttributedLeafElement
	};


	virtual ElementType getElementType() const = NULL;

	virtual size_t getChildren(wxDataViewItemArray &children) const = NULL;

	virtual wxString getLabel() const;

private:
	ElementDataViewModelNode *m_pParent;
	Separatista::Element *m_pSepaElement;
};

class ValueElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	ValueElementDataViewModelNode(Separatista::Element *pElement, LeafElementDataViewModelNode *pParent);

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;

	wxString getLabel() const;

	wxString getValue() const;

	void setValue(const wxString &value);
};

class AttributeValueElementDataViewModelNode : public ValueElementDataViewModelNode
{
public:
	AttributeValueElementDataViewModelNode(Separatista::Element *pElement, const wxString &attributeName, AttributedElementDataViewModelNode *pParent);
	
	wxString getLabel() const;

	wxString getValue() const;

	void setValue(const wxString &value);
private:
	wxString m_attributeName;
};

class LeafElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	LeafElementDataViewModelNode(Separatista::Element *pElement, ElementDataViewModelNode *pParent = NULL);

	size_t getChildren(wxDataViewItemArray &children) const;

	ElementType getElementType() const;

	wxString getValue() const;

	void setValue(const wxString value);
private:
	ValueElementDataViewModelNode m_valueNode;
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
	AttributedElementDataViewModelNode(Separatista::Element *pElement, const wxString &attributeName, ElementDataViewModelNode *pParent = NULL);

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;
	
	wxString getAttributeValue() const;

	void setAttributeValue(const wxString &value);

private:
	AttributeValueElementDataViewModelNode m_attributeValue;
};

class BranchElementDataViewModelNode : public ElementDataViewModelNode
{
public:
	BranchElementDataViewModelNode(Separatista::Element *pElement, ElementDataViewModelNode *pParent = NULL);

	ElementType getElementType() const;

	size_t getChildren(wxDataViewItemArray &children) const;

	void addChild(ElementDataViewModelNode *pChild);

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
private:
	BranchElementDataViewModelNode m_documentNode;
	DocumentEditor* m_pDocumentEditor;
};

#endif // !defined SEPARATISTA_GUI_EXPERTDATAVIEWMODEL_H
