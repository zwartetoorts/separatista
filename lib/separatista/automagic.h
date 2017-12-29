/***************************************************************************
*   Copyright (C) 2017 by Okkel Klaver   *
*   info@vanhetland.nl   *
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

#include <string>

#include "separatista/separatista.h"
#include "separatista/xerces_types.h"
#include "separatista/element.h"
#include "separatista/separatistadocument.h"

#ifndef SEPARATISTA_AUTOMAGIC_H
#define SEPARATISTA_AUTOMAGIC_H

namespace Separatista
{
	// Forward decl
	class AutoMagic;

	/**
		PathWatcher waits until the end element of a full path is created and then notifies an AutoMagic of events.
	*/
	class PathWatcher : public ElementListener
	{
	public:
		PathWatcher(AutoMagic *pAutoMagic, Element *pElement, const wchar_t *pPath);

		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
		virtual void elementCreated(Element *pParent, Element *pChild);
		virtual void elementDeleted(Element *pElement);
	protected:
		const wchar_t *m_pPath;
		AutoMagic *m_pAutoMagic;
	};

	/**
		Base class for all AutoMagic. 
	*/
	class AutoMagic : public ElementListener
	{
	public:
		/// Empty c'tor
		AutoMagic();

		/// C'tor for AutomagicFactory, doesn't create valuepath
		AutoMagic(Element *pBaseElement);
		/**
			Creates ValuePath and sets listeners on BaseElement
		*/
		AutoMagic(Element *pBaseElement, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
		virtual void elementCreated(Element *pParent, Element *pChild);
		virtual void elementDeleted(Element *pElement);

		/// Called from PathWatcher when the final element's value changes
		virtual void doValueMagic(Element *pElement, const wchar_t *pNewValue) = 0;
		/// Called from PathWatcher when the final element is created
		virtual void doCreatedMagic(Element *pParent, Element *pChild) = 0;
		/// Called from PathWatcher when the final element is deleted
		virtual void doDeletedMagic(Element *pElemenet) = 0;

		/**
			Global method for hooking AutoMagic to documents
		*/
		static void installAutoMagic(SeparatistaDocument *pDocument);

	protected:
		/**
			Gets the Value element if it still exists.
			@return Pointer to the value element, or NULL if the value element was destroyed.
		*/
		Element* getValueElement();

	private:
		Element *createValueElement(Element *pBaseElement, const wchar_t *pValuePath, const wchar_t *pDefaultValue = TEXT("0"));
		Element *m_pValueElement;
		Element *m_pBaseElement;
	};

	template <class T>
	class AutoMagicFactory : public AutoMagic
	{
	public:
		AutoMagicFactory(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		static void Create(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath)
		{
			DEBUG_STATIC_METHOD;

			new AutoMagicFactory<T>(pDocument, pBasePath, pWatchPath, pValuePath);
		};

		void doValueMagic(Element *pElement, const wchar_t *pNewValue);
		void doCreatedMagic(Element *pParent, Element *pChild);
		void doDeletedMagic(Element *pElemenet);

	private:
		const wchar_t *m_pWatchPath;
		const wchar_t *m_pValuePath;
	};

	class CountAutoMagic : public AutoMagic
	{
	public:
		CountAutoMagic(Element *pBaseElement, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		void doValueMagic(Element *pElement, const wchar_t *pNewValue);
		void doCreatedMagic(Element *pParent, Element *pChild);
		void doDeletedMagic(Element *pElemenet);
	private:
		size_t m_nCount;
	};

	class SumAutoMagic : public AutoMagic
	{
	public:
		SumAutoMagic(Element *pBaseElement, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		void doValueMagic(Element *pElement, const wchar_t *pNewValue);
		void doCreatedMagic(Element *pParent, Element *pChild);
		void doDeletedMagic(Element *pElemenet);
	protected:
		void sum();

		static unsigned int atoi(const wchar_t c);
		static wchar_t itoa(unsigned int i);
		/// Returns strlen pValue if not found
		static size_t findCh(const wchar_t *pValue, const wchar_t ch);

	private:
		std::list<Element*> m_elements;
	};
	
}

#endif // !defined SEPARATISTA_AUTOMAGIC_H
