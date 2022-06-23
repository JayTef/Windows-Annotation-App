#include "CTextInputBox.h"

BEGIN_MESSAGE_MAP(CTextInputBox, CEdit)
	ON_WM_CREATE()
END_MESSAGE_MAP()




int CTextInputBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
