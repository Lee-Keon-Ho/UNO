#include "waitingRoomScene.h"

CWaitingRoomScene::CWaitingRoomScene() : m_backGroundRect({0.0f, 0.0f, 1280.0f, 720.0f})
{
}

CWaitingRoomScene::~CWaitingRoomScene()
{
}

void CWaitingRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::WAITING);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject(sprite[CResourceManager::WAITING_ROOM], pBitmap, m_backGroundRect);
}

void CWaitingRoomScene::Start()
{
}

void CWaitingRoomScene::Update()
{
}

void CWaitingRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CWaitingRoomScene::Destroy()
{
}
