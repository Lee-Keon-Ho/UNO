#include "Client.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "PacketType.h"
#include "Input.h"
#include <ctime>
#include <string>

#define ROOM_NAME_MAX_SIZE 128
#define BUFFER_SIZE 1000

CLobbyScene::CLobbyScene()
	: m_backGroundRect({ 0.0f, 0.0f, 1280.0f, 720.0f }), m_createButtonRect({ 386.0f, 230.0f, 558.0f, 303.0f }),
	m_quickButtonRect({ 558.0f, 230.0f, 728.0f, 303.0f }), m_chooseButtonRect({ 728.0f, 230.0f, 900.0f, 303.0f }),
	m_exitButtonRect({ 1160.0f, 665.0f, 1260.0f, 705.f }), m_peopleIconRect({ 980.0f, 85.0f, 1050.0f, 155.0f }),
	m_myNameTextRect({ 1070.0f, 100.0f, 1250.0f, 200.0f }), m_userListRect({ 920.0f, 270.0f, 1250.0f, 300.0f }),
	m_exitTextObject({ 421.0f, 250.0f, 858.0f, 405.0f }), m_exitOkButtonRect({ 639.0f, 405.0f, 858.0f, 469.0f }),
	m_exitNoButtonRect({ 420.0f, 405.0f, 639.0f, 469.0f }), m_createRoomRect({ 426.0f, 250.0f, 854.0f, 470.f }),
	m_createOkButtonRect({ 588.0f,412.0f, 692.0f, 452.0f }), m_createNoButtonRect({ 820.0f, 264.0f, 836.0f, 280.0f }),
	m_createRoomTextRect({ 538.0f, 331.0f, 884.0f, 370.f }), m_roomListRect({350.0f, 347.0f, 700.0f, 500.0f}),
	m_pontSize1(30), m_pontSize2(15), m_textHeight(25), m_bOnExit(false), m_bOnCreate(false),
	m_roomNameCount(0), m_roomNameMax(24), m_bOnRoom(false), m_roomButtonNum(0), m_roomCount(0),
	m_roomButtonMAX(8)
{
	srand((unsigned int)time(NULL));
	m_userImageNum = rand() % 5;
}

CLobbyScene::~CLobbyScene()
{
	Destroy();
}

void CLobbyScene::Awake()
{
	CInformation::GetInstance()->SetImage(m_userImageNum);

	HRESULT hr;
	const WCHAR font[] = L"Consolas";

	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pLobbyBitmap = pRM->GetBitmap(bitmap_t::LOBBY);
	ID2D1Bitmap* pButtonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	ID2D1Bitmap* pCharcterBitmap = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pExitBitmap = pRM->GetBitmap(bitmap_t::EXIT);
	ID2D1Bitmap* pCreateRoomBitmap = pRM->GetBitmap(bitmap_t::CREATE);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pRoomList = new CRoom(m_roomListRect, m_pontSize2, 46, CText::T_BLACK);

	m_pMyNameText = new CText(CInformation::GetInstance()->GetName() , m_myNameTextRect, m_pontSize1, CText::T_BLACK);

	m_pUserList = new CUser(m_userListRect, m_pontSize2, m_textHeight, CText::T_BLACK);

	m_pCreateRoomText = new CText(m_createRoomTextRect, m_pontSize2, 0, CText::T_BLACK);

	m_pBackGround = new CObject2D(sprite[CResourceManager::LOBBY_BACKGROUND], pLobbyBitmap, m_backGroundRect);

	m_pExitBackGround = new CObject2D(sprite[CResourceManager::EXIT_BACKGROUND], pExitBitmap, m_backGroundRect);
	m_pExitTextObject = new CObject2D(sprite[CResourceManager::EXIT_TEXT_OBJECT], pExitBitmap, m_exitTextObject);
	
	m_pCreateRoomObject = new CObject2D(sprite[CResourceManager::CREATE_ROOM], pCreateRoomBitmap, m_createRoomRect);

	m_button.reserve(LB_BUTTON_MAX);
	m_button.push_back(new CButton(sprite[CResourceManager::CREATE_BUTTON], pButtonBitmap, m_createButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::QUICK_BUTTON], pButtonBitmap, m_quickButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::CHOOSE_BUTTON], pButtonBitmap, m_chooseButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::LOBYY_EXIT_BUTTON], pButtonBitmap, m_exitButtonRect));

	m_roomListButton.reserve(m_roomButtonMAX);
	for (int i = 0; i < m_roomButtonMAX; i++)
	{
		m_roomListButton.push_back(new CButton(sprite[CResourceManager::ROOM_LIST_BUTTON], pExitBitmap, { 161.0f, 334.0f + (47 * i), 882.0f, 380.0f + (47 * i) }));
	}

	m_pExitOkButton = new CButton(sprite[CResourceManager::EXIT_BUTTON_OK], pButtonBitmap, m_exitOkButtonRect);
	m_pExitNoButton = new CButton(sprite[CResourceManager::EXIT_BUTTON_NO], pButtonBitmap, m_exitNoButtonRect);

	m_pCreateOkButton = new CButton(sprite[CResourceManager::CREATE_BUTTON_OK], pButtonBitmap, m_createOkButtonRect);
	m_pCreateNoButton = new CButton(sprite[CResourceManager::CREATE_BUTTON_NO], pButtonBitmap, m_createNoButtonRect);

	m_pCharacter = new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pCharcterBitmap, m_peopleIconRect);

	m_pRoomName = new wchar_t[ROOM_NAME_MAX_SIZE];
	memset(m_pRoomName, 0, sizeof(wchar_t) * ROOM_NAME_MAX_SIZE);

	m_pRoomList->SetList();
	m_pUserList->SetList();

	m_roomCount = m_pRoomList->GetSize();

	//CTimer::GetInstance()->ResetTimer(); // 타이머 초기화
}

void CLobbyScene::Start()
{
}

void CLobbyScene::Update()
{
	//CTimer* pTimer = CTimer::GetInstance();
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	// 2022-05-24
	char buffer[] = "List";
	CClient::GetInstance()->Send(buffer, CS_PT_USERLIST);
	CClient::GetInstance()->Send(buffer, CS_PT_ROOMLIST);
	m_pUserList->SetList();
	m_pRoomList->SetList();
	m_roomCount = m_pRoomList->GetSize();
	/*if (pTimer->GetTime() >= 1.0f)
	{
		pTimer->ResetTimer();
	}*/

	for (int i = 0; i < LB_BUTTON_MAX; i++)
	{
		m_button[i]->OnButtonUp();
	}
	
	m_pExitOkButton->OnButtonUp();
	m_pExitNoButton->OnButtonUp();
	m_pCreateOkButton->OnButtonUp();

	if (m_bOnExit)
	{
		if (m_pExitNoButton->OnButton(mouse))
		{
			if (key == VK_LBUTTON)
			{
				m_pExitNoButton->OnButtonDown();
				m_bOnExit = false;
			}
		}
		if (m_pExitOkButton->OnButton(mouse))
		{
			if (key == VK_LBUTTON)
			{
				char buffer[] = "LogOut";
				m_pExitOkButton->OnButtonDown();
				CClient::GetInstance()->Send(buffer, CS_PT_LOGOUT);
				PostQuitMessage(0);
			}
		}
	}
	else if (m_bOnCreate)
	{
		if (key >= 'A' && key <= 'z')
		{
			m_pRoomName[m_roomNameCount] = key;
			m_roomNameCount++;
			if (m_roomNameCount > m_roomNameMax) m_roomNameCount = m_roomNameMax;
		}
		if (key == VK_BACK)
		{
			m_pRoomName[m_roomNameCount] = 0;
			--m_roomNameCount;
			if (m_roomNameCount < 0) m_roomNameCount = 0;
		}
		if (key == VK_RETURN)
		{
			m_pCreateOkButton->OnButtonDown();
			if (m_roomNameCount >= 4)
			{
				char sendBuffer[BUFFER_SIZE];
				char* tempBuffer = sendBuffer;
				*(unsigned short*)tempBuffer = m_userImageNum;
				tempBuffer += sizeof(unsigned short);
				memcpy(tempBuffer, m_pRoomName, ROOM_NAME_MAX_SIZE);
				CClient::GetInstance()->Send(sendBuffer, CS_PT_CREATEROOM);
			}
		}
		if (key == VK_LBUTTON)
		{
			if (m_pCreateOkButton->OnButton(mouse))
			{
				m_pCreateOkButton->OnButtonDown();
				if (m_roomNameCount >= 4)
				{
					char sendBuffer[BUFFER_SIZE];
					char* tempBuffer = sendBuffer;
					*(unsigned short*)tempBuffer = m_userImageNum;
					tempBuffer += sizeof(unsigned short);
					memcpy(tempBuffer, m_pRoomName, ROOM_NAME_MAX_SIZE);
					CClient::GetInstance()->Send(sendBuffer, CS_PT_CREATEROOM);
				}
			}
			if (m_pCreateNoButton->OnButton(mouse))
			{
				memset(m_pRoomName, 0, sizeof(wchar_t) * ROOM_NAME_MAX_SIZE);
				m_bOnCreate = false;
			}
		}
		if (key == VK_END)
		{
			memset(m_pRoomName, 0, sizeof(wchar_t) * ROOM_NAME_MAX_SIZE);
			m_bOnCreate = false;
		}
	}
	else
	{
		if (key == VK_LBUTTON)
		{
			for (int i = 0; i < LB_BUTTON_MAX; i++)
			{
				if (m_button[i]->OnButton(mouse))
				{
					switch (i)
					{
					case LB_CREATE:
						m_bOnCreate = true;
						break;
					case LB_EXIT:
						m_bOnExit = true;
						break;
					case LB_CHOOSE:
						if (m_bOnRoom)
						{							
							char sendBuffer[BUFFER_SIZE];
							char* tempBuffer = sendBuffer;
							*(unsigned short*)tempBuffer = m_roomButtonNum + 1;
							tempBuffer += sizeof(unsigned short);
							*(unsigned short*)tempBuffer = m_userImageNum;
							CClient::GetInstance()->Send(sendBuffer, CS_PT_INROOM);

						}
						break;
					case LB_QUICK:
						char buffer[] = "quick";
						CClient::GetInstance()->Send(buffer, CS_PT_QUICKROOM);
						break;
					}
				}
			}

			for (int i = 0; i < m_roomCount; i++)
			{
				if (m_roomListButton[i]->OnButton(mouse))
				{
					m_roomButtonNum = i;
					m_bOnRoom = true;
					break;
				}
				else
				{
					m_bOnRoom = false;
				}
			}
		}
	}
}

void CLobbyScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);

	for (int i = 0; i < LB_BUTTON_MAX; i++)
	{
		m_button[i]->Render(_pRT, 1.0f);
	}

	m_pCharacter->Render(_pRT, m_userImageNum, 1.0f);

	m_pMyNameText->Render(_pRT);
	
	m_pUserList->Render(_pRT);
	m_pRoomList->Render(_pRT);

	if (m_bOnExit)
	{
		m_pExitBackGround->Render(_pRT, 0.5f);
		m_pExitTextObject->Render(_pRT, 1.0f);
		m_pExitNoButton->Render(_pRT, 1.0f);
		m_pExitOkButton->Render(_pRT, 1.0f);
	}
	if (m_bOnCreate)
	{
		m_pExitBackGround->Render(_pRT, 0.5f);
		m_pCreateRoomObject->Render(_pRT, 1.0f);
		m_pCreateOkButton->Render(_pRT, 1.0f);
		m_pCreateNoButton->Render(_pRT, 1.0f);
		m_pCreateRoomText->Render(_pRT, m_pRoomName);
	}

	if (m_bOnRoom)
	{
		m_roomListButton[m_roomButtonNum]->Render(_pRT, 0.5f);
	}

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
	if (m_pCharacter) { delete m_pCharacter; m_pCharacter = nullptr; }
	if (m_pExitNoButton) { delete m_pExitNoButton; m_pExitNoButton = nullptr; }
	if (m_pExitOkButton) { delete m_pExitOkButton; m_pExitOkButton = nullptr; }
	if (m_pCreateRoomText) { delete m_pCreateRoomText; m_pCreateRoomText = nullptr; }
	if (m_pRoomName) { delete m_pRoomName; m_pRoomName = nullptr; }

	Button_t::iterator iter = m_button.begin();
	for (; iter != m_button.end(); iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_button.clear();

	if (m_pCreateRoomObject) { delete m_pCreateRoomObject; m_pCreateRoomObject = nullptr; }
	if (m_pExitTextObject) { delete m_pExitTextObject; m_pExitTextObject = nullptr; }
	if (m_pExitBackGround) { delete m_pExitBackGround; m_pExitBackGround = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
	if (m_pCreateRoomText) { delete m_pCreateRoomText; m_pCreateRoomText = nullptr; }
	if (m_pMyNameText) { delete m_pMyNameText; m_pMyNameText = nullptr; }
	if (m_pRoomList) { delete m_pRoomList; m_pRoomList = nullptr; }
	if (m_pUserList) { delete m_pUserList; m_pUserList = nullptr; }

	m_bOnCreate = false;
	m_bOnExit = false;
	m_roomNameCount = 0;
}