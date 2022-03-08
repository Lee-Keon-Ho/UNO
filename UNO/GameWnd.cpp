#include "GameWnd.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"

typedef CResourceManager::eBitmap bitmap_t;
typedef CResourceManager::eICON icon_t;

CGameWnd::CGameWnd()
{
}

CGameWnd::~CGameWnd()
{
}

bool CGameWnd::Initialize(HWND _hWnd)
{
	HRESULT hr;
	RECT rc;
	GetClientRect(_hWnd, &rc);
	int iBoundaryW = rc.right / 6 * 3;
	int iBoundaryS = rc.right / 6;
	if (!CWnd::Initialize(iBoundaryS, 0, iBoundaryW, rc.bottom, _hWnd, L"GameWnd"))
		return false;
	//��������������������������������������������������������������������������������������������������������������������������������������������������������������������
	// RenderTarget
	//��������������������������������������������������������������������������������������������������������������������������������������������������������������������
	GetClientRect(m_hWnd, &rc);
	hr = CDirect::GetInstance()->GetD2DFactory()->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(m_hWnd, D2D1::SizeU(rc.right, rc.bottom)),
		&m_pRenderTarget);
	if (FAILED(hr)) return false;
	//��������������������������������������������������������������������������������������������������������������������������������������������������������������������

	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0x9F0000, 1.0f),
		CResourceManager::GetInstance()->GetRedBrush());
	if (FAILED(hr)) return false;

	LoadBitmapFile();

	return true;
}

bool CGameWnd::LoadBitmapFile()
{
	CDirect* pDirect = CDirect::GetInstance();
	CResourceManager* pRM = CResourceManager::GetInstance();

	TCHAR mapPngFileName[][_MAX_PATH] = { L"PNG\\UNO Menus and Text.png",
											L"PNG\\icon.png" };

	char resourceFileName[][_MAX_PATH] = { "Resource\\RED TEXT26.bin",
											"Resource\\BLUE TEXT36.bin",
											"Resource\\YELLOW TEXT36.bin",
											"Resource\\GREEN TEXT36.bin",
											"Resource\\OK2.bin" };

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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}