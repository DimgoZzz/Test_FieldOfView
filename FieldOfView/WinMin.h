#pragma once
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <string>
#include <iostream>
#include "HighResClock.h"

inline void CritErr(std::string str)
{
    MessageBoxA(NULL, str.c_str(), "Critical Error", MB_ICONERROR);
    exit(-1);
}