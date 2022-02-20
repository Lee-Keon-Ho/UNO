#pragma once
#include <Windows.h>

class CWnd
{
public:
protected:
	HWND m_hWnd;
public:
	CWnd();
	~CWnd();

	bool Initialize(LPCWSTR _windowClass, LPCWSTR _title, int _width, int _height, int _nCmdShow);
	void Cleanup();

	virtual LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};