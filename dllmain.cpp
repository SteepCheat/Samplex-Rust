#include <Windows.h>
#include "Hooks/Hooks.hpp"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD callReason, LPVOID lpReserved )
{
    if (callReason == DLL_PROCESS_ATTACH)
		Hooks::init();
	
    return TRUE;
}