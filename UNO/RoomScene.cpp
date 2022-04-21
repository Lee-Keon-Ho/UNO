#include "RoomScene.h"

CRoomScene::CRoomScene()
	: m_gameBordRECT({ 0, 0, 770, 695 })
{
}

CRoomScene::~CRoomScene()
{
	Destroy();
}

void CRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	//ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();


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



	_pRT->EndDraw();
}

void CRoomScene::Destroy()
{

}
