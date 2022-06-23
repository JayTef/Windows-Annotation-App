#include "CTriangle.h"


void CTriangle::Push(int x, int y) {
	if (this->getPointCount() < 2) {
		CShape::Push(x, y);
	}
	else {
		this->lastPointUpdate(x, y);
	}
}


void CTriangle::OnDraw(CDC& dc, const LINE& points) {

	if (!this->isPointEmpty()) {

		const Gdiplus::PointF& pt1 = points.front();
		const Gdiplus::PointF& pt2 = points.back();

		Gdiplus::Graphics g(dc.m_hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

		Gdiplus::PointF point1((pt1.X + pt2.X) / 2, pt1.Y);
		Gdiplus::PointF point2(pt2.X, pt2.Y);
		Gdiplus::PointF point3(pt1.X, pt2.Y);
		Gdiplus::PointF points[] = { point1, point2, point3 };
		Gdiplus::PointF* pPoints = points;

		g.DrawPolygon(&m_pen, pPoints, 3);
	}
}

