#include "SignalScanner.h"
#include "detours.h"
#include <iostream>

DWORD64 pGetAddress = 0;

typedef int(*cFunction)(int input);

int HookFunction(int input);