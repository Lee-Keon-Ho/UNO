#include "GameWnd.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Input.h"

#pragma comment( lib, "imm32.lib")
#define IMC_GETOPENSTATUS 0x0005

#define WINDOW_WIDTH 1296
#define WINDOW_HEIGHT 759

typedef CResourceManager::eBitmap bitmap_t;
typedef CResourceManager::eICON icon_t;

CGameWnd::CGameWnd()
{
}

CGameWnd::~CGameWnd()
{
	Cleanup();
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
		CResourceManager::GetInstance()->GetBrush(CResourceManager::COLOR_WHITE));
	if (FAILED(hr)) return false;

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0x000000, 1.0f),
		CResourceManager::GetInstance()->GetBrush(CResourceManager::COLOR_BLACK));
	if (FAILED(hr)) return false;

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFF0000, 1.0f),
		CResourceManager::GetInstance()->GetBrush(CResourceManager::COLOR_RED));
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
											L"PNG\\Create.png",
											L"PNG\\RoomInPlayer.png",
											L"PNG\\card.png",
											L"PNG\\readyButton.png",
											L"PNG\\boss.png",
											L"PNG\\MY TURN.png",
											L"PNG\\choiceColor.png",
											L"PNG\\cardBoard.png",
											L"PNG\\GAME OVER.png"};

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
											"Resource\\CreateOkButton2.spr",
											"Resource\\roomListButton2.spr",
											"Resource\\PlayerOne1.spr",
											"Resource\\PlayerTwo1.spr" ,
											"Resource\\PlayerThree1.spr" ,
											"Resource\\PlayerFour1.spr" ,
											"Resource\\PlayerFive1.spr",
											"Resource\\UnoCard110.spr",
											"Resource\\ready2.spr",
											"Resource\\start2.spr",
											"Resource\\SecretCard1.spr",
											"Resource\\centerCard1.spr",
											"Resource\\boss1.spr",
											"Resource\\MyTurn1.spr",
											"Resource\\choiceColor4.spr",
											"Resource\\cardBoard1.spr",
											"Resource\\GameOver1.spr"};

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
	HIMC himc;
	POINT mouse;

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
	case WM_CHAR:
		CInput::GetInstance()->SetKey(_wParam);
		break;
	case WM_IME_COMPOSITION:
		OnImeComposition(_hWnd, _lParam);
		break;
	case WM_CLOSE:
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


bool CGameWnd::OnImeComposition(HWND _hWnd, LPARAM _lParam)
{
	HIMC hImc = ImmGetContext(_hWnd);
	if (hImc == NULL)
	{
		return false;
	}

	int nLength = 0;

	wchar_t wszComp[4] = { 0, };

	if (_lParam & GCS_RESULTSTR)
	{
		nLength = ImmGetCompositionStringW(hImc, GCS_RESULTSTR, NULL, 0);

		if (nLength > 0)
		{
			ImmGetCompositionStringW(hImc, GCS_RESULTSTR, wszComp, nLength);

			for (int i = 0; i < nLength; ++i)
			{
				if (wszComp[i] != 0)
				{
					wprintf_s(L"조합 완료 : %s \n", wszComp);
					memcpy(m_wchar, wszComp, 8);
				}
			}
		}
	}
	else if (_lParam & GCS_COMPSTR)
	{
		nLength = ImmGetCompositionStringW(hImc, GCS_COMPSTR, NULL, 0);

		if (nLength > 0)
		{
			ImmGetCompositionStringW(hImc, GCS_COMPSTR, wszComp, nLength);

			for (int i = 0; i < nLength; ++i)
			{
				if (wszComp[i] != 0)
				{
					wprintf_s(L"조합 ing : %s \n", wszComp);
					memcpy(m_wchar, wszComp, 8);
				}
			}
		}
	}
	CInput::GetInstance()->SetWkey(m_wchar);
	ImmReleaseContext(_hWnd, hImc);
	return true;
}