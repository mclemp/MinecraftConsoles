#include "stdafx.h"
#include "ClientConstants.h"

const wstring ClientConstants::VERSION_STRING = wstring(L"Minecraft Legacy ") + L"(1.6.4 / TU19)";
// Str1k3r - 4J ways of doing this which bakes in the version number at like 3 different spots
// const wstring ClientConstants::VERSION_STRING = wstring(L"Minecraft Legacy ") + VER_FILEVERSION_STR_W;//+ SharedConstants::VERSION_STRING;