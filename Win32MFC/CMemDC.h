#pragma once
#include "CShape.h"


class CMemDC {
public:
	CMemDC();
	virtual ~CMemDC();

public:

	CDC& getCDC() { return this->m_MemDC; }
	HDC& gethDC() { return this->m_MemDC.m_hDC; } 
	int getWidth() { return this->m_width; }
	int getHeight() { return this->m_height; }

	void Init(CDC* pDC, int nwidth, int nheight);

	void copyFrom(CMemDC& dc);

	void UpdateSurface(HWND hWnd);

private:
	CDC m_MemDC;
	HBITMAP m_hbitmap;
	HBITMAP m_hOldBitmap;
	int m_width;
	int m_height;
};


