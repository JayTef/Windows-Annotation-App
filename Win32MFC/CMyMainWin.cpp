#include "CMyMainWin.h"
#include "CLine.h"
#include "CStraightLine.h"
#include "CArrow.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CRightTriangle.h"
#include "CTriangle.h"
#include "CText.h"
#include "customWinMessage.h"


BEGIN_MESSAGE_MAP(CMyMainWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_MESSAGE(WS_USER_END_EDIT, &CMyMainWin::OnWsUserEndEdit)
END_MESSAGE_MAP()



int CMyMainWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	::SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	int ScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	this->SetWindowPos(&CWnd::wndTopMost, 0, 0, ScreenWidth, ScreenHeight, SWP_FRAMECHANGED);

	CDC* pDC = this->GetDC();

	m_realtime_dc.Init(pDC, ScreenWidth, ScreenHeight);
	m_final_dc.Init(pDC, ScreenWidth, ScreenHeight);

	this->ReleaseDC(pDC);


	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = 300;
	rc.bottom = 100;
	m_inputBox.Create(ES_MULTILINE | WS_BORDER | WS_CHILD, rc, this, 100);
	m_inputBox.ShowWindow(SW_HIDE);


	m_final_dc.UpdateSurface(this->m_hWnd);

	return 0;

}



void CMyMainWin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CFrameWnd::OnPaint() for painting messages

	//this->m_final_dc.copyTo(&dc);   //

}


CMyMainWin::CMyMainWin()
{
	isDown = false;
	m_color = Gdiplus::Color::White;
	m_option = 0;
}



CMyMainWin::~CMyMainWin() 
{
	for (size_t i = 0; i < m_shapes.size(); i++) {
		delete m_shapes[i];   
	}
}



void CMyMainWin::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	this->m_msg.Format(L"Move(%d,%d)\n", point.x, point.y);
	this->SetWindowText(this->m_msg);

	if (isDown) {

		this->m_realtime_dc.copyFrom(this->m_final_dc);   

		CShape& line = *m_shapes.back();
		line.Push(point.x, point.y);
		line.Draw(m_realtime_dc.getCDC());   


		m_realtime_dc.UpdateSurface(this->m_hWnd);
	}

	CFrameWnd::OnMouseMove(nFlags, point);
}



void CMyMainWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	this->m_msg.Format(L"LeftDown(%d,%d)\n", point.x, point.y);
	this->SetWindowText(this->m_msg);


	if (m_option == 7)
	{
		POINT pt;
		::GetCursorPos(&pt);
		::ScreenToClient(this->m_hWnd, &pt);
		m_inputBox.SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE);
		m_inputBox.ShowWindow(SW_SHOW);
	}
	else
	{
		switch (m_option)
		{
		case 1:
			m_shapes.push_back(new CStraightLine(m_color));   // new? 
			break;
		case 2:
			m_shapes.push_back(new CArrow(m_color));
			break;
		case 3:
			m_shapes.push_back(new CRectangle(m_color));
			break;
		case 4:
			m_shapes.push_back(new CEllipse(m_color));
			break;
		case 5:
			m_shapes.push_back(new CRightTriangle(m_color));
			break;
		case 6:
			m_shapes.push_back(new CTriangle(m_color));
			break;
		case 192:
			break;
		default:
			m_shapes.push_back(new CLine(m_color));
			break;
		}

		CShape& line = *m_shapes.back();
		line.Push(point.x, point.y);
		
		isDown = true;
	}


	CFrameWnd::OnLButtonDown(nFlags, point);
}



void CMyMainWin::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	this->m_msg.Format(L"LeftUp(%d,%d)\n", point.x, point.y);
	this->SetWindowText(this->m_msg);

	if (isDown) {

		CShape& line = *m_shapes.back();
		line.Push(point.x, point.y);
		isDown = false;

		m_final_dc.copyFrom(this->m_realtime_dc);   
		m_final_dc.UpdateSurface(this->m_hWnd);

	}

	CFrameWnd::OnLButtonUp(nFlags, point);
}



void CMyMainWin::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	this->m_msg.Format(L"OnKeyDown(%d)\n", nChar);
	this->SetWindowText(this->m_msg);

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CMyMainWin::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	this->m_msg.Format(L"OnKeyUp(%d)\n", nChar);
	this->SetWindowText(this->m_msg);

	switch (nChar)
	{
	case 82:
		m_color = Gdiplus::Color::Red;
		break;
	case 71:
		m_color = Gdiplus::Color::Green;
		break;
	case 66:
		m_color = Gdiplus::Color::Blue;
		break;
	case 83:
		m_color = Gdiplus::Color::SkyBlue;
		break;
	case 79:
		m_color = Gdiplus::Color::DarkOrange;
		break;
	case 80:
		m_color = Gdiplus::Color::HotPink;
		break;
	case 49:
		m_option = 1;
		break;
	case 50:
		m_option = 2;
		break;
	case 51:
	    m_option = 3;
		break;
	case 52:
		m_option = 4;
		break;
	case 53:
		m_option = 5;
		break;
	case 54:
		m_option = 6;
		break;
	case 55:
		m_option = 7;
		break;
	case 192:
		m_option = 192;
		break;
	default:
		m_color = Gdiplus::Color::White;
		m_option = 0;
		break;
	}

	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}



afx_msg LRESULT CMyMainWin::OnWsUserEndEdit(WPARAM wParam, LPARAM lParam) // added function
{
	RECT rc;
	CString str;
	this->m_inputBox.GetWindowText(str);
	this->m_inputBox.GetWindowRect(&rc); // Coordinates from entire Screen


	POINT pt1, pt2;
	pt1.x = rc.left;
	pt1.y = rc.top;
	::ScreenToClient(this->m_hWnd, &pt1); // Screen base to Client area base      :: -> global
	pt2.x = rc.right;
	pt2.y = rc.bottom;
	::ScreenToClient(this->m_hWnd, &pt2); // Screen base to Client area base      :: -> global


	m_shapes.push_back(new CText(str, m_color));
	CShape& txt = *m_shapes.back();
	txt.Push(pt1.x, pt1.y);
	txt.Push(pt2.x, pt2.y);


	this->m_realtime_dc.copyFrom(this->m_final_dc);   
	txt.Draw(m_realtime_dc.getCDC());  


	this->m_final_dc.copyFrom(this->m_realtime_dc);   
	m_final_dc.UpdateSurface(this->m_hWnd);


	m_color = Gdiplus::Color::White;
	m_option = 0;

	return 0;
}