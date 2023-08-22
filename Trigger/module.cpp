#include "module.h"

DWORD WINAPI GetPID(LPCSTR procName) {
    DWORD pid = 0;
    PROCESSENTRY32 pe;
    HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcSnap, &pe))
    {
        CloseHandle(hProcSnap);
        return 0;
    }

    do
    {
        if (0 == strcmp(pe.szExeFile, procName))
        {
            pid = pe.th32ProcessID;
            CloseHandle(hProcSnap);
            return pid;
        }

    } while (Process32Next(hProcSnap, &pe));

    CloseHandle(hProcSnap);
    return 0;
}

DWORD WINAPI GetModuleAddr(DWORD pid, LPCSTR moduleName)
{
    DWORD addr = 0;
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
        if (0 == strcmp(me.szModule, moduleName))
        {
            addr = (DWORD)me.modBaseAddr;
            CloseHandle(hModuleSnap);
            return addr;
        }

    } while (Module32Next(hModuleSnap, &me));

    CloseHandle(hModuleSnap);
    return 0;
}

DWORD WINAPI GetModule() {
    DWORD addr = 0;

    //addr = (DWORD)(GetModuleHandle(MODULENAME)); //dll
    addr = GetModuleAddr(GetPID(PROCNAME), MODULENAME); //exe

    /*std::ofstream fout;
    fout.open("C:\\Users\\p2282\\source\\repos\\Trigger\\debug.txt", std::ofstream::out | std::ofstream::app);
    fout << addr;*/
    return addr;
}