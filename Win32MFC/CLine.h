#pragma once
#include"CShape.h"



class CLine : public CShape {
public:
	CLine(Gdiplus::Color& clr) : CShape(clr) {}
public:
	void OnDraw(CDC& dc, const LINE& points);
};