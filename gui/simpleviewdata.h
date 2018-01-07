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

#ifndef SEPARATISTA_GUI_SIMPLEVIEWDATA_H
#define SEPARATISTA_GUI_SIMPLEVIEWDATA_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filename.h>
#include <unordered_map>

/**
	Class handling all Simple View Data.
*/
class SimpleViewData
{
public:
	/**
		Creates a SimpleViewData from a file.
		@see parseLine
		@throws wxString containing an error, which is a bug in the program
	*/
	SimpleViewData(const wxFileName &FileName);

	/**
		SimpleViewData Elements are build as trees from text maps.
		@see The maps directory for examples and syntax.
	*/
	class Element
	{
	public:
		enum ElementType
		{
			Root = 0,
			SimplePath,
			//SimplePathAttribute,
			Type,
			OptionKey,
			OptionValue,
			DocumentPath,
			DocumentPathAttribute,
			DefaultValue
		};

		Element(ElementType type);

		~Element();

		ElementType getType() const;

		/// Return the value (name) of the element
		const wxString& getValue() const;

		/// Set the value (name) of the element
		void setValue(const wxString &value);

		/**
			Adds an Element to it's parent, but requires it's value is unique.
			If the value is already present in the child Elements, the already present is returned and the 
			to-be-inserted Element is deleted.
		*/
		Element* addChild(Element *pElement);

		const Element* getChild(size_t index) const;

		size_t getChildCount() const;

		const Element* getChildByType(ElementType t) const;

	private:
		ElementType m_type;
		std::vector<Element*> m_elements;
		wxString m_value;
	};
	
	/// Return the root element as pointer, do not delete
	const Element* getRootElement() const;

protected:
	/**
		Recurses into the line read from a map file, creating elements.
		@param pParent The parent Element to append the Element to.
		@param pElement Empty Element object. This function will set it's value and add to the parent object.
		@see SimpleViewData::Element::addChild
		@throws wxString to report an error, which always is a bug in the program.
	*/
	const wxChar * parseLine(const wxChar *pLine, Element *pParent, Element *pElement);

private:
	Element m_RootElement;
};

#endif // !defined SEPARATISTA_GUI_SIMPLEVIEWDATA_H
