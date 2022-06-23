#include "CArrow.h"



void CArrow::Push(int x, int y) {
	if (this->getPointCount() < 2) {
		CShape::Push(x, y);
	}
	else {
		this->lastPointUpdate(x, y);
	}
}



void CArrow::OnDraw(CDC& dc, const LINE& points) {
	if (!this->isPointEmpty()) {
		const Gdiplus::PointF& pt1 = points.front();
		const Gdiplus::PointF& pt2 = points.back();


		Gdiplus::AdjustableArrowCap myArrow(5, 5, true);
		myArrow.SetMiddleInset(1.5);
		m_pen.SetCustomEndCap(&myArrow);

		Gdiplus::Graphics g(dc.m_hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		g.DrawLine(&m_pen, pt1, pt2);
	}
}
