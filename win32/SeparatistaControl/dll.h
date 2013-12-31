/***************************************************************************
 *   Copyright (C) 2013 by Okkel Klaver   *
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

#ifndef SEPARATISTACONTROL_DLL_H
#define SEPARATISTACONTROL_DLL_H

#include <windows.h>

#include "mt940s/mt940s.h"

// {6B20C63D-F57B-4755-9D58-11D93D7EC908}
DEFINE_GUID(SepaControlTypeLib, 
0x6b20c63d, 0xf57b, 0x4755, 0x9d, 0x58, 0x11, 0xd9, 0x3d, 0x7e, 0xc9, 0x8);

///	The global Dll reference counter
extern "C" UINT g_uDllRefCount;

/// The global Dll lock counter
extern "C" UINT g_uLockCount;

/// The global path to the Dll, stored from DllMain
extern "C" LPTSTR g_lpszDllPath;

#endif // SEPARATISTACONTROL_DLL_H