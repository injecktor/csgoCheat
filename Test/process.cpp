/*#include "includes.h"

DWORD GetPID(LPCWSTR procName) {
    DWORD pid = 0;
    WTS_PROCESS_INFOW* pProcessInfo;
    DWORD               NumProcesses;

    if (NULL == WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE,
        0, // Reserved.
        1, // Version,
        &pProcessInfo,
        &NumProcesses))
    {
        printf("WTSEnumerateProcesses failed with last error %lu.\r\n", GetLastError());
        return 0;
    }

    for (DWORD i = 0; i < NumProcesses; ++i)
    {
        if (0 == lstrcmp(pProcessInfo[i].pProcessName, procName))
        {
            pid = pProcessInfo[i].ProcessId;
        }
    }
    WTSFreeMemory(pProcessInfo);
    return pid;
}

DWORD GetModuleAddr(DWORD pid, LPCWSTR moduleName)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    me.dwSize = sizeof(MODULEENTRY32);
    if (!Module32First(hModuleSnap, &me))
    {
        CloseHandle(hModuleSnap);
        return 0;
    }

    do
    {
        if (0 == lstrcmp(me.szModule, moduleName))
        {
            return (DWORD)me.modBaseAddr;
        }

    } while (Module32Next(hModuleSnap, &me));

    CloseHandle(hModuleSnap);
    return 0;
}*/