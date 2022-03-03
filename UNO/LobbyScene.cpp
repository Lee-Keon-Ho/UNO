#include "LobbyScene.h"
#include "ResourceManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 350, 350}
#define RECT	{ 6, 61, 166, 205}

typedef CResourceManager::eBitmap bitmap_t;

CLobbyScene::CLobbyScene() : m_bOK(0)
{
}

CLobbyScene::~CLobbyScene()
{
}

void CLobbyScene::Awake()
{
	m_pRedBrush = *CResourceManager::GetInstance()->GetRedBrush();
}

void CLobbyScene::Start()
{
}

void CLobbyScene::Update()
{
}

void CLobbyScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	_pRT->DrawRectangle({ 50.0f, 80.0f, 300.0f, 260.0f }, m_pRedBrush);

	// ok icon
	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::ICON_OK),
		{ 304.0f , 306.0f, 334.0f, 331.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		pRM->GetOKIcon(m_bOK).GetRect()); m_bOK = 0;

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
}
