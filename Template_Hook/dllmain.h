#include "SignalScanner.h"
#include "detours.h"
#include <iostream>

DWORD64 pGetAddress = 0;

typedef __int64 (*CText_ptr)(__int64 rcx, __int64 rdx, __int64 r8);
CText_ptr CText_org;

__int64 __fastcall CText_Hk(__int64 rcx, __int64 rdx, __int64 r8);

const wchar_t* test = L"An Phim Bat Ki";