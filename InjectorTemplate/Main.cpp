/*
The base of this code is from InjectorTemplate by Junior_Djjr - MixMods.com.br
*/
#include "stdafx.h"
#include "IniReader/IniReader.h"
#include "ReadIniCustom.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"
#include "PatchStuff.h"
#include "GameStuff.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace injector;
using namespace std;

string const projectName = TARGET_NAME; // Set the name on your project properties
int const BUILD_NUMBER = 1;

enum gameVersion
{
	VERSION_UNKNOWN,
	VERSION_A
};
gameVersion version;

gameVersion GetGameVersion()
{
	switch (injector::ReadMemory<uint32_t>(0xDEADC0DE, true))
	{
	case 0x12345678:
		//MessageBoxA(0, "VERSION_A", "Game version", 0);
		return VERSION_A;
	default:
		//MessageBoxA(0, "VERSION_UNKNOWN", "Game version", 0);
		return VERSION_UNKNOWN;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		version = GetGameVersion();
		if (version != VERSION_UNKNOWN) Init();
		else MessageBoxA(0, "Incompatible game version.", "Error", 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

fstream lg;

///////////////////////////////////////////////////////////////////////////////////////////////////

uintptr_t gameProcessingOriginalCall;

void GameProcessing()
{
	lg << "Game processing." << endl;
	lg.flush();

	SimpleCall(gameProcessingOriginalCall);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void ReadIni()
{
	int i;
	float f;

	CIniReader ini(projectName + ".ini");
	if (ini.data.size() <= 0) { lg << projectName << ".ini NOT FOUND\n"; lg.flush(); return; }

	if (ReadIniInt(ini, &lg, "Settings", "ExampleInt", &i)) {
		WriteMemory<uint32_t>(0xDEADC0DE, i, true);
	}
	
	lg.flush();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Init()
{
	lg.open(projectName + ".log", std::fstream::out | std::fstream::trunc);
	lg << "Build " << BUILD_NUMBER << endl;
	lg.flush();

	uintptr_t address;
	switch (version)
	{
	case VERSION_A:
		address = 0xDEADC0DE;
		break;
	default:
		return;
	}
	SimpleHookCallStoreOriginal(address, GameProcessing, &gameProcessingOriginalCall);

	ReadIni();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
