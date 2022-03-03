#include "ChattingWnd.h"
#include "ResourceManager.h"

CChattingWnd::CChattingWnd() :
	m_pRenderTarget(nullptr), m_pWriteTextFormat(nullptr), 
	m_pWhiteBrush(nullptr)
{
}

CChattingWnd::~CChattingWnd()
{
}

bool CChattingWnd::Initialize(HWND _hWnd)
{
	HRESULT hr;
	RECT rc;
	GetClientRect(_hWnd, &rc);
	int iBoundaryS = rc.right / 6 * 4;
	int iBoundaryW = rc.right / 6 * 2;
	if (!CWnd::Initialize(iBoundaryS, 0, iBoundaryW, rc.bottom, _hWnd, L"ChattingWnd"))
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

	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	// Text
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		L"蜈擎 堅蛐", NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15, L"en-us", &m_pWriteTextFormat);
	if (FAILED(hr)) return false;
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),
		&m_pWhiteBrush);
	if (FAILED(hr)) return false;

	return true;
}

void CChattingWnd::Cleanup()
{
}

void CChattingWnd::Update()
{
}

void CChattingWnd::Render()
{
	TCHAR str[] = L"殮溘 : ";

	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->DrawTextW(str, ARRAYSIZE(str) - 1,
		m_pWriteTextFormat, D2D1::RectF(10, 300, 200, 375),
		m_pWhiteBrush);

	m_pRenderTarget->EndDraw();
}

LRESULT CChattingWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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