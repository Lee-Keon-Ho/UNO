#pragma once
#include "Wnd.h"
#include "Direct.h"

class CGameWnd : public CWnd
{
public:
private:
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pRedBrush;
public:
	CGameWnd();
	~CGameWnd();

	bool Initialize(HWND _hWnd);
	void Cleanup();

	void Update();
	void Render();

	bool LoadBitmapFile();
	ID2D1HwndRenderTarget* GetRT() { return m_pRenderTarget; }

	LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};