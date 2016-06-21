#pragma once

#include <string>

#ifdef _WIN32
#ifdef HOENGINE_EXPORT
#define HO_API __declspec(dllexport)
#else
#define HO_API
#endif
#endif

#ifndef _DEBUG
#define _DEBUG 1
#endif

#if _DEBUG
#include "debug/debug.h"
#endif
#define _LEAK_DETECTION 1
#if _LEAK_DETECTION
#include <vld.h>
#endif

typedef unsigned int uint;
typedef unsigned char byte;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned short ushort;