#pragma once
#include "Wnd.h"
#include <d2d1.h>

class CChattingWnd : public CWnd
{
public:
private:
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteTextFormat* m_pWriteTextFormat;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	
public:
	CChattingWnd();
	~CChattingWnd();

	bool Initialize(HWND _hWnd);
	void Cleanup();

	void Update();
	void Render();

	LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};