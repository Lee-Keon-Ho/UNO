#include "UserListWnd.h"
#include "ResourceManager.h"

CUserListWnd::CUserListWnd()
{
}

CUserListWnd::~CUserListWnd()
{
}

bool CUserListWnd::Initialize(HWND _hWnd)
{
	HRESULT hr;
	RECT rc;
	GetClientRect(_hWnd, &rc);
	int iBoundaryW = rc.right / 6;
	if (!CWnd::Initialize(0 , 0, iBoundaryW, rc.bottom, _hWnd, L"UserListWnd"))
		return false;

	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	// RenderTarget
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	GetClientRect(m_hWnd, &rc);
	hr = CDirect::GetInstance()->GetD2DFactory()->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(rc.right, rc.bottom)),
		&m_pRenderTarget);
	if (FAILED(hr)) return false;
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

	return true;
}

void CUserListWnd::Cleanup()
{
}

void CUserListWnd::Update()
{
}

void CUserListWnd::Render()
{
}

LRESULT CUserListWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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