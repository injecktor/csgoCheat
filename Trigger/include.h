#pragma once
#include <windows.h>
#include <WtsApi32.h>
#include <TlHelp32.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

#include "offsets.h"

#define PROCNAME "csgo.exe"
#define MODULENAME "client.dll"
#define WINDOWNAME "Counter-Strike: GLobal Offensive - Direct3D 9"

using namespace offset::netvars;
using namespace offset::signatures;