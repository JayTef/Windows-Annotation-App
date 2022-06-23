#pragma once
#include"CShape.h"


class CEllipse : public CShape {
public:
	CEllipse(Gdiplus::Color& clr) : CShape(clr) {}
public:
	void Push(int x, int y) override;

protected:
	void OnDraw(CDC& dc, const LINE& points) override;
};


