#include "CTextInputBox.h"
#include "customWinMessage.h"
#include "common.h"




BEGIN_MESSAGE_MAP(CTextInputBox, CEdit)
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



void CTextInputBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_ESCAPE:
		this->GetParent()->SendMessage(WS_USER_END_EDIT);
		this->ShowWindow(SW_HIDE);
		break;
	}

	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}



int CTextInputBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	RECT rc;
	this->GetWindowRect(&rc);

	::SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, 
		::GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	int nWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int nHeight = ::GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(&CWnd::wndTopMost, 0, 0, nWidth, nHeight, SWP_FRAMECHANGED);

	CDC* pDC = this->GetDC();
	m_realtime_dc.Init(pDC, nWidth, nHeight);
	m_final_dc.Init(pDC, nWidth, nHeight);
	this->ReleaseDC(pDC);

	return 0;
}



void CTextInputBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default


	// windows8-aware in the manifest
	LOG("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");


	// one m_dc
	this->m_realtime_dc.copyFrom(this->m_final_dc);


	CDC* pDC = this->GetDC();
	Gdiplus::Graphics g(pDC->m_hDC);
	Gdiplus::Pen pen(Gdiplus::Color::OrangeRed);
	Gdiplus::RectF rc(0, 0, 300, 300);
	g.DrawRectangle(&pen, rc);
	this->ReleaseDC(pDC);


	m_final_dc.UpdateSurface(this->m_hWnd);

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
