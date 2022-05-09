#include "Client.h"
#include "PacketType.h"
#include "LoginScene.h"
#include "SceneManager.h"
#include "Input.h"
#include "information.h"

CLoginScene::CLoginScene()
	: m_bufferCount(0), m_buttonRect({ 460.0f, 400.0f, 820.0f, 430.0f }), m_nameMAX(8),
	m_nameRect({ 565.0f, 330.0f, 820.0f, 430.0f })
{
	
}

CLoginScene::~CLoginScene()
{
	Destroy();
}

void CLoginScene::Awake()
{
	HRESULT hr;
	const wchar_t font[] = L"Consolas";
	const FLOAT fontsize = 15;

	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::LOGIN);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	// Text 
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		font, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontsize, L"en-us", &m_pWriteTextFormat);
	//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式


	m_pBrush = *pRM->GetBrush(1);

	m_pBackGround = new CObject2D(sprite[CResourceManager::LOGIN_BACKGROUND], pBitmap, { 0.0f, 0.0f, 1280.0f, 720.0f });

	m_pLogin = new CObject2D(sprite[CResourceManager::LOGIN_OBJECT], pBitmap, { 450.0f, 240.0f, 830.0f, 440.0f });

	m_pButton = new CButton(sprite[CResourceManager::LOGIN_BUTTON], pBitmap, m_buttonRect);

	m_pName = new CText(m_nameRect, 15, 0, CText::T_BLACK);

	m_pBuffer = new wchar_t[MAX_PATH];
	memset(m_pBuffer, 0, MAX_PATH);
}

void CLoginScene::Start()
{
}

void CLoginScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pButton->OnButtonUp();

	if (key >= 'A' && key <= 'z')
	{
		m_pBuffer[m_bufferCount] = key;
		m_bufferCount++;
		if (m_bufferCount > m_nameMAX) m_bufferCount = m_nameMAX;
	}
	if (key == VK_BACK)
	{
		--m_bufferCount;
		if (m_bufferCount < 0) m_bufferCount = 0;
		m_pBuffer[m_bufferCount] = 0;
	}

	if (key == VK_RETURN)
	{
		m_pButton->OnButton(mouse);
		if (m_bufferCount > 3)
		{
			m_pBuffer[m_bufferCount] = 0;
			CClient::GetInstance()->Send(m_pBuffer, CS_PT_LOGIN);
			CClient::GetInstance()->Send(m_pBuffer, CS_PT_ROOMLIST);
			CInformation::GetInstance()->SetName(m_pBuffer);
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}

	if (key == VK_LBUTTON)
	{
		if (m_pButton->OnButton(mouse) && m_bufferCount > 0)
		{
			if (m_bufferCount > 3)
			{
				m_pBuffer[m_bufferCount] = 0;
				CClient::GetInstance()->Send(m_pBuffer, CS_PT_LOGIN);
				CClient::GetInstance()->Send(m_pBuffer, CS_PT_ROOMLIST);
				CInformation::GetInstance()->SetName(m_pBuffer);
				CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
			}
		}
	}
}

void CLoginScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);
	m_pLogin->Render(_pRT, 1.0f);
	m_pButton->Render(_pRT, 1.0f);
	m_pName->Render(_pRT, m_pBuffer);

	_pRT->EndDraw();
}

void CLoginScene::Destroy()
{
	m_bufferCount = 0;
	if (m_pBuffer) { delete[] m_pBuffer; m_pBuffer = nullptr; }
	if (m_pName) { delete m_pName; m_pName = nullptr; }
	if (m_pButton) { delete m_pButton; m_pButton = nullptr; }
	if (m_pLogin) { delete m_pLogin; m_pLogin = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}