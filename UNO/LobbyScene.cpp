#include "Client.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "information.h"
#include "Timer.h"
#include <ctime>
#include <string>

CLobbyScene::CLobbyScene()
	: m_backGroundRect({ 0.0f, 0.0f, 1280.0f, 720.0f }), m_createButtonRect({ 390.0f, 226.0f, 562.0f, 299.0f }),
	m_quickButtonRect({ 562.0f, 226.0f, 732.0f, 299.0f }), m_chooseButtonRect({ 732.0f, 226.0f, 904.0f, 299.0f }),
	m_exitButtonRect({ 1160.0f, 665.0f, 1260.0f, 705.f }), m_peopleIconRect({ 980.0f, 85.0f, 1050.0f, 155.0f }),
	m_myNameTextRect({ 1070.0f, 100.0f, 1250.0f, 200.0f }), m_userListRect({ 920.0f, 270.0f, 1250.0f, 300.0f }),
	m_exitOkButtonRect({421.0f, 250.0f, 858.0f, 469.0f}),
	m_pontSize1(30), m_pontSize2(15), m_textHeight(25), m_bOnExit(false)
{
}

CLobbyScene::~CLobbyScene()
{
}

void CLobbyScene::Awake()
{
	srand((unsigned int)time(NULL));
	m_num = rand() % 5;

	HRESULT hr;
	const WCHAR font[] = L"Consolas";

	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pLobbyBitmap = pRM->GetBitmap(bitmap_t::LOBBY);
	ID2D1Bitmap* pButtonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	ID2D1Bitmap* pCharcterBitmap = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pExitBitmap = pRM->GetBitmap(bitmap_t::EXIT);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pMyNameText = new CText(CInformation::GetInstance()->GetName() , m_myNameTextRect, m_pontSize1);

	m_pUserListText = new CText(m_userListRect, m_pontSize2, m_textHeight);

	m_pBackGround = new CObject(sprite[CResourceManager::LOBBY_BACKGROUND], pLobbyBitmap, m_backGroundRect);

	m_pExitBackGround = new CObject(sprite[CResourceManager::EXIT_BACKGROUND], pExitBitmap, m_backGroundRect);

	m_button.reserve(LB_BUTTON_MAX);
	m_button.push_back(new CButton(sprite[CResourceManager::CREATE_BUTTON], pButtonBitmap, m_createButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::QUICK_BUTTON], pButtonBitmap, m_quickButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::CHOOSE_BUTTON], pButtonBitmap, m_chooseButtonRect));
	m_button.push_back(new CButton(sprite[CResourceManager::LOBYY_EXIT_BUTTON], pButtonBitmap, m_exitButtonRect));

	m_pExitOkButton = new CButton(sprite[CResourceManager::EXIT_BUTTON_OK], pExitBitmap, m_exitOkButtonRect);
	m_pExitNoButton = new CButton(sprite[CResourceManager::EXIT_BUTTON_NO], pExitBitmap, m_exitOkButtonRect);

	m_pCharacter = new CObject(sprite[CResourceManager::CHARCTER_ICON], pCharcterBitmap, m_peopleIconRect);

	m_userList = CInformation::GetInstance()->GetUserList();
	m_pName = CInformation::GetInstance()->GetName();
}

void CLobbyScene::Start()
{
}

void CLobbyScene::Update()
{
	CTimer* pTimer = CTimer::GetInstance();
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	for (int i = 0; i < LB_BUTTON_MAX; i++)
	{
		m_button[i]->OnButtonUp();
	}
	
	m_pExitOkButton->OnButtonUp();
	m_pExitNoButton->OnButtonUp();

	if (m_bOnExit)
	{
		if (key == VK_LBUTTON)
		{
			if (m_pExitOkButton->OnButton(mouse));
			if (m_pExitNoButton->OnButton(mouse)) m_bOnExit = false;
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
						CSceneManager::GetInstance()->ChangeScene(eScene::WAITING_SCENE);
						break;
					case LB_EXIT:
						m_bOnExit = true;
						break;
					}
				}
			}
		}
	}

	if (pTimer->GetTime() == 10)
	{
		char buffer[] = "UserList";
		CClient::GetInstance()->Send(buffer, 3);
		pTimer->ResetTimer();
	}
}

void CLobbyScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	// background
	m_pBackGround->Render(_pRT, 1.0f);

	for (int i = 0; i < LB_BUTTON_MAX; i++)
	{
		m_button[i]->Render(_pRT, 1.0f);
	}

	m_pCharacter->Render(_pRT, m_num, 1.0f);

	m_pMyNameText->Render(_pRT);

	m_pUserListText->Render(_pRT, *m_userList);
	
	if (m_bOnExit)
	{
		m_pExitBackGround->Render(_pRT, 0.5f);
		m_pExitNoButton->Render(_pRT, 1.0f);
		m_pExitOkButton->Render(_pRT, 1.0f);
	}

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
	if (m_pCharacter) { delete m_pCharacter; m_pCharacter = nullptr; }
	
	Button_t::iterator iter = m_button.begin();
	for (; iter != m_button.end(); iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_button.clear();

	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
	if (m_pMyNameText) { delete m_pMyNameText; m_pMyNameText = nullptr; }
	if (m_pUserListText) { delete m_pUserListText; m_pUserListText = nullptr; }
}
