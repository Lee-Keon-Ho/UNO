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
	const WCHAR font[] = L"Consolas";
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

	m_pName = new WCHAR[MAX_PATH];
	m_pBuffer = new char[MAX_PATH];
	memset(m_pName, 0, MAX_PATH);
	memset(m_pBuffer, 0, MAX_PATH);
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
		m_pBuffer[m_bufferCount] = key;
		m_pName[m_bufferCount] = key;
		m_bufferCount++;
		if (m_bufferCount >= m_nameMAX) m_bufferCount = m_nameMAX;
	}
	if (key == VK_BACK)
	{
		--m_bufferCount;
		if(m_bufferCount < 0) m_bufferCount = 0;
		m_pBuffer[m_bufferCount] = 0;
		m_pName[m_bufferCount] = 0;
	}

	if (key == VK_RETURN)
	{
		m_pButton->OnButtonDown();
		if (m_bufferCount > 3)
		{
			CClient::GetInstance()->Send(m_pBuffer, 1); // 변경 필요
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

	_pRT->DrawTextW(m_pName, m_nameMAX, m_pWriteTextFormat, D2D1::Rect(565.0f, 330.0f, 820.0f, 430.0f), m_pBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	m_bufferCount = 0;
	if (m_pBuffer) { delete[] m_pBuffer; m_pBuffer = nullptr; }
	if (m_pName) { delete[] m_pName; m_pName = nullptr; }
	if (m_pButton) { delete m_pButton; m_pButton = nullptr; }
	if (m_pLogin) { delete m_pLogin; m_pLogin = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}
