#include "Client.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "information.h"
#include <ctime>
#include <string>

CLobbyScene::CLobbyScene()
	: m_backGroundRect({ 0.0f, 0.0f, 1280.0f, 720.0f }), m_createButtonRect({ 390.0f, 226.0f, 562.0f, 299.0f }),
	m_quickButtonRect({ 562.0f, 226.0f, 732.0f, 299.0f }), m_chooseButtonRect({ 732.0f, 226.0f, 904.0f, 299.0f }),
	m_exitButtonRect({ 1160.0f, 665.0f, 1260.0f, 705.f }), m_peopleIconRect({ 980.0f, 85.0f, 1050.0f, 155.0f }),
	m_myNameTextRect({ 1070.0f, 100.0f, 1250.0f, 200.0f }), m_userListRect({ 920.0f, 270.0f, 1250.0f, 300.0f })
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
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pMyNameText = new CText(CInformation::GetInstance()->GetName() , m_myNameTextRect, 30);

	m_pUserListText = new CText(m_userListRect, 15, 25);

	m_pName = CInformation::GetInstance()->GetName();

	m_pBackGround = new CObject(sprite[CResourceManager::LOBBY_BACKGROUND], pLobbyBitmap, m_backGroundRect);

	m_pCreateButton = new CButton(sprite[CResourceManager::CREATE_BUTTON], pButtonBitmap, m_createButtonRect);

	m_pQuickButton = new CButton(sprite[CResourceManager::QUICK_BUTTON], pButtonBitmap, m_quickButtonRect);

	m_pChooseButton = new CButton(sprite[CResourceManager::CHOOSE_BUTTON], pButtonBitmap, m_chooseButtonRect);

	m_pExitButton = new CButton(sprite[CResourceManager::EXIT_BUTTON], pButtonBitmap, m_exitButtonRect);

	m_pCharacter = new CObject(sprite[CResourceManager::CHARCTER_ICON], pCharcterBitmap, m_peopleIconRect);
}

void CLobbyScene::Start()
{
}

void CLobbyScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pCreateButton->OnButtonUp();
	m_pQuickButton->OnButtonUp();
	m_pChooseButton->OnButtonUp();
	m_pExitButton->OnButtonUp();
	
	if (key == VK_LBUTTON)
	{
		// 버튼이 늘어나도 신경쓰지 않는 방법이 있다.
		if (m_pCreateButton->OnButton(mouse))
		{

		}
		if (m_pQuickButton->OnButton(mouse))
		{

		}
		if (m_pChooseButton->OnButton(mouse))
		{

		}
		if (m_pExitButton->OnButton(mouse))
		{
			CSceneManager::GetInstance()->ChangeScene(eScene::NAME_SCENE);
		}
	}
}

void CLobbyScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	// background
	m_pBackGround->Render(_pRT, 1.0f);

	m_pCreateButton->Render(_pRT, 1.0f);

	m_pQuickButton->Render(_pRT, 1.0f);

	m_pChooseButton->Render(_pRT, 1.0f);

	m_pExitButton->Render(_pRT, 1.0f);

	m_pCharacter->Render(_pRT, m_num, 1.0f);

	//TEXT class를 따로 만들어서 사용하자
	m_pMyNameText->Render(_pRT);

	// 특정 시간마다 Update에서 새로 갱신 하도록 만들자
	UserList_t temp = CInformation::GetInstance()->GetUserList();
	m_pUserListText->Render(_pRT, temp);
	
	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
	if (m_pCharacter) { delete m_pCharacter; m_pCharacter = nullptr; }
	if (m_pExitButton) { delete m_pExitButton; m_pExitButton = nullptr; }
	if (m_pChooseButton) { delete m_pChooseButton; m_pChooseButton = nullptr; }
	if (m_pQuickButton) { delete m_pQuickButton; m_pQuickButton = nullptr; }
	if (m_pCreateButton) { delete m_pCreateButton; m_pCreateButton = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
	if (m_pMyNameText) { delete m_pMyNameText; m_pMyNameText = nullptr; }
	if (m_pUserListText) { delete m_pUserListText; m_pUserListText = nullptr; }
}
