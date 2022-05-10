#include "Client.h"
#include "PacketType.h"
#include "GameRoomScene.h"
#include "timer.h"
#include "Input.h"
#include "SceneManager.h"
#include "information.h"

CGameRoomScene::CGameRoomScene() : 
	m_backGroundRect({0.0f, 0.0f, 1280.0f, 720.0f}), m_chatBackGroundRect({ 0.0f, 486.0f, 353.0f, 686.0f }), 
	m_chatTextRect({ 10.0f, 693.0f, 343.0f, 720.0f }), m_chattingRect({ 10.0f, 680.0f, 343.0f, 720.0f }),
	fontSize(15), m_MyNumber(0), m_bChatting(false), m_chatCount(0)
{
}

CGameRoomScene::~CGameRoomScene()
{
	Destroy();
}

void CGameRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	CInformation* pInformation = CInformation::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::WAITING);
	ID2D1Bitmap* pButtonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	ID2D1Bitmap* pExitBitmap = pRM->GetBitmap(bitmap_t::EXIT);
	ID2D1Bitmap* pCardBitmap = pRM->GetBitmap(bitmap_t::CARD);
	ID2D1Bitmap* pReadyBitmap = pRM->GetBitmap(bitmap_t::READY);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject2D(sprite[CResourceManager::WAITING_ROOM], pBitmap, m_backGroundRect);
	m_pChatBackGround = new CObject2D(sprite[CResourceManager::EXIT_BACKGROUND], pExitBitmap, m_chatBackGroundRect);

	m_pExitButton = new CButton(sprite[CResourceManager::WATTING_ROOM_EXIT], pButtonBitmap, { 1179.0f, 686.0f, 1280.0f, 720.0f });
	m_pReadyButton = new CButton(sprite[CResourceManager::READY_BUTTON], pReadyBitmap, { 566.0f, 321.0f, 713.0f, 399.0f });
	m_pStartButton = new CButton(sprite[CResourceManager::START_BUTTON], pReadyBitmap, { 566.0f, 321.0f, 713.0f, 399.0f });

	// 2022-04-29
	m_pChatText = new CText(m_chatTextRect, fontSize, 0, CText::T_WHITE);
	m_pChatting = new CChatting(m_chattingRect, fontSize, fontSize, CText::T_WHITE);

	// 2022-05-09 수정
	m_pPlayerObject = new CPlayerObject();

	m_pUserInfo = CInformation::GetInstance()->GetUserInfo();
	m_pRoomInfo = CInformation::GetInstance()->GetRoomInfo();
	
	// 2022-05-03 수정 : test
	for (int i = 0; i < 12; i++)
	{
		m_player1Card.push_back(new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 500.0f + (19 * i), 500.0f, 570.0f + (19 * i), 607.0f }));
		m_player2Card.push_back(new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 171.0f + (12 * i), 108.0f, 241.0f + (12 * i), 215.0f }));
		m_player3Card.push_back(new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 1050.0f - (12 * i), 108.0f, 1120.0f - (12 * i), 215.0f }));
		m_player4Card.push_back(new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 171.0f + (12 * i), 319.0f, 241.0f + (12 * i), 426.0f }));
		m_player5Card.push_back(new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 1050.0f - (12 * i), 319.0f, 1120.0f - (12 * i), 426.0f }));
	}

	// 2022-04-28 수정
	m_chatBuffer = new wchar_t[CHAT_MAX];
	memset(m_chatBuffer, 0, sizeof(wchar_t) * CHAT_MAX);

	CTimer::GetInstance()->ResetTimer();

	m_pUserInfo = pInformation->GetUserInfo();
	m_pRoomInfo = pInformation->GetRoomInfo();

	char buffer[] = "game";
	CClient::GetInstance()->Send(buffer, CS_PT_ROOMSTATE);
	Sleep(10);

	/* 2022-05-11 start
	if (m_pUserInfo->boss) m_pCurrentButton = m_pReadyButton;
	else m_pCurrentButton = m_pStartButton;
	*/
}

void CGameRoomScene::Start()
{
}

void CGameRoomScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	CTimer* pTimer = CTimer::GetInstance();
	CInformation* pInformation = CInformation::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	if (pTimer->GetTime() >= 1.0)
	{
		char buffer[] = "game";
		CClient::GetInstance()->Send(buffer, CS_PT_ROOMSTATE);
		pTimer->ResetTimer();
	}

	m_pExitButton->ButtonPosition(mouse);

	if (key == VK_LBUTTON)
	{
		if (m_pUserInfo->boss != 1)
		{
			if (m_pCurrentButton->OnButton(mouse))
			{
				char buffer[] = "ready";
				CClient::GetInstance()->Send(buffer, CS_PT_READY);
			}
		}
		else
		{
			if (m_bStart)
			{
				m_pCurrentButton->OnButton(mouse);
			}
		}
		
		if (m_pExitButton->OnButton(mouse))
		{
			char buffer[] = "destroy";
			m_pExitButton->OnButtonUp();
			CClient::GetInstance()->Send(buffer, CS_PT_OUTROOM);
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
		m_bChatting = false;
	}

	if (key == VK_RETURN)
	{
		m_bChatting = true;
	}

	// 2022-04-28 수정 : test
	if (m_bChatting)
	{
		if ((key >= 'A' && key <= 'z') || (key >= '0' && key <= '9') || key == VK_SPACE)
		{
			m_chatBuffer[m_chatCount] = key;
			m_chatCount++;
			if (m_chatCount > CHAT_MAX - 1) m_chatCount = CHAT_MAX - 1;
		}
		if (key == VK_BACK)
		{
			--m_chatCount;
			if (m_chatCount < 0) m_chatCount = 0;
			m_chatBuffer[m_chatCount] = 0;
		}
		if (key == VK_RETURN)
		{
			if (m_chatCount > 0)
			{
				m_chatBuffer[m_chatCount] = 0;
				CClient::GetInstance()->Send(m_chatBuffer, CS_PT_CHATTING);
				memset(m_chatBuffer, 0, sizeof(WCHAR) * CHAT_MAX);
				m_chatCount = 0;
			}
		}
		//2022-05-10
		//m_chatBuffer[m_chatCount] = *CInput::GetInstance()->GetWKey();
	}


	// 2022-05-10 수정
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (wcsncmp(m_pUserInfo[i].playerName, pInformation->GetName(), wcslen(pInformation->GetName())) == 0)
		{
			m_MyNumber = m_pUserInfo[i].number;
		}
	}
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (m_pUserInfo[i].ready == true)
		{
			m_bStart = true;
		}
		else
		{
			m_bStart = false;
			break;
		}
	}
}

void CGameRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);
	

	// 2022-05-09 수정
	m_pPlayerObject->Render(_pRT, m_pRoomInfo, m_pUserInfo, m_MyNumber);
	
	m_pChatBackGround->Render(_pRT, 0.3f);

	if (m_bChatting)
	{
		m_pChatText->Render(_pRT, m_chatBuffer);
	}

	// 2022-05-04 수정 : test
	/*
	for (int i = 0; i < 12; i++)
	{
		m_player1Card[i]->Render(_pRT, 1.0f);
		m_player2Card[i]->Render(_pRT, 1.0f);
		m_player3Card[i]->Render(_pRT, 1.0f);
		m_player4Card[i]->Render(_pRT, 1.0f);
		m_player5Card[i]->Render(_pRT, 1.0f);
	}
	*/
	if (m_pUserInfo->boss == true) m_pCurrentButton->Render(_pRT, 1, 1.0f);
	else m_pCurrentButton->Render(_pRT, 1.0f);
	

	m_pChatting->Render(_pRT);

	m_pExitButton->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CGameRoomScene::Destroy()
{
	// 2022-05-02 수정
	memset(m_chatBuffer, 0, 32);
	CInformation::GetInstance()->ReSetChatting();

	card_t::iterator cardIter1 = m_player1Card.begin();
	card_t::iterator cardEndIter1 = m_player1Card.end();
	card_t::iterator cardIter2 = m_player1Card.begin();
	card_t::iterator cardEndIter2 = m_player1Card.end();
	card_t::iterator cardIter3 = m_player1Card.begin();
	card_t::iterator cardEndIter3 = m_player1Card.end();
	card_t::iterator cardIter4 = m_player1Card.begin();
	card_t::iterator cardEndIter4 = m_player1Card.end();
	card_t::iterator cardIter5 = m_player1Card.begin();
	card_t::iterator cardEndIter5 = m_player1Card.end();
	while (cardIter1 != cardEndIter1)
	{
		if (*cardIter1) { delete* cardIter1; *cardIter1 = nullptr; }
		if (*cardIter2) { delete* cardIter2; *cardIter2 = nullptr; }
		if (*cardIter3) { delete* cardIter3; *cardIter3 = nullptr; }
		if (*cardIter4) { delete* cardIter4; *cardIter4 = nullptr; }
		if (*cardIter5) { delete* cardIter5; *cardIter5 = nullptr; }
		cardIter1++; cardIter2++; cardIter3++; cardIter4++; cardIter5;;
	}
	m_player1Card.clear();
	m_player2Card.clear();
	m_player3Card.clear();
	m_player4Card.clear();
	m_player5Card.clear();

	if (m_pPlayerObject) { delete m_pPlayerObject; m_pPlayerObject = nullptr; }
	if (m_pChatting) { delete m_pChatting; m_pChatting = nullptr; }
	if (m_pStartButton) { delete m_pStartButton; m_pStartButton = nullptr; }
	if (m_pReadyButton) { delete m_pReadyButton; m_pReadyButton = nullptr; }
	if (m_pExitButton) { delete m_pExitButton; m_pExitButton = nullptr; }
	if (m_pChatBackGround) { delete m_pChatBackGround; m_pChatBackGround = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}