#include "Client.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "Input.h"

CLobbyScene::CLobbyScene()
	: m_backGroundRect({ 0.0f, 0.0f, 1280.0f, 720.0f }), m_createButtonRect({ 390.0f, 226.0f, 562.0f, 299.0f }),
	m_quickButtonRect({ 562.0f, 226.0f, 732.0f, 299.0f }), m_chooseButtonRect({ 732.0f, 226.0f, 904.0f, 299.0f })
{
}

CLobbyScene::~CLobbyScene()
{
}

void CLobbyScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* plobbyBitmap = pRM->GetBitmap(bitmap_t::LOBBY);
	ID2D1Bitmap* pbuttonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject(sprite[CResourceManager::LOBBY_BACKGROUND], plobbyBitmap, m_backGroundRect);

	m_pCreateButton = new CButton(sprite[CResourceManager::CREATE_BUTTON], pbuttonBitmap, m_createButtonRect);

	m_pQuickButton = new CButton(sprite[CResourceManager::QUICK_BUTTON], pbuttonBitmap, m_quickButtonRect);

	m_pChooseButton = new CButton(sprite[CResourceManager::CHOOSE_BUTTON], pbuttonBitmap, m_chooseButtonRect);
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
	
	if (key == VK_LBUTTON)
	{
		m_pCreateButton->OnButton(mouse);
		m_pQuickButton->OnButton(mouse);
		m_pChooseButton->OnButton(mouse);
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

	_pRT->EndDraw();
}

void CLobbyScene::Destroy()
{
	if (m_pChooseButton) { delete m_pChooseButton; m_pChooseButton = nullptr; }
	if (m_pQuickButton) { delete m_pQuickButton; m_pQuickButton = nullptr; }
	if (m_pCreateButton) { delete m_pCreateButton; m_pCreateButton = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}
