#include "CMemDC.h"


CMemDC::CMemDC()
{
	m_hbitmap = NULL;
	m_hOldBitmap = NULL;
	m_width = 0;
	m_height = 0;
}


CMemDC::~CMemDC()
{
	if (m_hbitmap) {
		::DeleteObject(m_hbitmap);
	}

	if (m_hOldBitmap) {
		m_MemDC.SelectObject(m_hOldBitmap);
	}
}



void CMemDC::Init(CDC* pDC, int nWidth, int nHeight)
{

	this->m_width = nWidth;
	this->m_height = nHeight;
	this->m_MemDC.CreateCompatibleDC(pDC);   


	Gdiplus::Bitmap bmp(m_width, m_height, PixelFormat32bppARGB);
	bmp.GetHBITMAP(Gdiplus::Color::Transparent, &m_hbitmap);


	m_hOldBitmap = (HBITMAP)m_MemDC.SelectObject(m_hbitmap);


	Gdiplus::Graphics g(this->m_MemDC.m_hDC);
	g.Clear(Gdiplus::Color(1, 0, 0, 0));
}



void CMemDC::copyFrom(CMemDC& dc) 
{
	this->m_MemDC.BitBlt(0, 0, m_width, m_height, &dc.getCDC(), 0, 0, SRCCOPY);
}



void CMemDC::UpdateSurface(HWND hWnd) 
{

	RECT rc;
	::GetWindowRect(hWnd ,&rc);
	HDC hdc = ::GetDC(hWnd);

	POINT src_pt;
	src_pt.x = 0;
	src_pt.y = 0;

	POINT pt;
	pt.x = rc.left;
	pt.y = rc.top;

	SIZE sz;
	sz.cx = rc.right - rc.left;
	sz.cy = rc.bottom - rc.top;

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	::UpdateLayeredWindow(hWnd, hdc, &pt, &sz, this->m_MemDC.m_hDC, &src_pt, RGB(0, 0, 0), &bf, ULW_ALPHA); 

	::ReleaseDC(hWnd, hdc);
}