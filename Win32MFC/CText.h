#pragma once
#include"CShape.h"
#include<string>



class CText : public CShape {
public:
	CText(LPCTSTR str, Gdiplus::Color& clr);
public:
	void Push(int x, int y) override;

protected:
	void OnDraw(CDC& dc, const LINE& points) override;

private:
	std::wstring m_text;
};


