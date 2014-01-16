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

#ifndef SEPARATISTACONTROL_MACROS_H
#define SEPARATISTACONTROL_MACROS_H

#define SEPARATISTA_COM_PROPERTY_GET(type, name, modifier) \
	STDMETHOD(get##name)(type *p##name) modifier;

#define SEPARATISTA_COM_PROPERTY_SET(type, name, modifier) \
	STDMETHOD(set##name)(type name) modifier;

#define SEPARATISTA_COM_PROPERTY(type, name, modifier) \
	SEPARATISTA_COM_PROPERTY_GET(type, name, modifier) \
	SEPARATISTA_COM_PROPERTY_SET(type, name, modifier)

#endif // !defined SEPARATISTACONTROL_MACROS_H
