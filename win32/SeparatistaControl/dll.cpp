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
#include "dispatch.cpp"

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
	if(IsEqualIID(rclsid, __uuidof(CMT940SDocument)))
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

/**
	Unregister a COM object by clearing all the registry values
	@param lpCLSID CLSID in { } form
	@param lpProgID ProgID like Toolkit.Object.Version
	@param VersIndProgID Version independent ProgID like Toolkit.Object
*/

void DllUnregisterObject(LPCTSTR lpCLSID, LPCTSTR lpProgID, LPCTSTR lpVersIndProgID)
{
	// Open the classes root key
	RegistryKey classesKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Classes"));
	if(!classesKey.isOpen())
		return;

	// Remove ProdID and VersionIndependentProgID
	classesKey.DeleteTree(lpProgID);
	classesKey.DeleteTree(lpVersIndProgID);

	// Open the CLSID subkey
	RegistryKey clsidKey(classesKey, TEXT("CLSID"));
	if(!clsidKey.isOpen())
		return;

	// Remove the CLSID key
	clsidKey.DeleteTree(lpCLSID);
}

STDAPI DllUnregisterServer()
{
	// Self unregister typelib
	UnRegisterTypeLib(__uuidof(ISepaControlTypeLib), 1, 0, 0, SYS_WIN32);

	// Unregister Separatista.MT940SDocument
	DllUnregisterObject(
		TEXT("{6DF05A76-0582-415a-9B96-163F76914250}"),
		TEXT("Separatista.MT940SDocument.1"),
		TEXT("Separatista.MT940SDocument"));
	
	// Unregister Separatista.MT940SRecord
	DllUnregisterObject(
		TEXT("{343F637E-DA0B-43a4-A802-8F9EF2DCC5DF}"),
		TEXT("Separatista.MT940SRecordset.1"),
		TEXT("Separatista.MT940SRecordset"));

	// Unregister Separatista.IBAN
	DllUnregisterObject(
		TEXT("{6DF05A76-0582-415a-9B96-163F76914250}"),
		TEXT("Separatista.MT940SDocument.1"),
		TEXT("Separatista.MT940SDocument"));

	return S_OK;
}

/**
	Register a COM object by setting all the registry values
	@param lpCLSID CLSID in { } form
	@param lpProgID ProgID like Toolkit.Object.Version
	@param VersIndProgID Version independent ProgID like Toolkit.Object
	@return S_OK on success, SELFREG_E_CLASS on error
*/

HRESULT DllRegisterObject(LPCTSTR lpCLSID, LPCTSTR lpProgID, LPCTSTR lpVersIndProgID)
{
	// Open the classes root key
	RegistryKey classesKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Classes"));
	if(!classesKey.isOpen())
		return SELFREG_E_CLASS;

	// Open root clsid key first
	RegistryKey rootKey(classesKey, TEXT("CLSID"));
	if(!rootKey.isOpen())
		return SELFREG_E_CLASS;

	// Create the clsid subkey
	RegistryKey clsidKey(rootKey, lpCLSID);
	if(!clsidKey.isOpen())
		return SELFREG_E_CLASS;
	if(!clsidKey.setValue(lpVersIndProgID))
		return SELFREG_E_CLASS;

	// Set subkeyvalues on the clsid subkey
	// InprocServer32
	RegistryKey inprocKey(clsidKey, TEXT("InprocServer32"));
	if(!inprocKey.isOpen())
		return SELFREG_E_CLASS;
	if(!inprocKey.setValue(g_lpszDllPath))
		return SELFREG_E_CLASS;
	if(!inprocKey.setValue(TEXT("ThreadingModel"), TEXT("Apartment")))
		return SELFREG_E_CLASS;
	
	// ProgID
	RegistryKey progIDKey(clsidKey, TEXT("ProgID"));
	if(!progIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!progIDKey.setValue(lpProgID))
		return SELFREG_E_CLASS;

	// VersionIndependentProgID
	RegistryKey vidProgIDKey(clsidKey, TEXT("VersionIndependentProgID"));
	if(!vidProgIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!vidProgIDKey.setValue(lpVersIndProgID))
		return SELFREG_E_CLASS;

	// Create the classes ProgID key
	RegistryKey classesProgIDKey(classesKey, lpProgID);
	if(!classesProgIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!classesProgIDKey.setValue(lpVersIndProgID))
		return SELFREG_E_CLASS;

	// Classes ProgID CLSID
	RegistryKey classesCLSIDKey(classesProgIDKey, TEXT("CLSID"));
	if(!classesCLSIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!classesCLSIDKey.setValue(lpCLSID))
		return SELFREG_E_CLASS;

	// Classes ProgID CurVer
	RegistryKey classesCurVerKey(classesProgIDKey, TEXT("CurVer"));
	if(!classesCurVerKey.isOpen())
		return SELFREG_E_CLASS;
	if(!classesCurVerKey.setValue(lpVersIndProgID))
		return SELFREG_E_CLASS;

	// Create the classes VersionIndependentProgID key
	RegistryKey classesVidProgIDKey(classesKey, lpVersIndProgID);
	if(!classesVidProgIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!classesVidProgIDKey.setValue(lpVersIndProgID))
		return SELFREG_E_CLASS;

	// VersionIndependentProgID CLSID
	RegistryKey classesVidCLSIDKey(classesVidProgIDKey, TEXT("CLSID"));
	if(!classesVidCLSIDKey.isOpen())
		return SELFREG_E_CLASS;
	if(!classesVidCLSIDKey.setValue(lpCLSID))
		return SELFREG_E_CLASS;

	return S_OK;
}

STDAPI DllRegisterServer()
{
	HRESULT hr = S_OK;
	ITypeLib* pTypeLib;
	
	// Check dll path
	if(!g_lpszDllPath)
		return SELFREG_E_TYPELIB;

	// Try to self register typelib
	hr = LoadTypeLibEx(g_lpszDllPath, REGKIND_REGISTER, &pTypeLib);
	if(FAILED(hr))
		return SELFREG_E_TYPELIB;

	// Free the typelib
	pTypeLib->Release();

	// Try to register Separatista.MT940SDocument
	hr = DllRegisterObject(
		TEXT("{6DF05A76-0582-415a-9B96-163F76914250}"),
		TEXT("Separatista.MT940SDocument.1"),
		TEXT("Separatista.MT940SDocument"));
	if(FAILED(hr))
	{
		DllUnregisterServer();
		return hr;
	}

	// Try to register Separatista.MT940SRecordset
	hr = DllRegisterObject(
		TEXT("{343F637E-DA0B-43a4-A802-8F9EF2DCC5DF}"),
		TEXT("Separatista.MT940SRecordset.1"),
		TEXT("Separatista.MT940SRecordset"));
	if(FAILED(hr))
	{
		DllUnregisterServer();
		return hr;
	}

	// Try to register Separatista.IBAN
	hr = DllRegisterObject(
		TEXT("{2BD7342E-B12D-45b0-A5D6-ADF118386112}"),
		TEXT("Separatista.IBAN.1"),
		TEXT("Separatista.IBAN"));
	if(FAILED(hr))
	{
		DllUnregisterServer();
		return hr;
	}

	return hr;
}



