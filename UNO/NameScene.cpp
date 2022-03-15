#include "Client.h"
#include "NameScene.h"
#include "SceneManager.h"

CNameScene::CNameScene() 
	: m_bufferCount(0), m_bOK(0), m_spellingSize(26),
	m_widthMax(7), m_heightMax(4), m_nameSize(5), m_currentSpelling(0),
	m_titleSize(0), m_rectangle({0.0f, 0.0f}), m_barRect({200.0f, 350.0f, 201.0f, 351.0f}),
	m_okRect({ 670 , 600, 740, 670 })
{
	
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	ID2D1Bitmap* pBitmapOK = pRM->GetBitmap(bitmap_t::ICON_OK);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();
	
	//background
	m_pBord = new CObject(sprite[CResourceManager::BORD], pBitmap);
	m_pBord->SetTarget({ 0, 0, 770, 695 });

	//spelling
	m_pYellowSpelling = new CObject(sprite[CResourceManager::YELLOW], pBitmap);
	m_pBlueSpelling = new CObject(sprite[CResourceManager::BLUE], pBitmap);
	int count = 0;
	for (int y = 0; y < m_heightMax; y++)
	{
		for (int x = 0; x < m_widthMax; x++)
		{
			if (++count > m_spellingSize) break;
			m_pYellowSpelling->SetTarget({ 150.0f + (80 * x), 170.0f + (80 * y), 190.0f + (80 * x), 230.0f + (80 * y) });
			m_pBlueSpelling->SetTarget({ 150.0f + (80 * x), 170.0f + (80 * y), 190.0f + (80 * x), 230.0f + (80 * y) });
		}
	}

	// title
	m_pTitle = new CObject(sprite[CResourceManager::GREEN], pBitmap);
	char str[] = { "ENTER NAME" };
	int size = sizeof(str) - 1;
	m_pTextArr = new int[size];
	count = 0;
	//m_title = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
		m_pTextArr[count++] = str[i] - 'A';
		m_pTitle->SetTarget({ 190.0f + (i * 40), 90.0f, 230.0f + (i * 40), 150.0f });
	}

	//bar
	m_pBar = new CObject(new CSprite(m_barRect), pBitmap);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_pBar->SetTarget({ 150.0f + (80 * i), 585, 190.0f + (80 * i), 600.0f });
	}

	//select name
	m_pName = new CObject(sprite[CResourceManager::BLUE], pBitmap);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_pName->SetTarget({ 150.0f + (80 * i), 490, 190.0f + (80 * i), 570 });
	}

	//OK icon
	m_pOk = new CObject(sprite[CResourceManager::OK], pBitmapOK);
	m_pOk->SetTarget(m_okRect);
	m_pOk->SetTarget(m_okRect);

	m_pNameArr = new int[m_nameSize];

	m_pBuffer = new char[MAX_PATH];
	memset(m_pBuffer, 0, MAX_PATH);

	m_rectangle = { 0.0f, 0.0f };
}

void CNameScene::Start()
{
}

void CNameScene::Update()
{
	if (KEY_DOWN(VK_LEFT)) m_rectangle.x -= 1;
	if (KEY_DOWN(VK_RIGHT))	m_rectangle.x += 1;
	if (KEY_DOWN(VK_UP)) m_rectangle.y -= 1;
	if (KEY_DOWN(VK_DOWN)) m_rectangle.y += 1;

	if (KEY_DOWN(VK_RETURN))
	{
		m_bOK = 1;
		if (strlen(m_pBuffer) == m_nameSize)
		{
			CClient::GetInstance()->NickNameSend(m_pBuffer);
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}

	if (KEY_DOWN('A'))
	{
		if (m_bufferCount >= m_nameSize) m_bufferCount = m_nameSize - 1;
		m_pBuffer[m_bufferCount] = 'A' + m_rectangle.x + m_rectangle.y * m_widthMax;
		m_pNameArr[m_bufferCount] = m_rectangle.x + m_rectangle.y * m_widthMax;
		m_bufferCount++;
	}
	if (KEY_DOWN('S'))
	{
		m_pBuffer[m_bufferCount] = 0;
		m_bufferCount--;
		if (m_bufferCount < 0) m_bufferCount = 0;
	}

	if (m_rectangle.x < 0) m_rectangle.x = 0;
	if (m_rectangle.x > m_widthMax - 1) m_rectangle.x = m_widthMax - 1;
	if (m_rectangle.y < 0) m_rectangle.y = 0;
	if (m_rectangle.y > m_heightMax - 1) m_rectangle.y = m_heightMax - 1;

	if (m_rectangle.y == m_heightMax - 1)
	{
		if (m_rectangle.x > m_widthMax - 3)
		{
			m_rectangle.x = m_widthMax - 3;
		}
	}

	m_currentSpelling = m_rectangle.x + m_rectangle.y * m_widthMax;
}

void CNameScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	char str[] = { "ENTER NAME" };

	_pRT->BeginDraw();

	//background
	m_pBord->Render(_pRT, 1.0f);

	// title (enter name)
	m_pTitle->Render(_pRT, m_pTextArr, 1.0f);

	// spelling
	m_pYellowSpelling->Render(_pRT, 1.0f);
	m_pBlueSpelling->Render(_pRT, m_currentSpelling, 1.0f);

	// bar
	m_pBar->Render(_pRT);

	// Selection name
	m_pName->Render(_pRT, m_pNameArr, m_bufferCount, 1.0f);

	// ok icon
	m_pOk->Render(_pRT, m_bOK, 1.0f);
	m_bOK = 0;

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	if (m_pBuffer) { delete[] m_pBuffer; m_pBuffer = nullptr; }
	if (m_pNameArr) { delete[] m_pNameArr; m_pNameArr = nullptr; }
	if (m_pOk) { delete m_pOk; m_pOk = nullptr; }
	if (m_pName) { delete m_pName; m_pName = nullptr; }
	if (m_pBar) { delete m_pBar; m_pBar = nullptr; }
	if (m_pTitle) { delete m_pTitle; m_pTitle = nullptr; }
	if (m_pTextArr) { delete[] m_pTextArr; m_pTextArr = nullptr; }
	if (m_pBlueSpelling) { delete m_pBlueSpelling; m_pBlueSpelling = nullptr; }
	if (m_pYellowSpelling) { delete m_pYellowSpelling; m_pYellowSpelling = nullptr; }
	if (m_pBord) { delete m_pBord; m_pBord = nullptr; }
}
