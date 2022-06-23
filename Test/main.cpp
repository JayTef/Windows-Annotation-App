#include <afxwin.h>
#include<sdkddkver.h>
#include<gdiplus.h>
#include<ole2.h>
#pragma comment(lib, "Gdiplus.lib")  


class CMemDC {
public:
	CMemDC()
	{
		m_hbitmap = NULL;
		m_hOldBitmap = NULL;
		m_width = 0;
		m_height = 0;
	}
	virtual ~CMemDC()
	{
		if (m_hbitmap)
		{
			// The DeleteObject function deletes a logical pen, brush, font, bitmap, 
			// region, or palette, freeing all system resources associated with the object.
			::DeleteObject(m_hbitmap);
		}

		if (m_hOldBitmap) 
		{
			// Selects an object into the device context.
			m_MemDC.SelectObject(m_hOldBitmap);
		}
	}

public:

	CDC& getCDC() { return this->m_MemDC; }
	HDC& gethDC() { return this->m_MemDC.m_hDC; }
	int getWidth() { return this->m_width; }
	int getHeight() { return this->m_height; }

	void Init(CDC* pDC, int nWidth, int nHeight)
	{

		this->m_width = nWidth;
		this->m_height = nHeight;

		// Creates a memory device context that is compatible with the device specified by pDC.
		this->m_MemDC.CreateCompatibleDC(pDC);


		// PixelFormat32bppARGB specifies that the format is 32 bits per pixel;
		// 8 bits each are used for the alpha, red, green, and blue components.
		Gdiplus::Bitmap bmp(m_width, m_height, PixelFormat32bppARGB);
		// The method creates a Windows Graphics Device Interface (GDI) bitmap from this Bitmap object.
		bmp.GetHBITMAP(Gdiplus::Color::Transparent, &m_hbitmap);

		// HBITMAP is a handle to a bitmap.
		m_hOldBitmap = (HBITMAP)m_MemDC.SelectObject(m_hbitmap);


		Gdiplus::Graphics g(this->m_MemDC.m_hDC);
		// The method clears a Graphics object to a specified color.
		g.Clear(Gdiplus::Color(128, 255, 0, 0));
	}

	void copyFrom(CMemDC& dc)
	{
		// Copies a bitmap from the source device context to this current device context.
		this->m_MemDC.BitBlt(0, 0, m_width, m_height, &dc.getCDC(), 0, 0, SRCCOPY);
	}

	void  UpdateSurface(HWND hWnd)
	{

		RECT rc;
		// Retrieves the dimensions of the bounding rectangle of the specified window.
		::GetWindowRect(hWnd, &rc);
		HDC hdc = ::GetDC(hWnd);

		POINT src_pt;
		src_pt.x = 0;
		src_pt.y = 0;

		POINT pt;
		pt.x = rc.left;
		pt.y = rc.top;

		SIZE sz;
		sz.cx = rc.right - rc.left;
		sz.cy = rc.bottom - rc.top;

		// The BLENDFUNCTION structure controls blending 
		// by specifying the blending functions for source and destination bitmaps.
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		// Updates the position, size, shape, content, and translucency of a layered window.
		::UpdateLayeredWindow(hWnd, hdc, &pt, &sz, this->m_MemDC.m_hDC, &src_pt, RGB(255, 0, 0), &bf, ULW_ALPHA);

		::ReleaseDC(hWnd, hdc);
	}

private:
	CDC m_MemDC;
	HBITMAP m_hbitmap;
	HBITMAP m_hOldBitmap;
	int m_width;
	int m_height;
};


class CMyEdit : public CEdit
{
public:
	CMyEdit() :
		m_StrFmt(Gdiplus::StringFormat::GenericTypographic()) // : initialise member variable
	{
		m_StrFmt.SetFormatFlags(Gdiplus::StringFormatFlagsMeasureTrailingSpaces);
	}

	virtual ~CMyEdit(){
	}

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	void FitToText();
	void MeasureString(CString& str, Gdiplus::RectF& boundRect);

private:
	CFont m_font;
	LOGFONT m_lf;
	Gdiplus::StringFormat m_StrFmt;

	CMemDC m_dc;
};

class GdiPlusInitialiser {
public:
	GdiPlusInitialiser() {
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	virtual ~GdiPlusInitialiser() {
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
private:
	ULONG_PTR gdiplusToken;
};

class MyApp : public CWinApp
{
public:
	MyApp() {}
	virtual ~MyApp() {}

protected:
	virtual BOOL InitInstance() override
	{
		CFrameWnd* pWnd = new CFrameWnd();
		pWnd->Create(NULL, L"My Program", WS_OVERLAPPEDWINDOW); 
		pWnd->ShowWindow(SW_SHOW);
		this->m_pMainWnd = pWnd;

		CMyEdit* pChild = new CMyEdit();
		RECT rc;
		rc.left = 100;
		rc.top = 100;
		rc.right = 130;
		rc.bottom = 130;
		pChild->Create(WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE
			| ES_WANTRETURN| ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc, pWnd, 100);

		return TRUE;
	}
private:
	GdiPlusInitialiser _gdiPlus_init;
};
MyApp app;

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_UPDATE, &CMyEdit::OnEnUpdate)
END_MESSAGE_MAP()



// the function measures the size of a stringand then draws a rectangle that represents that size
void CMyEdit::MeasureString(CString& str, Gdiplus::RectF& boundRect)
{
	CDC* pDC = this->GetDC();
	Gdiplus::Graphics g(pDC->m_hDC);

	Gdiplus::Font font(L"Arial", 21);
	//Gdiplus::Font font(pDC->m_hDC, &m_lf);
	Gdiplus::RectF layoutRect;

	// use when object is created to practice memory efficient code
	//Gdiplus::StringFormat StrFmt; 
	// The GenericTypographic method creates a generic, typographic StringFormat object.
	//Gdiplus::StringFormat StrFmt = Gdiplus::StringFormat::GenericTypographic();
 
	// SetFormatFlags sets the format flags for this StringFormat object.
	// The StringFormatFlags enumeration specifies text layout information and display manipulations .
	//StrFmt.SetFormatFlags(Gdiplus::StringFormatFlagsMeasureTrailingSpaces); 

	g.MeasureString(str, str.GetLength(), &font, layoutRect, &m_StrFmt, &boundRect);

	this->ReleaseDC(pDC);
}


void CMyEdit::FitToText()
{
	
	// Get text input
	CString str;
	this->GetWindowText(str);

	// Get the starting and ending character positions of the current selection in an edit control
	int start = -1, end = -1;
	this->GetSel(start, end);

	// Replace tab with 5 space bar
	CString new_tab_str = L"     ";
	int tab_len = new_tab_str.GetLength() - 1;
											
	if (str.Replace(L"\t", new_tab_str) == 0)
	{
		// When tab is NOT pressed
		tab_len = 0;
	}

	
	bool removeLastChar = false;
	// IsEmpty is to avoid the situation where (0 - 1 = -1) assertion failure occur
	if (!str.IsEmpty() && str[str.GetLength() - 1] == L'\n')
	{
		// place 'A' at the end 
		str.AppendChar(L'A');
		removeLastChar = true;
	}

	// the method measures the extent of the string in the specified font, format, and layout rectangle.
	Gdiplus::RectF boundRect;
	this->MeasureString(str, boundRect);

	// Remove 'A' after \n is pressed
	if (removeLastChar)
	{
		str.Delete(str.GetLength() - 1, 1); // from the last index to count
	}

	// Displays a prompt in the masked edit control
	this->SetWindowText(str);

	// select a range of characters in an edit control
	this->SetSel(end + tab_len, end + tab_len);

	// Changes the size, position, and Z-order of child, pop-up, and top-level windows.
	this->SetWindowPos(NULL, 0, 0, boundRect.GetRight() - boundRect.GetLeft(), boundRect.GetBottom() - boundRect.GetTop(), SWP_NOMOVE);
	this->LineScroll(this->GetLineCount());
}



void CMyEdit::OnEnUpdate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here

	this->m_dc.copyFrom(this->m_dc);

	this->FitToText();

	m_dc.UpdateSurface(this->m_hWnd);
}




int CMyEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	::SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, 
		::GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);


	// Retrieves the specified system metric or system configuration setting.
    // Note that all dimensions retrieved by GetSystemMetrics are in pixels.
	int ScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
	this->SetWindowPos(&CWnd::wndTopMost, 0, 0, ScreenWidth, ScreenHeight, SWP_FRAMECHANGED);

	CDC* pDC = this->GetDC();
	m_dc.Init(pDC, ScreenWidth, ScreenHeight);
	this->ReleaseDC(pDC);




	memset(&m_lf, 0, sizeof(LOGFONT)); // clear out structure
	m_lf.lfWidth = 13; // 13
	m_lf.lfHeight = 30;
	_tcsncpy_s(m_lf.lfFaceName, LF_FACESIZE, _T("Arial"), 21); // 21 request a face name "Arial"
	m_font.CreateFontIndirect(&m_lf); // create the font

	this->SetFont(&m_font);
	this->GetFont()->GetLogFont(&m_lf); // After dialogue gets basic font information, gives that attribute to log variable																				  
    //CFont* pFont = this->GetFont();
	//pFont->GetLogFont(&m_lf);
	
	return 0;
}