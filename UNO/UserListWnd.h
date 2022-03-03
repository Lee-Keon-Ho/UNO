#pragma once
#include "Wnd.h"
#include <d2d1.h>

class CUserListWnd : public CWnd
{
public:
private:
	ID2D1HwndRenderTarget* m_pRenderTarget;

public:
	CUserListWnd();
	~CUserListWnd();

	bool Initialize(HWND _hWnd);
	void Cleanup();

	void Update();
	void Render();

	LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};