#include "GameWnd.h"
#include "ResourceManager.h"
#include "Sprite.h"

#define WINDOW_WIDTH 366
#define WINDOW_HEIGHT 389

typedef CResourceManager::eBitmap bitmap_t;

CGameWnd::CGameWnd()
{
}

CGameWnd::~CGameWnd()
{
}

bool CGameWnd::Initialize()
{
	HRESULT hr;
	RECT rc;

	if (!CWnd::Initialize(L"UNO", L"UNO", WINDOW_WIDTH, WINDOW_HEIGHT, SW_SHOW)) return false;
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

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0x9F0000, 1.0f),
		&m_pRedBrush);
	if (FAILED(hr)) return false;

	LoadBitmapFile();

	//
	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->FillRectangle({ 0.0f, 0.0f, 450.0f, 450.0f }, m_pRedBrush);

	m_pRenderTarget->EndDraw();
	return true;
}

bool CGameWnd::LoadBitmapFile()
{
	CDirect* pDirect = CDirect::GetInstance();
	CResourceManager* pRM = CResourceManager::GetInstance();

	TCHAR mapPngFileName[][_MAX_PATH] = { L"PNG\\UNO Menus and Text.png" };

	char resourceFileName[][_MAX_PATH] = { "RED TEXT26.bin" };

	FILE* pFile;
	CSprite* tmpSprite;
	int iTmp = 0;

	for (int y = 0; y < 1; y++)
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
				//_character->SetClip(y, tmpSprite, iTmp);
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

LRESULT CGameWnd::MSGProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
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