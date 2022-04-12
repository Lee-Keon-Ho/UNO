#include "Client.h"
#include "NameScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "information.h"

CNameScene::CNameScene() 
	: m_bufferCount(0), m_buttonRect({ 460.0f, 400.0f, 820.0f, 430.0f }), m_nameMAX(8)
{
	
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	HRESULT hr;
	const wchar_t font[] = L"Consolas";
	const FLOAT fontsize = 15;

	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::LOGIN);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	//──────────────────────────────────────────────────────────────────────────────────
	// Text 
	//──────────────────────────────────────────────────────────────────────────────────
	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		font, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontsize, L"en-us", &m_pWriteTextFormat);
	//──────────────────────────────────────────────────────────────────────────────────


	m_pBrush = *pRM->GetBlackBrush();

	m_pBackGround = new CObject(sprite[CResourceManager::LOGIN_BACKGROUND], pBitmap, { 0.0f, 0.0f, 1280.0f, 720.0f });

	m_pLogin = new CObject(sprite[CResourceManager::LOGIN_OBJECT], pBitmap, { 450.0f, 240.0f, 830.0f, 440.0f });

	m_pButton = new CButton(sprite[CResourceManager::LOGIN_BUTTON], pBitmap, m_buttonRect);

	m_pUser = new CUser();

	m_pName = new wchar_t[MAX_PATH];
	memset(m_pName, 0, MAX_PATH);
}

void CNameScene::Start()
{
}

void CNameScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pButton->OnButtonUp();

	if (key >= 'A' && key <= 'z')
	{
		m_pName[m_bufferCount] = key;
		m_bufferCount++;
		if (m_bufferCount >= m_nameMAX) m_bufferCount = m_nameMAX;
	}
	if (key == VK_BACK)
	{
		--m_bufferCount;
		if(m_bufferCount < 0) m_bufferCount = 0;
		m_pName[m_bufferCount] = 0;
	}

	if (key == VK_RETURN)
	{
		m_pButton->OnButton(mouse);
		if (m_bufferCount > 3)
		{
			m_pName[m_bufferCount] = 0;
			m_pUser->SetName(m_pName);
			CClient::GetInstance()->Send(m_pUser, 1); // 수정 : TYPE
			CInformation::GetInstance()->SetName(m_pName);
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}

	if (key == VK_LBUTTON)
	{
		if (m_pButton->OnButton(mouse) && m_bufferCount > 0)
		{
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}
}

void CNameScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);
	m_pLogin->Render(_pRT, 1.0f);
	m_pButton->Render(_pRT, 1.0f);

	// 수정
	_pRT->DrawTextW(m_pName, m_nameMAX, m_pWriteTextFormat, D2D1::Rect(565.0f, 330.0f, 820.0f, 430.0f), m_pBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	m_bufferCount = 0;
	if (m_pName) { delete[] m_pName; m_pName = nullptr; }
	if (m_pUser) { delete m_pUser; m_pUser = nullptr; }
	if (m_pButton) { delete m_pButton; m_pButton = nullptr; }
	if (m_pLogin) { delete m_pLogin; m_pLogin = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}