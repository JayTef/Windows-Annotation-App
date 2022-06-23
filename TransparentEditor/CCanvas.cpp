#include "CCanvas.h"

BEGIN_MESSAGE_MAP(CCanvas, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

CCanvas::CCanvas()
{
	m_MemDC = NULL;
	m_hOldBitmap = NULL;
}

CCanvas::~CCanvas()
{
	if (m_MemDC != NULL)
	{
		HBITMAP bmp = (HBITMAP)::SelectObject(m_MemDC, m_hOldBitmap);
		::DeleteObject(bmp);
		::DeleteDC(m_MemDC);
	}
}


void CCanvas::InitMemDC() 
{
	HDC hdc;
	hdc = ::GetDC(m_hWnd);
  
	this->m_MemDC = ::CreateCompatibleDC(hdc);

	// just use CDC (mfc)
}




int CCanvas::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here


	// Changes an attribute of the specified window.
	// The function also sets a value at the specified offset in the extra window memory.
	SetWindowLongPtrA(this->GetSafeHwnd(), GWL_EXSTYLE, 
		::GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	return 0;
}
