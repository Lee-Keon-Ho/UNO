#include "Client.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "Input.h"

CLobbyScene::CLobbyScene()
	: m_bOK(0), m_okRect({ 670 , 600, 740, 670 }), m_bordRect({ 0, 0, 770, 695 }),
	m_roomRect({ 50.0f, 50.0f, 500.0f, 400.0f }), m_userRect({ 501.0f, 50.0f, 710.0f, 400.0f }),
	m_chatRect({ 50.0f, 401.0f, 500.0f, 650.0f }), m_createButtonRect({ 501.0f, 401.0f, 605.0f, 481.0f }),
	m_quickButtonRect({ 606.0f, 401.0f, 710.0f, 481.0f }), m_numTextSize(3),
	m_roomNameTextSize(8), m_stateTextSize(5), m_createTextSize(6), m_quickTextSize(5)
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

	// createButton
	m_pCreateButton = new CObject(sprite[CResourceManager::CREATE], pBitmap);
	m_pCreateButton->SetTarget(m_createButtonRect);
	for (int i = 0; i < m_createTextSize; i++)
	{
		m_pCreateButton->SetTarget({505.0f + (i * 15), 426.0f, 525.0f + (i * 15), 456.0f });
	}

	// quickButton
	m_pQuickButton = new CObject(sprite[CResourceManager::QUICK], pBitmap);
	m_pQuickButton->SetTarget(m_quickButtonRect);
	for (int i = 0; i < m_quickTextSize; i++)
	{
		m_pQuickButton->SetTarget({ 617.0f + (i * 15), 426.0f, 637.0f + (i * 15), 456.0f });
	}

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

	/*room = new CRoom(sprite[CResourceManager::BORD], pBitmap);
	room->m_room.number = 1;
	room->SetTarget({ 60.0f, 90.0f, 490.0f, 140.0f });

	room1 = new CRoom(sprite[CResourceManager::BORD], pBitmap);
	room1->m_room.number = 2;
	room1->SetTarget({ 60.0f, 90.0f, 490.0f, 140.0f });

	room2 = new CRoom(sprite[CResourceManager::BORD], pBitmap);
	room2->m_room.number = 3;
	room2->SetTarget({ 60.0f, 90.0f, 490.0f, 140.0f });*/
}

void CLobbyScene::Start()
{
}

void CLobbyScene::Update()
{
	POINT mouse = CInput::GetInstance()->GetMousePosition();
	if (mouse.x >= m_createButtonRect.left && mouse.x <= m_createButtonRect.right &&
		mouse.y >= m_createButtonRect.top && mouse.y <= m_createButtonRect.bottom)
	{
		CClient::GetInstance()->Send(CResourceManager::GetInstance()->GetName(), 2);
		CSceneManager::GetInstance()->ChangeScene(eScene::GAME_SCENE);
	}
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
	m_pCreateButton->Render(_pRT, 1.0f);
	m_pQuickButton->Render(_pRT, 1.0f);
	m_pNumText->Render(_pRT, 1.0f);
	m_pRoomNameText->Render(_pRT, 1.0f);
	m_pStateText->Render(_pRT, 1.0f);
	/*room->Render(_pRT, 1.0f);
	room1->Render(_pRT, 1.0f);
	room2->Render(_pRT, 1.0f);*/
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
	if (m_pQuickButton) { delete m_pQuickButton; m_pQuickButton = nullptr; }
	if (m_pCreateButton) { delete m_pCreateButton; m_pCreateButton = nullptr; }
	if (m_pChatting) { delete m_pChatting; m_pChatting = nullptr; }
	if (m_pUserList) { delete m_pUserList; m_pUserList = nullptr; }
	if (m_pRoomList) { delete m_pRoomList; m_pRoomList = nullptr; }
	if (m_pOk) { delete m_pOk; m_pOk = nullptr; }
	if (m_pBord) { delete m_pBord; m_pBord = nullptr; }
}
