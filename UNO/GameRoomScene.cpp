#include "Client.h"
#include "PacketType.h"
#include "GameRoomScene.h"
#include "Input.h"
#include "SceneManager.h"
#include "information.h"
#include "Timer.h"

#define BUFFER_SIZE 100

CGameRoomScene::CGameRoomScene() : 
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

	m_pBackGround = new CObject2D(sprite[CResourceManager::WAITING_ROOM], pBitmap, { 0.0f, 0.0f, 1280.0f, 720.0f });
	m_pChatBackGround = new CObject2D(sprite[CResourceManager::EXIT_BACKGROUND], pExitBitmap, { 0.0f, 486.0f, 353.0f, 686.0f });

	m_pCurrentCard = new CObject2D(sprite[CResourceManager::UNO_CARD], pCardBitmap, { 605.0f, 227.0f, 675.0f, 334.0f });

	m_pExitButton = new CButton(sprite[CResourceManager::WATTING_ROOM_EXIT], pButtonBitmap, { 1179.0f, 686.0f, 1280.0f, 720.0f });
	m_pReadyButton = new CButton(sprite[CResourceManager::READY_BUTTON], pReadyBitmap, { 566.0f, 321.0f, 713.0f, 399.0f });
	m_pStartButton = new CButton(sprite[CResourceManager::START_BUTTON], pReadyBitmap, { 566.0f, 321.0f, 713.0f, 399.0f });

	m_pChatText = new CText({ 10.0f, 693.0f, 343.0f, 720.0f }, fontSize, 0, CText::T_WHITE);
	m_pChatting = new CChatting({ 10.0f, 680.0f, 343.0f, 720.0f }, fontSize, fontSize, CText::T_WHITE);

	m_pPlayerObject = new CPlayerObject();
	m_pCenterCard = new CButton(sprite[CResourceManager::CENTER_CARD], pCardBitmap, { 465.0f, 287.0f, 535.0f, 404.0f });

	m_pUserInfo = CInformation::GetInstance()->GetUserInfo();
	m_pRoomInfo = CInformation::GetInstance()->GetRoomInfo();

	m_chatBuffer = new wchar_t[CHAT_MAX];
	memset(m_chatBuffer, 0, sizeof(wchar_t) * CHAT_MAX);

	//CTimer::GetInstance()->ResetTimer();

	m_pUserInfo = pInformation->GetUserInfo();
	m_pRoomInfo = pInformation->GetRoomInfo();

	char buffer[] = "game";
	CClient::GetInstance()->Send(buffer, CS_PT_ROOMSTATE);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (wcsncmp(m_pUserInfo[i].name, pInformation->GetName(), wcslen(pInformation->GetName())) == 0)
		{
			m_MyNumber = m_pUserInfo[i].number;
			if (m_pUserInfo[i].boss)
			{
				m_bBoss = true;
				m_bReady = true;
				m_pCurrentButton = m_pStartButton;
			}
			else
			{
				m_bBoss = false;
				m_bReady = false;
				m_pCurrentButton = m_pReadyButton;
			}
			break;
		}
	}
}

void CGameRoomScene::Start()
{
}

void CGameRoomScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	//CTimer* pTimer = CTimer::GetInstance();
	CInformation* pInformation = CInformation::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	// 2022-05-24 수정
	char buffer[] = "game";
	CClient::GetInstance()->Send(buffer, CS_PT_ROOMSTATE);
	m_pUserInfo = pInformation->GetUserInfo();
	m_pRoomInfo = pInformation->GetRoomInfo();
	/*if (pTimer->GetTime() >= 1.0f)
	{
		pTimer->ResetTimer();
	}*/
	if (m_pRoomInfo->victory)
	{
		if (CTimer::GetInstance()->GetTime() > 5)
		{
			char buffer[] = "victory";
			CClient::GetInstance()->Send(buffer, CS_PT_VICTORY);
		}
	}
	m_pExitButton->ButtonPosition(mouse);

	if (key == VK_LBUTTON)
	{
		if (m_pRoomInfo->state)
		{
			if (m_bBoss)
			{
				if (m_bStart)
				{
					if (m_pCurrentButton->OnButton(mouse) && m_pRoomInfo->playerCount > 1)
					{
						char buffer[] = "start";
						CClient::GetInstance()->Send(buffer, CS_PT_START);
					}
				}
			}
			else
			{
				if (m_pCurrentButton->OnButton(mouse))
				{
					m_bReady = !m_bReady;
					char buffer[BUFFER_SIZE];
					char* tempBuffer = buffer;
					*(unsigned short*)tempBuffer = m_bReady;
					CClient::GetInstance()->Send(buffer, CS_PT_READY);
				}
			}

			if (m_pExitButton->OnButton(mouse))
			{
				char buffer[] = "destroy";
				m_pExitButton->OnButtonUp();
				CClient::GetInstance()->Send(buffer, CS_PT_OUTROOM);
			}
			m_bChatting = false;
		}
		else if(!m_pRoomInfo->victory) // 2022-05-24 수정
		{
			if (m_pUserInfo[m_MyNumber - 1].turn)
			{
				if (m_pCenterCard->OnButton(mouse))
				{
					char buffer[] = "take";
					CClient::GetInstance()->Send(buffer, CS_PT_TAKECARD);
				}
			}
		}
	}

	if (key == VK_RETURN)
	{
		m_bChatting = true;
	}

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
	}
	
	for (int i = 0; i < m_pRoomInfo->playerCount; i++)
	{
		if (wcsncmp(m_pUserInfo[i].name, pInformation->GetName(), wcslen(pInformation->GetName())) == 0)
		{
			if (m_pUserInfo[i].boss)
			{
				m_bBoss = true;
				m_pCurrentButton = m_pStartButton;
			}
		}
		if (m_pUserInfo[i].number != 0)
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

	m_pPlayerObject->Update(&m_pUserInfo[m_MyNumber - 1], m_pRoomInfo, mouse, key);
}

void CGameRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);
	
	if (!m_pRoomInfo->state)
	{
		m_pCurrentCard->Render(_pRT, CInformation::GetInstance()->GetCurrentCard(), 1.0f);
		m_pCenterCard->Render(_pRT, 0, 1.0f);
	}

	m_pPlayerObject->Render(_pRT, m_pUserInfo, m_pRoomInfo->playerCount, m_MyNumber);
	
	m_pChatBackGround->Render(_pRT, 0.3f);

	if (m_bChatting)
	{
		m_pChatText->Render(_pRT, m_chatBuffer);
	}

	// START or READY
	if (m_pRoomInfo->playerCount > 1 && m_pRoomInfo->state)
	{
		if (m_bBoss)
		{
			m_pCurrentButton->Render(_pRT, !m_bStart, 1.0f);
		}
		else m_pCurrentButton->Render(_pRT, 1.0f);
	}

	m_pChatting->Render(_pRT);

	m_pExitButton->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CGameRoomScene::Destroy()
{
	memset(m_chatBuffer, 0, 32);
	CInformation::GetInstance()->ReSetChatting();

	if (m_chatBuffer) { delete m_chatBuffer; m_chatBuffer = nullptr; }
	if (m_pPlayerObject) { delete m_pPlayerObject; m_pPlayerObject = nullptr; }
	if (m_pChatting) { delete m_pChatting; m_pChatting = nullptr; }
	if (m_pStartButton) { delete m_pStartButton; m_pStartButton = nullptr; }
	if (m_pReadyButton) { delete m_pReadyButton; m_pReadyButton = nullptr; }
	if (m_pExitButton) { delete m_pExitButton; m_pExitButton = nullptr; }
	if (m_pCurrentCard) { delete m_pCurrentCard; m_pCurrentCard = nullptr; }
	if (m_pChatBackGround) { delete m_pChatBackGround; m_pChatBackGround = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}