#include "wallhack.h"

DWORD rColor = 255;
DWORD gColor = 0;
DWORD bColor = 255;
DWORD aColor = 255;

float rHealth;
float rrColor;
float rgColor;
float rbColor;
float raColor;

bool isWhHp = false;

BOOL WINAPI WallhackThread(HMODULE hModule) {
    DWORD gameModule = GetModule();
    if (gameModule == NULL) {
        return 1;
    }

    for (; !GetAsyncKeyState(VK_NUMPAD2); std::this_thread::sleep_for(std::chrono::milliseconds(5)))
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


            DWORD glowIndex = ReadMemory<DWORD>(target + m_iGlowIndex);

            DWORD tTeam = ReadMemory<DWORD>(target + m_iTeamNum);

            if (localTeam != tTeam) {
                float rHealth = (float)tHealth / 100;
                if (isWhHp) {
                    rrColor = 1.f - rHealth;
                    rgColor = rHealth;
                    rbColor = 0.f;
                    raColor = 1.f;
                }
                else {
                    rrColor = (float)rColor / 255;
                    rgColor = (float)gColor / 255;
                    rbColor = (float)bColor / 255;
                    raColor = (float)aColor / 255;
                }
                WriteMemory<float>(glowObjectManager + glowIndex * 0x38 + 0x8, rrColor); //Red
                WriteMemory<float>(glowObjectManager + glowIndex * 0x38 + 0xC, rgColor); //Green
                WriteMemory<float>(glowObjectManager + glowIndex * 0x38 + 0x10, rbColor); //Blue
                WriteMemory<float>(glowObjectManager + glowIndex * 0x38 + 0x14, raColor); //Alpha
            }
            WriteMemory<bool>(glowObjectManager + glowIndex * 0x38 + 0x28, true);
        }

    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}