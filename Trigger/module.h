#pragma once
#include "include.h"

DWORD WINAPI GetPID(LPCSTR procName);
DWORD WINAPI GetModuleAddr(DWORD pid, LPCSTR moduleName);
DWORD WINAPI GetModule();