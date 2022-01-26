#pragma once

#pragma warning(disable:4996)//CRTNOWARNINGS

#include <Windows.h>
#include <string>
#include <map>
#include <TlHelp32.h>
#include <array>

#include "Dependencies/ReturnSpoofer/ReturnSpoofer.h"
#include "Dependencies/Encrypt/lazy_importer.hpp"
#include "Dependencies/Encrypt/xorstr.hpp"
#include "Dependencies/SDK/il2cpp.hpp"
#include "Dependencies/SDK/unity.hpp"
#include "Dependencies/SDK/classes.hpp"
#include "Dependencies/SDK/math.hpp"
#include "Dependencies/config.hpp"
#include "Features/Aimbot/aimbot.hpp"
#include "Features/Miscellaneous/miscellaneous.hpp"
#include "Features/Lua/luaenv.hpp"

//common used throughout project
#define _(str) xorstr(str).crypt_get()
#define ePtr(Ptr) M::ptrEnc(Ptr)//Never got around to doing this
BasePlayer* localPlayer;

#ifdef _DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif
//I want to kill myself -notSam 10/18/2021