#include "CFillRect.h"


void CFillRect::Push(int x, int y) {
	if (this->getPointCount() < 2) {
		CShape::Push(x, y);
	}
	else {
		this->lastPointUpdate(x, y);
	}
}


void CFillRect::OnDraw(CDC& dc, const LINE& points) {

	if (!this->isPointEmpty()) {

		const Gdiplus::PointF& pt1 = points.front();
		const Gdiplus::PointF& pt2 = points.back();

		Gdiplus::Graphics g(dc.m_hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		g.DrawRectangle(&m_pen, min(pt1.X, pt2.X), min(pt1.Y, pt2.Y), abs(pt2.X - pt1.X), abs(pt2.Y - pt1.Y));
	}
}


