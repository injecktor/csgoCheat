#include "antiflash.h"

BOOL WINAPI AntiflashThread(HMODULE hModule) {
    DWORD gameModule = GetModule();
    if (gameModule == NULL) {
        return 1;
    }

    for (; !GetAsyncKeyState(VK_NUMPAD3); std::this_thread::sleep_for(std::chrono::milliseconds(10)))
    {
        DWORD localPlayer = ReadMemory<DWORD>(gameModule + dwLocalPlayer);
        if (localPlayer == NULL) continue;

        DWORD flashDuration = ReadMemory<DWORD>(localPlayer + m_flFlashDuration);
        if (flashDuration > 0) {
            WriteMemory<DWORD>(localPlayer + m_flFlashDuration, 0);
        }
    }
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}