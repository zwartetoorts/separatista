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

#include <windows.h>
#include <olectl.h>

#include "dll.h"
#include "classfactory.h"


/**
	Globals
*/

LPTSTR g_lpszDllPath = NULL;
UINT g_uDllRefCount = 0;
UINT g_uLockCount = 0;

/**
	DllMain
*/

BOOL WINAPI DllMain(HINSTANCE hinstDll,
					DWORD fdwReason,
					LPVOID lpvReserved)
{
	DWORD dwPathLen = 0;
	DWORD dwPathRet;

	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Save the Dll path
		do{
			if(g_lpszDllPath)
				delete g_lpszDllPath;
			dwPathLen += MAX_PATH;
			g_lpszDllPath = new TCHAR[dwPathLen];
			if(!g_lpszDllPath)
				return E_OUTOFMEMORY;
			dwPathRet = GetModuleFileName(hinstDll, g_lpszDllPath, dwPathLen);
		}while(dwPathRet == dwPathLen);
		break;
	case DLL_PROCESS_DETACH:
		// Free the Dll path
		if(g_lpszDllPath)
			delete g_lpszDllPath;
	}
	Separatista::MT940SDocument *doc = new Separatista::MT940SDocument();
	doc->Open("C:\\Documents and Settings\\Okkel Klaver\\Mijn documenten\\Downloads\\MT940.swi");
	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid,
						 REFIID riid,
						 LPVOID* ppv)
{
	HRESULT hRet;
	SepaControlClassFactory* pFactory;

	*ppv = NULL;
	return CLASS_E_CLASSNOTAVAILABLE;

	if(!pFactory)
		return E_OUTOFMEMORY;
	
	hRet = pFactory->QueryInterface(riid, ppv);
	if(hRet != S_OK)
		delete pFactory;
	return hRet;
}

STDAPI DllCanUnloadNow()
{
	if(0 == g_uDllRefCount &&
		0 == g_uLockCount)
		return S_OK;
	return S_FALSE;
}

struct __declspec(uuid("6B20C63D-F57B-4755-9D58-11D93D7EC908")) ISepaControlTypeLib;

STDAPI DllUnregisterServer()
{
	HRESULT hRet;
	
	hRet = UnRegisterTypeLib(__uuidof(ISepaControlTypeLib), 1, 0, 0, SYS_WIN32);
	
	return S_OK;
}

STDAPI DllRegisterServer()
{
	HRESULT hr = S_OK;
	ITypeLib* pTypeLib;

	if(!g_lpszDllPath)
		return SELFREG_E_TYPELIB;

	hr = LoadTypeLibEx(g_lpszDllPath, REGKIND_REGISTER, &pTypeLib);
	if(hr != S_OK)
		return SELFREG_E_TYPELIB;

	if(hr != S_OK)
		DllUnregisterServer();
	pTypeLib->Release();
	return hr;
}



