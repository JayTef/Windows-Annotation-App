#pragma once
#include"wincommon.h"
#include"common.h"

class GdiPlusInitialiser {
public:
	GdiPlusInitialiser() {
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	virtual ~GdiPlusInitialiser() {
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
private:
	ULONG_PTR gdiplusToken;
};



