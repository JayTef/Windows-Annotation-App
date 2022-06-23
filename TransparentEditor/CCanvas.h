#pragma once
#include <afxwin.h>



class CCanvas : public CFrameWnd
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitMemDC();

private:
	HDC m_MemDC;
	HBITMAP m_hbitmap;
	HBITMAP m_hOldBitmap;
	int m_width;
	int m_height;
};

