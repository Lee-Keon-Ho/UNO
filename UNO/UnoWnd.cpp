#include "UnoWnd.h"
#include "SceneManager.h"

#define WINDOW_WIDTH 728
#define WINDOW_HEIGHT 389

CUnoWnd::CUnoWnd()
{
	m_pGameWnd = new CGameWnd();
	m_pChattingWnd = new CChattingWnd();
	m_pUserListWnd = new CUserListWnd();
}

CUnoWnd::~CUnoWnd()
{
	Cleanup();
}

bool CUnoWnd::Initialize()
{
	if (!CWnd::Initialize(L"Uno", L"Uno", WINDOW_WIDTH, WINDOW_HEIGHT, SW_SHOW)) return false;
	if (!m_pUserListWnd->Initialize(m_hWnd)) return false;
	if (!m_pGameWnd->Initialize(m_hWnd)) return false;
	if (!m_pChattingWnd->Initialize(m_hWnd)) return false;
	return true;
}

void CUnoWnd::Cleanup()
{
	if (m_pChattingWnd) { delete m_pChattingWnd; m_pChattingWnd = nullptr; }
	if (m_pGameWnd) { delete m_pGameWnd; m_pGameWnd = nullptr; }
	if (m_pUserListWnd) { delete m_pUserListWnd; m_pUserListWnd = nullptr; }
}

void CUnoWnd::Update()
{
	m_pGameWnd->Update();
	m_pChattingWnd->Update();
}

void CUnoWnd::Render()
{
	m_pGameWnd->Render();
	m_pChattingWnd->Render();
}

LRESULT CUnoWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}