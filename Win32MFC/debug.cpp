#include"debug.h"

void DebugMsg(LPCTSTR format, ...) {

	TCHAR buf[1024 + 1] = { 0, };
	va_list vl;
	va_start(vl, format);
	vswprintf_s(buf, 1024, format, vl);
	va_end(vl);
	OutputDebugString(buf);
}