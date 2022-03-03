#pragma once
#include "GameWnd.h"
#include "ChattingWnd.h"
#include "UserListWnd.h"

class CUnoWnd : public CWnd
{
public:
private:
	CGameWnd* m_pGameWnd;
	CChattingWnd* m_pChattingWnd;
	CUserListWnd* m_pUserListWnd;

public:
	CUnoWnd();
	~CUnoWnd();

	bool Initialize();
	void Cleanup();

	void Update();
	void Render();

	LRESULT MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
private:
};