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
#include "mt940sdocument.h"
#include "registrykey.h"


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

	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid,
						 REFIID riid,
						 LPVOID *ppv)
{
	HRESULT hRet;
	SepaControlClassFactory *pFactory;

	*ppv = NULL;
	if(IsEqualIID(rclsid, __uuidof(IMT940SDocument)))
		pFactory = new SepaControlClassFactory(SepaControlDispatch<IMT940SDocument>::Create<CMT940SDocument>);
	else
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

	RegistryKey 
	
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

	RegistryKey MT940SDocumentKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{6DF05A76-0582-415a-9B96-163F76914250}"));

	if(MT940SDocumentKey.isOpen())
	{
		MT940SDocumentKey = TEXT("MT940SDocument");

		RegistryKey MT940SDocumentInProcServerKey(MT940SDocumentKey, TEXT("InProcServer32"));

		if(!MT940SDocumentInProcServerKey.isOpen() ||
			!MT940SDocumentInProcServerKey.setValue(g_lpszDllPath) ||
			!MT940SDocumentInProcServerKey.setValue(TEXT("ThreadingModel"), TEXT("Apartment")))
			hr = E_FAIL;
		else
			if(!MT940SDocumentKey.setValue(TEXT("InProcServer32"), g_lpszDllPath) ||
				!MT940SDocumentKey.setValue(TEXT("ProgId"), TEXT("Separatista.MT940SDocument.1")) ||
				!MT940SDocumentKey.setValue(TEXT("VersIndProgId"), TEXT("Separatista.MT940SDocument")))
				hr = E_FAIL;
	}
	else
		hr = E_FAIL;

	if(hr == S_OK)
	{
		RegistryKey MT940SDocumentAppKey(HKEY_CLASSES_ROOT, TEXT("Separatista.MT940SDocument.1"));
		RegistryKey MT940SDocumentIndAppKey(HKEY_CLASSES_ROOT, TEXT("Separatista.MT940SDocument"));

		if(MT940SDocumentAppKey.isOpen() &&
			MT940SDocumentIndAppKey.isOpen())
		{
			if(!MT940SDocumentAppKey.setValue(TEXT("CLSID"), TEXT("{6DF05A76-0582-415a-9B96-163F76914250}")) ||
				!MT940SDocumentAppKey.setValue(TEXT("CurVer"), TEXT("Separatista.MT940SDocument")) ||
				!MT940SDocumentIndAppKey.setValue(TEXT("CLSID"), TEXT("{6DF05A76-0582-415a-9B96-163F76914250}")))
				hr = E_FAIL;
		}
		else
			hr = E_FAIL;
	}

	if(hr != S_OK)
		DllUnregisterServer();
	pTypeLib->Release();
	return hr;
}



