#include "Client.h"
#include "NameScene.h"
#include "SceneManager.h"
#include "Input.h"

CNameScene::CNameScene() 
	: m_bufferCount(0), m_buttonRect({ 460.0f, 400.0f, 820.0f, 430.0f }), m_nameMAX(8)
{
	
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::LOGIN);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();
	m_pBrush = *pRM->GetBlackBrush();

	m_pBackGround = new CObject(sprite[CResourceManager::LOGIN_BACKGROUND], pBitmap, { 0.0f, 0.0f, 1280.0f, 720.0f });

	m_pLogin = new CObject(sprite[CResourceManager::LOGIN_OBJECT], pBitmap, { 450.0f, 240.0f, 830.0f, 440.0f });

	m_pButton = new CButton(sprite[CResourceManager::LOGIN_BUTTON], pBitmap, m_buttonRect);

	m_pBuffer = new WCHAR[MAX_PATH];
	memset(m_pBuffer, 0, MAX_PATH);

	m_rectangle = { 0.0f, 0.0f };
}

void CNameScene::Start()
{
}

void CNameScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pButton->OnButton(mouse);

	if (key >= 'A' && key <= 'z')
	{
		m_pBuffer[m_bufferCount] = key;
		m_bufferCount++;
		if (m_bufferCount >= m_nameMAX) m_bufferCount = m_nameMAX;
	}
	if (key == VK_BACK)
	{
		--m_bufferCount;
		if(m_bufferCount < 0) m_bufferCount = 0;
		m_pBuffer[m_bufferCount] = 0;
	}

	if (key == VK_RETURN)
	{
		m_pButton->OnButtonDown();
		if (m_bufferCount > 0)
		{
			//CClient::GetInstance()->Send(m_pBuffer, 1); // 변경 필요
			//CResourceManager::GetInstance()->SetName(m_pBuffer);
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

	_pRT->DrawTextW(m_pBuffer, m_nameMAX, *pRM->GetWriteFormat(), D2D1::Rect(565.0f, 330.0f, 820.0f, 430.0f), m_pBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	if (m_pBuffer) { delete[] m_pBuffer; m_pBuffer = nullptr; }
	if (m_pButton) { delete m_pButton; m_pButton = nullptr; }
	if (m_pLogin) { delete m_pLogin; m_pLogin = nullptr; }
	if (m_pBackGround) { delete m_pBackGround; m_pBackGround = nullptr; }
}
