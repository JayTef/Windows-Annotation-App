#pragma once
#include "CShape.h"
#include "common.h"
#include "CTextInputBox.h"



class CMyMainWin : public CFrameWnd {
public:
	CMyMainWin();
	virtual ~CMyMainWin();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnWsUserEndEdit(WPARAM wParam, LPARAM lParam);

private:
	std::vector<CShape*> m_shapes;
	bool isDown;
	Gdiplus::Color m_color;
	int m_option;
	CString m_msg;

	CMemDC m_realtime_dc;
	CMemDC m_final_dc;

	CTextInputBox m_inputBox;
};