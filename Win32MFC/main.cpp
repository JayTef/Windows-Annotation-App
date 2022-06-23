#include "wincommon.h"
#include "GdiPlusInitialiser.h"
#include "CMyMainWin.h"



#pragma comment(lib, "Gdiplus.lib")   // only in win32 MVS environment



class MyApp : public CWinApp
{
public:
	MyApp() {}
	virtual ~MyApp() {}
protected:
	virtual BOOL InitInstance() override
	{
		CMyMainWin* pWnd = new CMyMainWin();
		pWnd->Create(NULL, L"My Program", WS_POPUP); // L"EDIT"
		pWnd->ShowWindow(SW_SHOW);
		this->m_pMainWnd = pWnd;
		return TRUE;
	}
private:
	GdiPlusInitialiser _gdiPlus_init;
};

MyApp app;