#pragma once
#include "rwmem.h"

template <typename T>
T ReadMemory(DWORD addr) {
    T buf = T();
    HWND hGameWindow = FindWindow(NULL, WINDOWNAME);
    if (hGameWindow == NULL) {
        return T();
    }
    DWORD pID = NULL;
    GetWindowThreadProcessId(hGameWindow, &pID);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL) {
        return T();
    }
    ReadProcessMemory(processHandle, (LPCVOID)addr, &buf, sizeof(T), NULL);
    CloseHandle(processHandle);
    return buf;
}

template <typename T>
void WriteMemory(DWORD addr, const T buf) {
    HWND hGameWindow = FindWindow(NULL, WINDOWNAME);

    DWORD pID = NULL;
    GetWindowThreadProcessId(hGameWindow, &pID);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

    WriteProcessMemory(processHandle, (LPVOID)addr, &buf, sizeof(T), NULL);
    CloseHandle(processHandle);
}