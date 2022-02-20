#include "Wnd.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
// Wnd Procedure
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	CWnd* pWnd = nullptr;
	if (_message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0);
		pWnd = (CWnd*)pCS->lpCreateParams;
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)pWnd))
		{
			if (GetLastError() != 0)return E_FAIL;
		}
	}
	else
	{
		pWnd = (CWnd*)GetWindowLongPtr(_hWnd, GWLP_USERDATA);
	}

	if (pWnd) return pWnd->MSGProc(_hWnd, _message, _wParam, _lParam);

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

CWnd::CWnd()
{
	m_hWnd = nullptr;
}

CWnd::~CWnd()
{

}

bool CWnd::Initialize(LPCWSTR _windowClass, LPCWSTR _title, int _width, int _height, int _nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _windowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Fail_RegisterClassEX", L"Fail_RegisterClassEX", MB_OK);
		return false;
	}

	m_hWnd = CreateWindow(
		_windowClass,
		_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_width, _height,
		NULL, NULL,
		GetModuleHandle(NULL),
		this);

	if (!m_hWnd)
	{
		MessageBox(NULL, L"Fail_Wnd", L"Fail_Wnd", MB_OK);
		return false;
	}

	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	ShowWindow(m_hWnd, _nCmdShow);
	UpdateWindow(m_hWnd);

	return true;
}

void CWnd::Cleanup()
{

}

LRESULT CWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	return 0;
}