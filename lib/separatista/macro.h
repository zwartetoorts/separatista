/***************************************************************************
*   Copyright (C) 2014 by Okkel Klaver   *
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

#include <array>

#ifndef SEPARATISTA_MACRO_H
#define SEPARATISTA_MACRO_H

#define BEGIN_DECLARE_CLASS(name) \
class name : public Element \
	{ \
	public: \
	name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t* pTagName); \
	protected: \
	const wchar_t* const* getOrder(); \

#define BEGIN_DECLARE_CLASS_SUPER(type, name) \
class name : public Element, public Separatista::type \
	{ \
	public: \
	name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t* pTagName); \
	protected: \
	const wchar_t* const* getOrder(); \
	
#define END_DECLARE_CLASS };

#define DECLARE_CHILD(type, name, tag) \
	private: \
	type m_##name; \
	public: \
	static const wchar_t* tag; \
	type& get##name() { return m_##name; };

#define DECLARE_CHILD_MULTI(type, name, tag, size) \
	private: \
	std::array<type, size> m_##name##s; \
	public: \
	static const wchar_t *tag; \
	type& get##name(size_t index) { return m_##name##s[index]; };

#define DECLARE_TAG_MULTI(name, tag, size) \
	private: \
	std::array<const wchar_t*, size> m_##name##s; \
	public: \
	static const wchar_t *tag; \
	const wchar_t* get##name(size_t index) { return m_##name##s[index]; };

#define DECLARE_TAG_GET(name, tag) \
	public: \
	static const wchar_t* tag; \
	const wchar_t* get##name() { return getChildElementValue(tag); };

#define DECLARE_TAG_SET(name, tag) \
	void set##name(const wchar_t *pValue) { setChildElementValue(tag, pValue); };

#define DECLARE_TAG(name, tag) \
	DECLARE_TAG_GET(name, tag) \
	DECLARE_TAG_SET(name, tag)

#define DECLARE_TAG_ATTRIBUTE_GET(name, tag, attr) \
	const wchar_t* get##name##attr() { return getChildElementAttributeValue(tag, L#attr); };

#define DECLARE_TAG_ATTRIBUTE(name, tag, attr) \
	DECLARE_TAG_ATTRIBUTE_GET(name, tag, attr) \
	void set##name##attr(const wchar_t* pValue) { setChildElementAttributeValue(tag, L#attr, pValue); };

#define DECLARE_TAG_TYPE_GET(type, name, tag) \
	public: \
	static const wchar_t* tag; \
	type get##name();

#define DECLARE_TAG_TYPE(type, name, tag) \
	DECLARE_TAG_TYPE_GET(type, name, tag) \
	void set##name(type value);

#define DECLARE_TAG_ENUM_GET(type, name, count, tag) \
	public: \
	static const struct name##Table { type m_code; const wchar_t* m_value; } m_##name##Table[count]; \
	public: \
	static const wchar_t* tag; \
	type get##name();

#define DECLARE_TAG_ENUM(type, name, count, tag) \
	DECLARE_TAG_ENUM_GET(type, name, count, tag) \
	void set##name(type value);

#define DECLARE_TAG_TIME_GET(name, tag) \
	public: \
	static const wchar_t* tag; \
	time_t get##name() { \
		return toTime(getChildElementValue(tag)); };

#define DECLARE_TAG_TIME(name, tag) \
	DECLARE_TAG_TIME_GET(name, tag) \
	DECLARE_TAG_SET(name, tag)

#define DECLARE_TAG_LONG_GET(name, tag) \
	public: \
	static const wchar_t* tag; \
	long get##name() { \
		return toLong(getChildElementValue(tag)); };

#define DECLARE_TAG_LONG(name, tag) \
	DECLARE_TAG_LONG_GET(name, tag) \
	DECLARE_TAG_SET(name, tag);

#define DECLARE_TAG_UINT64_GET(name, tag) \
	public: \
	static const wchar_t* tag; \
	uint64_t get##name() { \
		return toUInt64(getChildElementValue(tag)); };

#define DECLARE_TAG_UINT64(name, tag) \
	DECLARE_TAG_UINT64_GET(name, tag) \
	DECLARE_TAG_SET(name, tag);

#define IMPLEMENT_CONSTRUCTOR(name) \
	SeparatistaPrivate::name::name(DOMDocument *pDocument, Element *pParent, DOMElement *pElement, const wchar_t *pTagName) \
	:Element(pDocument, pParent, pElement, pTagName)

#define IMPLEMENT_CHILD(child, tag) \
	, m_##child(pDocument, this, NULL, tag)

#define IMPLEMENT_TAG(name, tag) \
	const wchar_t* SeparatistaPrivate::name::tag = L#tag;

#define BEGIN_IMPLEMENT_CHILD_MULTI(type, child, tag, size) \
	, m_##child##s(std::array<type, size>{ {

#define IMPLEMENT_CHILD_MULTI(type, index, tag) \
	type(pDocument, pParent, pParent->getChildElement(index, tag), tag),

#define END_IMPLEMENT_CHILD_MULTI \
	}})

#define BEGIN_IMPLEMENT_TAG_MULTI(name, tag, size) \
	, m_##name##s(std::array<const wchar_t*, size> { {

#define IMPLEMENT_TAG_MULTI(index, tag) \
	getChildElementValue(index, tag),

#define END_IMPLEMENT_TAG_MULTI \
	}})

#define BEGIN_IMPLEMENT_TAG_ENUM(cls, type, name, tag) \
	type cls::get##name() \
	{ \
	const wchar_t *pValue = getChildElementValue(tag); \
	for(int i = 0; i < sizeof(m_##name##Table) / sizeof(m_##name##Table[0]); i++) \
		{ \
		if(std::wcscmp(m_##name##Table[i].m_value, pValue) == 0) \
		return m_##name##Table[i].m_code; \
		} \
		return (type)0; \
	} \
	void cls::set##name(type value) \
	{ \
	for(int i = 0; i < sizeof(m_##name##Table) / sizeof(m_##name##Table[0]); i++) \
		{ \
		if(m_##name##Table[i].m_code == value) \
			{\
			setChildElementValue(tag, m_##name##Table[i].m_value); \
			return; \
	} } } \
	const cls::##name##Table cls::m_##name##Table[] = {

#define IMPLEMENT_TAG_ENUM(code, value) \
	{ code, L#value },

#define END_IMPLEMENT_TAG_ENUM \
	};

#define BEGIN_IMPLEMENT_ORDER(name) \
	const wchar_t* const* SeparatistaPrivate::name::getOrder() \
	{ \
	static const wchar_t* order[] = { \

#define END_IMPLEMENT_ORDER  \
	, NULL }; \
	return order; }


#endif // !defined SEPARATISTA_MACRO_H
