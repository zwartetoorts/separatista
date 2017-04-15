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
	class PathWatcher : public ElementListener
	{
	public:
		PathWatcher(ElementListener *pAutoMagic, Element *pElement, const wchar_t *pPath);

		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
		virtual void elementCreated(Element *pParent, Element *pChild);
		virtual void elementDeleted(Element *pElement);
	protected:
		const wchar_t *m_pPath;
		ElementListener *m_pAutoMagic;
	};


	class AutoMagic : public ElementListener
	{
	public:
		AutoMagic(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue);
		virtual void elementCreated(Element *pParent, Element *pChild);
		virtual void elementDeleted(Element *pElement);

		static void installAutoMagic(SeparatistaDocument *pDocument);

	protected:
		Element* createValueElement();

	private:
		Element *m_pBaseElement;
		const wchar_t *m_pWatchPath;
		const wchar_t *m_pValuePath;
	};

	class CountAutoMagic : public AutoMagic
	{
	public:
		CountAutoMagic(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		virtual void elementCreated(Element *pParent, Element *pChild);
		virtual void elementDeleted(Element *pElement);

	private:
		size_t m_nCount;
	};

	class SumAutoMagic : public AutoMagic
	{
	public:
		SumAutoMagic(SeparatistaDocument *pDocument, const wchar_t *pBasePath, const wchar_t *pWatchPath, const wchar_t *pValuePath);

		virtual void elementValueChanged(Element *pElement, const wchar_t *pNewValue);

	private:
		std::wstring m_sum;
	};
	
}

#endif // !defined SEPARATISTA_AUTOMAGIC_H
