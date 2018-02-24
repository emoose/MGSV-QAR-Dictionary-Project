#include "stdafx.h"

//dinput8.dll

typedef HRESULT(*DirectInput8Create_ptr)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter);

DirectInput8Create_ptr DirectInput8Create_orig;

bool origLoaded = false;
HMODULE origDll = NULL;
extern HMODULE ourModule;

bool LoadProxiedDll()
{
	if (origLoaded)
		return true;

	// get the filename of our DLL and try loading the DLL with the same name from system32
	WCHAR modulePath[MAX_PATH] = { 0 };
	if (!GetSystemDirectoryW(modulePath, _countof(modulePath)))
		return false;

	// get filename of this DLL, which should be the original DLLs filename too
	WCHAR ourModulePath[MAX_PATH] = { 0 };
	GetModuleFileNameW(ourModule, ourModulePath, _countof(ourModulePath));

	WCHAR exeName[MAX_PATH] = { 0 };
	WCHAR extName[MAX_PATH] = { 0 };
	_wsplitpath_s(ourModulePath, NULL, NULL, NULL, NULL, exeName, MAX_PATH, extName, MAX_PATH);

	swprintf_s(modulePath, MAX_PATH, L"%ws\\%ws%ws", modulePath, exeName, extName);

	origDll = LoadLibraryW(modulePath);
	if (!origDll)
		return false;

	DirectInput8Create_orig = (DirectInput8Create_ptr)GetProcAddress(origDll, "DirectInput8Create");

	origLoaded = true;
	return true;
}

extern "C" __declspec(dllexport) HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter)
{
	if (!DirectInput8Create_orig)
		LoadProxiedDll();

	return DirectInput8Create_orig(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}
