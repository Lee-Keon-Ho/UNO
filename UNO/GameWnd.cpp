#include "GameWnd.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"

#define WINDOW_WIDTH 785
#define WINDOW_HEIGHT 734

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

	//──────────────────────────────────────────────────────────────────────────────────
	// Text 사용에 필요
	//──────────────────────────────────────────────────────────────────────────────────
	const WCHAR font[] = L"Consolas";
	const FLOAT fontsize = 15;

	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		font, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontsize, L"en-us", CResourceManager::GetInstance()->GetWriteFormat());
	if (FAILED(hr)) return false;
	//──────────────────────────────────────────────────────────────────────────────────

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0x9F0000, 1.0f),
		CResourceManager::GetInstance()->GetRedBrush());
	if (FAILED(hr)) return false;

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0xFFFFCC, 1.0f),
		CResourceManager::GetInstance()->GetYellowBrush());
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

	TCHAR mapPngFileName[][_MAX_PATH] = { L"PNG\\Menus and Text.png",
											L"PNG\\ok.png" };

	char resourceFileName[][_MAX_PATH] = { "Resource\\RED TEXT26.spr",
											"Resource\\BLUE TEXT36.spr",
											"Resource\\YELLOW TEXT36.spr",
											"Resource\\GREEN TEXT36.spr",
											"Resource\\OK2.spr",
											"Resource\\BORD1.spr",
											"Resource\\LOBBY1.spr",
											"Resource\\NUM3.spr",
											"Resource\\ROOMNAME8.spr", 
											"Resource\\STATE5.spr",
											"Resource\\CREATE7.spr",
											"Resource\\GameBord1.spr"};

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
	switch (_message)
	{
	case WM_LBUTTONDOWN:
		POINT mouse;
		GetCursorPos(&mouse);
		ScreenToClient(_hWnd, &mouse);
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