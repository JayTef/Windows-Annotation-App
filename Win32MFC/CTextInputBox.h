#pragma once
#include <afxwin.h>
#include "common.h"

class CTextInputBox : public CEdit
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	CMemDC m_realtime_dc;
	CMemDC m_final_dc;
};

