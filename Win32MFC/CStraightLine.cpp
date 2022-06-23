#include "CStraightLine.h"



void CStraightLine::Push(int x, int y) {
	if (this->getPointCount() < 2) {
		CShape::Push(x, y);
	}
	else {
		this->lastPointUpdate(x, y);
	}
}


// add  LineCapRound
void CStraightLine::OnDraw(CDC& dc, const LINE& points) {
	if (!this->isPointEmpty()) {
		const Gdiplus::PointF& pt1 = points.front();
		const Gdiplus::PointF& pt2 = points.back();

		Gdiplus::Graphics g(dc.m_hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		g.DrawLine(&m_pen, pt1, pt2);
	}
}