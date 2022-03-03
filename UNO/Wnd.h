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
	bool Initialize(int _iSx, int _iSy, int _iWidth, int _iHeight,
		HWND _hParent, LPCTSTR _szClassName);
	void Cleanup();

	virtual LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};