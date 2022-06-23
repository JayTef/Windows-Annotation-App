#pragma once
#include <afxwin.h>


class CTextInputBox : public CEdit
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

