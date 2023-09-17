// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        pGetAddress = FindPattern((char *)"unknown.exe", (char*)"\x55\x8B\xEC\x8B\x45\x08\x03\x45\x0C", (char*)"xxxxxxxxx");

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(LPVOID&)pGetAddress, &HookFunction);
        DetourTransactionCommit();

        break;
    case DLL_PROCESS_DETACH:

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(LPVOID&)pGetAddress, &HookFunction);
        DetourTransactionCommit();

        break;
    }
    return TRUE;
}

int HookFunction(int input)
{
    cFunction res = (cFunction)pGetAddress;
    return res(input);
}