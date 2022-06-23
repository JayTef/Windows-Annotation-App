#include "CText.h"



CText::CText(LPCTSTR str, Gdiplus::Color& clr) 
	: CShape(clr) // : initialise member variable
{
	m_text = str;
}



void CText::Push(int x, int y)
{
	if (this->getPointCount() < 2)
	{
		CShape::Push(x, y);
	}
	else 
	{
		this->lastPointUpdate(x, y);
	}
}



void CText::OnDraw(CDC& dc, const LINE& points) 
{

	if (!this->isPointEmpty()) 
	{

		const Gdiplus::PointF& pt1 = points.front();
		const Gdiplus::PointF& pt2 = points.back();

		Gdiplus::FontFamily   fontFamily(L"Arial");
		Gdiplus::Font         font(&fontFamily, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
		Gdiplus::RectF        rectF(min(pt1.X, pt2.X), min(pt1.Y, pt2.Y), abs(pt2.X - pt1.X), abs(pt2.Y - pt1.Y));
		Gdiplus::SolidBrush   solidBrush(this->getColor());

		Gdiplus::Graphics g(dc.m_hDC);
		g.DrawString(m_text.c_str(), -1, &font, rectF, NULL, &solidBrush);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	}
}