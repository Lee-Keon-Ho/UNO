#include "Client.h"
#include "PacketType.h"
#include "waitingRoomScene.h"
#include "timer.h"
#include "Input.h"
#include "SceneManager.h"
#include "information.h"

CWaitingRoomScene::CWaitingRoomScene() : 
	m_backGroundRect({0.0f, 0.0f, 1280.0f, 720.0f}), m_player1Rect({ 384.0f, 472.0f, 838.0f, 720.0f }),
	m_player2Rect({ 0.0f, 69.0f, 440.0f, 250.0f }), m_player3Rect({ 837.0f, 69.0f, 1280.0f, 250.0f }),
	m_player4Rect({ 10.0f, 285.0f, 450.0f, 466.0f }), m_player5Rect({ 837.0f, 275.0f, 1280.0f, 456.0f }),
	m_player1ImageRect({ 400.0f, 514.0f, 480.0f, 594.0f }), m_player2ImageRect({ 80.0f, 114.0f, 160.0f, 194.0f }),
	m_player3ImageRect({ 1129.0f, 114.0f, 1209.0f, 194.0f }), m_player4ImageRect({ 80.0f, 330.0f, 160.0f, 410.0f }),
	m_player5ImageRect({ 1129.0f, 330.0f, 1209.0f, 410.0f }), m_player1NameRect({ 424.0f, 602.0f, 504.0f, 682.0f }),
	m_player2NameRect({ 103.0f, 197.0f, 183.0f, 277.0f }), m_player3NameRect({ 1153.0f, 197.0f, 1233.0f, 277.0f }),
	m_player4NameRect({ 103.0f, 412.0f, 183.0f, 492.0f }), m_player5NameRect({ 1153.0f, 412.0f, 1233.0f, 492.0f }),
	m_chatBackGroundRect({ 0.0f, 486.0f, 353.0f, 686.0f }),
	fontSize(15), m_MyNumber(0), m_bChatting(false), m_chatCount(0)
{
}

CWaitingRoomScene::~CWaitingRoomScene()
{
	Destroy();
}

void CWaitingRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	CInformation* pInformation = CInformation::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::WAITING);
	ID2D1Bitmap* pButtonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	ID2D1Bitmap* pPlayerCountBitmap = pRM->GetBitmap(bitmap_t::ROOM_IN_PLAYER);
	ID2D1Bitmap* pPlayerImage = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pExitBitmap = pRM->GetBitmap(bitmap_t::EXIT);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject2D(sprite[CResourceManager::WAITING_ROOM], pBitmap, m_backGroundRect);
	m_pChatBackGround = new CObject2D(sprite[CResourceManager::EXIT_BACKGROUND], pExitBitmap, m_chatBackGroundRect);

	m_pExitButton = new CButton(sprite[CResourceManager::WATTING_ROOM_EXIT], pButtonBitmap, { 1179.0f, 686.0f, 1280.0f, 720.0f });

	// 2022-04-29
	m_pChatText = new CText({ 10.0f, 693.0f, 343.0f, 720.0f }, fontSize, 0, CText::T_WHITE);
	m_pChatting = new CChatting({ 10.0f, 680.0f, 343.0f, 720.0f }, fontSize, 15, CText::T_WHITE);

	m_playerImage.reserve(PLAYER_MAX);
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player1ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player2ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player3ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player4ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player5ImageRect));

	m_pUserInfo = CInformation::GetInstance()->GetUserInfo();
	m_pRoomInfo = CInformation::GetInstance()->GetRoomInfo();

	m_player.reserve(PLAYER_MAX);
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_ONE], pPlayerCountBitmap, m_player1Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_TWO], pPlayerCountBitmap, m_player2Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_THREE], pPlayerCountBitmap, m_player3Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FOUR], pPlayerCountBitmap, m_player4Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FIVE], pPlayerCountBitmap, m_player5Rect));

	m_pName.reserve(PLAYER_MAX);
	m_pName.push_back(new CText(m_player1NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player2NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player3NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player4NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player5NameRect, fontSize, 0, CText::T_WHITE));
	
	// 2022-04-28 수정
	m_chatBuffer = new wchar_t[32];
	memset(m_chatBuffer, 0, 64);

	CTimer::GetInstance()->ResetTimer();

	m_pUserInfo = pInformation->GetUserInfo();
	m_pRoomInfo = pInformation->GetRoomInfo();
	m_pChatting->SetList();
}

void CWaitingRoomScene::Start()
{
}

void CWaitingRoomScene::Update()
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
		m_pUserInfo = pInformation->GetUserInfo();
		m_pRoomInfo = pInformation->GetRoomInfo();
		m_pChatting->SetList();
		pTimer->ResetTimer();
	}

	m_pExitButton->OnButton(mouse);

	if (key == VK_LBUTTON)
	{
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
			if (m_chatCount > 31) m_chatCount = 31;
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
				m_pChatting->SetList();
				memset(m_chatBuffer, 0, 64);
				m_chatCount = 0;
			}
		}
	}

	for (int i = 0; i < m_pRoomInfo->playerCount; i++)
	{
		if (wcsncmp(m_pUserInfo[i].playerName, CInformation::GetInstance()->GetName(), wcslen(CInformation::GetInstance()->GetName())) == 0)
		{
			m_MyNumber = m_pUserInfo[i].number;
		}
	}
}

void CWaitingRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);
	
	// 2022-04-28 수정 필요
	for (int iObject = 1, iUserInfo = 0; iUserInfo < m_pRoomInfo->playerCount; iUserInfo++)
	{
		int count = m_pUserInfo[iUserInfo].number;
		if (m_MyNumber == count)
		{
			m_player[0]->Render(_pRT, 1.0f);
			m_playerImage[0]->Render(_pRT, m_pUserInfo[count].image, 1.0f);
			m_pName[0]->Render(_pRT, m_pUserInfo[count].playerName);
		}
		else
		{
			m_player[iObject]->Render(_pRT, 1.0f);
			m_playerImage[iObject]->Render(_pRT, m_pUserInfo[count].image, 1.0f);
			m_pName[iObject]->Render(_pRT, m_pUserInfo[count].playerName);
			iObject++;
		}
	}
	
	m_pChatBackGround->Render(_pRT, 0.3f);

	if (m_bChatting)
	{
		m_pChatText->Render(_pRT, m_chatBuffer);
	}

	m_pChatting->Render(_pRT);

	m_pExitButton->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CWaitingRoomScene::Destroy()
{
	// 2022-05-02 수정
	memset(m_chatBuffer, 0, 32);
	CInformation::GetInstance()->ReSetChatting();

	if (m_pChatting) { delete m_pChatting; m_pChatting = nullptr; }

	player_t::iterator iter = m_player.begin();
	player_t::iterator endIter = m_player.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_player.clear();

	player_t::iterator imageIter = m_playerImage.begin();
	player_t::iterator imageEndIter = m_playerImage.end();
	for (; imageIter != imageEndIter; imageIter++)
	{
		if (*imageIter) { delete* imageIter; *imageIter = nullptr; }
	}
	m_playerImage.clear();

	playerName_t::iterator nameIter = m_pName.begin();
	playerName_t::iterator nameEndIter = m_pName.end();
	for (; nameIter != nameEndIter; nameIter++)
	{
		if (*nameIter) { delete* nameIter; *nameIter = nullptr; }
	}
	m_pName.clear();

	if (m_pExitButton) { delete m_pExitButton; m_pExitButton = nullptr; }
	if (m_pChatBackGround) { delete m_pChatBackGround; m_pChatBackGround = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}
