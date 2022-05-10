#pragma once
#include "Wnd.h"
#include "Direct.h"

class CGameWnd : public CWnd
{
public:
private:
	ID2D1HwndRenderTarget* m_pRenderTarget;
	wchar_t m_wchar[4];
public:
	CGameWnd();
	~CGameWnd();

	bool Initialize();
	void Cleanup();

	void Update();
	void Render();

	bool LoadBitmapFile();
	ID2D1HwndRenderTarget* GetRT() { return m_pRenderTarget; }

	bool OnImeComposition(HWND _hWnd, LPARAM _lParam);

	LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};