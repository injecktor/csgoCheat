#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule,DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TriggerThread, 0, 0, nullptr));
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WallhackThread, 0, 0, nullptr));
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiflashThread, 0, 0, nullptr));
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RadarThread, 0, 0, nullptr));
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

