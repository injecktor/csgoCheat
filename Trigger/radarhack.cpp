#include "radarhack.h"

BOOL WINAPI RadarThread(HMODULE hModule) {
    DWORD gameModule = GetModule();
    if (gameModule == NULL) {
        return 1;
    }

    for (; !GetAsyncKeyState(VK_NUMPAD4); std::this_thread::sleep_for(std::chrono::milliseconds(10)))
    {
        DWORD localPlayer = ReadMemory<DWORD>(gameModule + dwLocalPlayer);
        if (localPlayer == NULL) continue;

        DWORD glowObjectManager = ReadMemory<DWORD>(gameModule + dwGlowObjectManager);
        DWORD localTeam = ReadMemory<DWORD>(localPlayer + m_iTeamNum);

        for (size_t i = 0; i < 32; i++)
        {
            DWORD target = ReadMemory<DWORD>(gameModule + dwEntityList + i * 0x10);
            if (target == NULL) continue;

            DWORD tHealth = ReadMemory<DWORD>(target + m_iHealth);
            if (tHealth <= 0) continue;

            if (tHealth > 0 && tHealth <= 100)
                WriteMemory<DWORD>(target + m_bSpotted, 1);
        }
    }
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}