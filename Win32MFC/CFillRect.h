#pragma once
#include"CShape.h"

class CFillRect : public CShape {
public:
	CFillRect(Gdiplus::Color& clr) : CShape(clr) {}
public:
	void Push(int x, int y) override;

protected:
	void OnDraw(CDC& dc, const LINE& points) override;
};