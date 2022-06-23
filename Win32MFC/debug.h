#pragma once
#include"wincommon.h"


#ifdef _UNICODE
#define __W(x) L ##x
#define _W(x) __W(x)
#define VSPRINTF vsprintf_s
#else
#define VSPRINTF vsprintf_s
#define __W(x)   ##x
#define _W(x) __W(x)
#endif

#ifdef _DEBUG
#define LOG(fmt, ...) DebugMsg(_W("%s(%d):") fmt,_T(__FUNCTION__),__LINE__,__VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif


void DebugMsg(LPCTSTR format, ...);