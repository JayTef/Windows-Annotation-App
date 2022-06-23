#pragma once
#include <vector>
#include "wincommon.h"
#include "common.h"


typedef std::vector<Gdiplus::PointF> LINE;


class CShape
{
public:
	CShape(Gdiplus::Color& clr) :
		m_clr(clr),
		m_pen(clr, 5)
	{
	}

	virtual ~CShape() {}

public:

	inline const Gdiplus::Color& getColor() const
	{   
		return m_clr;
	}

	inline size_t getPointCount() const  // inline, const
	{   
		return m_points.size();
	}

	inline bool isPointEmpty() const 
	{
		return m_points.empty();
	}

	inline void lastPointUpdate(int x, int y) 
	{
		Gdiplus::PointF& pt = m_points.back();
		pt.X = (Gdiplus::REAL)x;
		pt.Y = (Gdiplus::REAL)y;
	}

	void Draw(CDC& dc) 
	{
		this->OnDraw(dc, m_points);
	}
public:

	virtual void Push(int x, int y) 
	{
		m_points.emplace_back((Gdiplus::REAL)x, (Gdiplus::REAL)y);
	}

	virtual void OnDraw(CDC& dc, const LINE& points) = 0;   // 0

protected:
	Gdiplus::Pen m_pen;
	Gdiplus::Color m_clr;

private:
	LINE m_points;
};