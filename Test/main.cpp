#include "includes.h"

int main() {
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TriggerThread, 0, 0, nullptr));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WallhackThread, 0, 0, nullptr));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiflashThread, 0, 0, nullptr));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RadarThread, 0, 0, nullptr));
	while (true) Sleep(1000);
	return 0;
}