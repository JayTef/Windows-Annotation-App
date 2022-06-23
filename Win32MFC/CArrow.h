#pragma once
#include"CShape.h"



class CArrow : public CShape {
public:
	CArrow(Gdiplus::Color& clr) : CShape(clr) {}
public:
	void Push(int x, int y) override;

protected:
	void OnDraw(CDC& dc, const LINE& points) override; // in h.file to tell compiler
};

