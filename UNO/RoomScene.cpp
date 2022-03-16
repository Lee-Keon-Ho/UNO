#include "RoomScene.h"

CRoomScene::CRoomScene()
	: m_gameBordRECT({ 0, 0, 770, 695 })
{
}

CRoomScene::~CRoomScene()
{
}

void CRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pGameBord = new CObject(sprite[CResourceManager::GAMEBORD], pBitmap);
	m_pGameBord->SetTarget(m_gameBordRECT);
}

void CRoomScene::Start()
{
}

void CRoomScene::Update()
{
}

void CRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pGameBord->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CRoomScene::Destroy()
{
	if (m_pGameBord) { delete m_pGameBord; m_pGameBord = nullptr; }
}
