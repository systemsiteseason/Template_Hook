// dllmain.cpp : Defines the entry point for the DLL application.
#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

    Loop:;
        pGetAddress = FindPattern(NULL, (char*)"\x4C\x8B\xDC\x55\x49\x8D\xAB\x28\xFF\xFF\xFF\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x1F\x88", (char*)"xxxxxxxxxxxxxx????xxxxx");
        if (pGetAddress == -1)
            goto Loop;

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach((PVOID*)(&pGetAddress), CText_Hk);
        DetourTransactionCommit();

        CText_org = (CText_ptr)pGetAddress;

        break;
    case DLL_PROCESS_DETACH:

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(LPVOID&)pGetAddress, &CText_Hk);
        DetourTransactionCommit();

        break;
    }
    return TRUE;
}

__int64 __fastcall CText_Hk(__int64 rcx, __int64 rdx, __int64 r8)
{
    wchar_t* org_text = *(wchar_t**)rdx;

    if (org_text != NULL)
    {
        std::wstring txt(org_text);
        if (txt == L"Press Any Button")
        {
            *(DWORD64*)rdx = (DWORD64)test;
            *(DWORD*)(rdx + 8) = wcslen(test) + 1;
            *(DWORD*)(rdx + 0xC) = wcslen(test) + 4;
        }
    }

    return CText_org(rcx, rdx, r8);
}