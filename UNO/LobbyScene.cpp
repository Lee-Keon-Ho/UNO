#include "LobbyScene.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 770, 695 }
#define RECT	{ 6, 61, 166, 205 }

typedef CResourceManager::eBitmap bitmap_t;

CLobbyScene::CLobbyScene()
	: m_bOK(0), m_okRect({ 670 , 600, 740, 670 }), m_bordRect({ 0, 0, 770, 695 }),
	m_roomRect({ 50.0f, 50.0f, 500.0f, 400.0f }), m_userRect({ 501.0f, 50.0f, 710.0f, 400.0f }),
	m_chatRect({ 50.0f, 401.0f, 500.0f, 650.0f }), m_numTextSize(3), m_roomNameTextSize(8),
	m_stateTextSize(5)
{
}

CLobbyScene::~CLobbyScene()
{
}

void CLobbyScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	ID2D1Bitmap* pBitmapOK = pRM->GetBitmap(bitmap_t::ICON_OK);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();
	m_pRedBrush = *pRM->GetBlackBrush();

	//background
	m_pBord = new CObject(sprite[CResourceManager::BORD], pBitmap);
	m_pBord->SetTarget(m_bordRect);

	//OK icon
	m_pOk = new CObject(sprite[CResourceManager::OK], pBitmapOK);
	m_pOk->SetTarget(m_okRect);
	m_pOk->SetTarget(m_okRect);
	
	//Room
	m_pRoomList = new CObject(sprite[CResourceManager::LOBBY], pBitmap);
	m_pRoomList->SetTarget(m_roomRect);

	//user
	m_pUserList = new CObject(sprite[CResourceManager::LOBBY], pBitmap);
	m_pUserList->SetTarget(m_userRect);

	//chatting
	m_pChatting = new CObject(sprite[CResourceManager::LOBBY], pBitmap);
	m_pChatting->SetTarget(m_chatRect);

	//num text
	m_pNumText = new CObject(sprite[CResourceManager::NUM], pBitmap);
	for (int i = 0; i < m_numTextSize; i++)
	{
		m_pNumText->SetTarget({ 65.0f + (i * 15), 55.0f, 85.0f + (i * 15), 75.0f });
	}
	
	//room name text
	m_pRoomNameText = new CObject(sprite[CResourceManager::ROOMNAME], pBitmap);
	for (int i = 0; i < m_roomNameTextSize; i++)
	{
		m_pRoomNameText->SetTarget({ 200.0f + (i * 15), 55.0f, 220.0f + (i * 15), 75.0f });
	}

	//state text
	m_pStateText = new CObject(sprite[CResourceManager::STATE], pBitmap);
	for (int i = 0; i < m_stateTextSize; i++)
	{
		m_pStateText->SetTarget({ 400.0f + (i * 15), 55.0f, 420.0f + (i * 15), 75.0f });
	}
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

	// background
	m_pBord->Render(_pRT, 0, 1.0f);

	m_pRoomList->Render(_pRT, 0, 1.0f);
	m_pUserList->Render(_pRT, 0, 1.0f);
	m_pChatting->Render(_pRT, 0, 1.0f);
	m_pNumText->Render(_pRT, 1.0f);
	m_pRoomNameText->Render(_pRT, 1.0f);
	m_pStateText->Render(_pRT, 1.0f);

	// ok icon
	m_pOk->Render(_pRT, m_bOK, 1.0f);
	m_bOK = 0;

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
	if (m_pStateText) { delete m_pStateText; m_pStateText = nullptr; }
	if (m_pRoomNameText) { delete m_pRoomNameText; m_pRoomNameText = nullptr; }
	if (m_pNumText) { delete m_pNumText; m_pNumText = nullptr; }
	if (m_pRoomList) { delete m_pRoomList; m_pRoomList = nullptr; }
	if (m_pOk) { delete m_pOk; m_pOk = nullptr; }
	if (m_pBord) { delete m_pBord; m_pBord = nullptr; }
}
