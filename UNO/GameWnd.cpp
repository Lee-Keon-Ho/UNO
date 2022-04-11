#include "GameWnd.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Input.h"

#define WINDOW_WIDTH 1296
#define WINDOW_HEIGHT 759

typedef CResourceManager::eBitmap bitmap_t;
typedef CResourceManager::eICON icon_t;

CGameWnd::CGameWnd()
{
}

CGameWnd::~CGameWnd()
{
}

bool CGameWnd::Initialize()
{
	if (!CWnd::Initialize(L"Uno", L"Uno", WINDOW_WIDTH, WINDOW_HEIGHT, SW_SHOW)) return false;

	HRESULT hr;
	RECT rc;

	//──────────────────────────────────────────────────────────────────────────────────
	// RenderTarget
	//──────────────────────────────────────────────────────────────────────────────────
	GetClientRect(m_hWnd, &rc);
	hr = CDirect::GetInstance()->GetD2DFactory()->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(rc.right, rc.bottom)),
		&m_pRenderTarget);
	if (FAILED(hr)) return false;
	//──────────────────────────────────────────────────────────────────────────────────

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFFFFFF, 1.0f),
		CResourceManager::GetInstance()->GetWhiteBrush());
	if (FAILED(hr)) return false;

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0x000000, 1.0f),
		CResourceManager::GetInstance()->GetBlackBrush());
	if (FAILED(hr)) return false;

	LoadBitmapFile();

	return true;
}

bool CGameWnd::LoadBitmapFile()
{
	CDirect* pDirect = CDirect::GetInstance();
	CResourceManager* pRM = CResourceManager::GetInstance();

	TCHAR mapPngFileName[][_MAX_PATH] = {	L"PNG\\LOGIN.png",
											L"PNG\\LOBBY.png",
											L"PNG\\BUTTON.png",
											L"PNG\\character.png",
											L"PNG\\waitingRoom.png",
											L"PNG\\exit.png",
											L"PNG\\Create.png"};

	char resourceFileName[][_MAX_PATH] = {	"Resource\\LOBBY1.spr",
											"Resource\\LOGIN_background1.spr",
											"Resource\\LOGIN_BUTTON2.spr",
											"Resource\\LOGIN_object1.spr",
											"Resource\\CREATE_BUTTON2.spr",
											"Resource\\QUICK_BUTTON2.spr",
											"Resource\\CHOOSE_BUTTON2.spr",
											"Resource\\Lobby_exit_button2.spr",
											"Resource\\character5.spr",
											"Resource\\waitingRoom1.spr",
											"Resource\\waitingroom_Exit_Button2.spr",
											"Resource\\exit_ok2.spr",
											"Resource\\exit_no2.spr",
											"Resource\\exitbackground1.spr",
											"Resource\\exitTextObject1.spr",
											"Resource\\CreateRoom1.spr",
											"Resource\\CreateNoButton2.spr",
											"Resource\\CreateOkButton2.spr"};

	FILE* pFile;
	CSprite* tmpSprite;
	int iTmp = 0;

	for (int y = 0; y < icon_t::ICON_MAX; y++)
	{
		for (int x = 0; resourceFileName[y][x] != '\0'; x++)
		{
			if (isdigit(resourceFileName[y][x]))
			{
				iTmp = atoi(&resourceFileName[y][x]);
				tmpSprite = new CSprite[iTmp];
				errno_t errNum = fopen_s(&pFile, resourceFileName[y], "rb");
				if (errNum != 0)
				{
					MessageBox(NULL, L"Fail", L"Fail", MB_OK);
					if (tmpSprite) { delete[] tmpSprite; tmpSprite = nullptr; }
					return false;
				}
				fread(tmpSprite, sizeof(CSprite), iTmp, pFile);
				pRM->SetSprite(tmpSprite, iTmp, y);
				if (tmpSprite) { delete[] tmpSprite; tmpSprite = nullptr; }
				fclose(pFile); iTmp = 0; break;
			}
		}
	}

	// Bitmap
	ID2D1Bitmap* pBitmap;
	for (int i = 0; i < bitmap_t::MAX; i++)
	{
		pDirect->LoadBitmapFromFile(mapPngFileName[i],
			&pBitmap, m_pRenderTarget);
		pRM->SetBitmap(pBitmap);
	}
	return true;
}

void CGameWnd::Cleanup()
{
	if (m_pRenderTarget) { m_pRenderTarget->Release(); m_pRenderTarget = nullptr; }
}

void CGameWnd::Update()
{
	CSceneManager::GetInstance()->Update();
}

void CGameWnd::Render()
{
	CSceneManager::GetInstance()->Render(m_pRenderTarget);
}

LRESULT CGameWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	POINT mouse;
	char key;
	switch (_message)
	{
	case WM_MOUSEMOVE :
	case WM_LBUTTONUP:
		mouse.x = LOWORD(_lParam);
		mouse.y = HIWORD(_lParam);
		CInput::GetInstance()->SetMousePosition(mouse);
		break;
	case WM_LBUTTONDOWN:
		CInput::GetInstance()->SetKey(_wParam);
		break;
	case WM_KEYDOWN:
		// 대소문자 구분을 하지 않음 character를 사용해야함
		CInput::GetInstance()->SetKey(_wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}

	/*case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:*/
enum class eInputType : u_short
{
	MOUSE_MOVE = 0,
	MOUSE_LBUTTONDOWN,
	MOUSE_LBUTTONUP,
	MOUSE_LBUTTONDBLCLK,
	MOUSE_RBUTTONDOWN,
	MOUSE_RBUTTONUP,
	MOUSE_RBUTTONDBLCLK,

	KEY_DOWN,
	KEY_UP,
	KEY_CHAR,

	INPUT_TYPE_MAX
};
