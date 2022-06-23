#include "CLine.h"


void CLine::OnDraw(CDC& dc, const LINE& points) {
	if (!this->isPointEmpty()) {

		m_pen.SetStartCap(Gdiplus::LineCapRound);
		m_pen.SetEndCap(Gdiplus::LineCapRound);
		Gdiplus::Graphics g(dc.m_hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		g.DrawLines(&m_pen, points.data(), points.size());
	}
}
