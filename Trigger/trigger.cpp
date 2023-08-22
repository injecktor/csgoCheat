#include "trigger.h"

BOOL WINAPI TriggerThread(HMODULE hModule) {
    DWORD gameModule = GetModule();
    if (gameModule == NULL) {
        return 1;
    }

    for (; !GetAsyncKeyState(VK_NUMPAD1); std::this_thread::sleep_for(std::chrono::milliseconds(10)))
    {
        DWORD localPlayer = ReadMemory<DWORD>(gameModule + dwLocalPlayer);
        if (localPlayer == NULL) continue;

        DWORD localTeam = ReadMemory<DWORD>(localPlayer + m_iTeamNum);
        DWORD targetId = ReadMemory<DWORD>(localPlayer + m_iCrosshairId);


        if (targetId <= 0 || targetId >= 32) continue;

        DWORD target = ReadMemory<DWORD>(gameModule + dwEntityList + (targetId - 1) * 0x10);
        if (target == NULL) continue;

        DWORD tHealth = ReadMemory<DWORD>(target + m_iHealth);
        if (tHealth <= 0) continue;

        DWORD tTeam = ReadMemory<DWORD>(target + m_iTeamNum);

        if (localTeam != tTeam) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}