#include <afxwin.h>
#include "CCanvas.h"
#include "CTextInputBox.h"
#include <gdiplus.h>


#pragma comment(lib, "Gdiplus.lib")


class MyApp : public CWinApp
{
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;
private:
	ULONG_PTR m_gdiplusToken;
};



BOOL MyApp::InitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


	CCanvas* pWnd = new CCanvas();
	pWnd->Create(NULL, NULL);
	pWnd->ShowWindow(SW_SHOW);
	this->m_pMainWnd = pWnd;

	CTextInputBox* pChild = new CTextInputBox();
	RECT rc;
	rc.left = 10;
	rc.top = 10;
	rc.right = 100;
	rc.bottom = 100;
	pChild->Create(WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE 
		| ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc, pWnd, 1000);

	return CWinApp::InitInstance();
}



int MyApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}
