#include "LobbyScene.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 770, 695 }
#define RECT	{ 6, 61, 166, 205 }

typedef CResourceManager::eBitmap bitmap_t;

CLobbyScene::CLobbyScene() : m_bOK(0)
{
}

CLobbyScene::~CLobbyScene()
{
}

void CLobbyScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	m_target = new targetList_t[MAX];
	m_pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	m_pOkBitmap = pRM->GetBitmap(bitmap_t::ICON_OK);
	m_pRedBrush = *pRM->GetRedBrush();
	m_sprite = pRM->GetSprite();

	//background
	m_target[BACKGROUND].reserve(1);
	m_target[BACKGROUND].push_back({ 0, 0, 770, 695 });

	//OK icon
	m_target[OK].reserve(1);
	m_target[OK].push_back({ 670 , 600, 740, 670 });
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

	m_sprite[CResourceManager::BORD].at(0).Render(_pRT, m_pBitmap, m_target[BACKGROUND].at(0), 1.0f);

	//_pRT->DrawRectangle({ 50.0f, 80.0f, 300.0f, 260.0f }, m_pRedBrush);

	// ok icon
	m_sprite[CResourceManager::OK].at(m_bOK).Render(_pRT, m_pOkBitmap, m_target[OK].at(0), 1.0f);
	m_bOK = 0;

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
}
