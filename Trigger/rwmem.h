#pragma once
#include "include.h"

#include "rwmem.cpp"

template <typename T>
T ReadMemory(DWORD addr);

template <typename T>
void WriteMemory(DWORD addr, const T buf);