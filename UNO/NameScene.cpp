#include "Client.h"
#include "NameScene.h"
#include "SceneManager.h"

CNameScene::CNameScene() : m_bufferCount(0), m_bOK(0), m_spellingSize(26),
m_widthMax(7), m_heightMax(4), m_nameSize(5), m_currentSpelling(0),
m_titleSize(0), m_rectangle({0.0f, 0.0f}), m_barRect({200.0f, 350.0f, 201.0f, 351.0f})
{
	
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	m_target = new targetList_t[MAX];
	m_pRedBrush = *pRM->GetRedBrush();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	m_pOkBitmap = pRM->GetBitmap(bitmap_t::ICON_OK);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();
	
	//background
	m_bord = new CObject(sprite[CResourceManager::BORD], pBitmap);
	m_bord->SetTarget({ 0, 0, 770, 695 });

	//spelling
	m_yellowSpelling = new CObject(sprite[CResourceManager::YELLOW], pBitmap);
	m_blueSpelling = new CObject(sprite[CResourceManager::BLUE], pBitmap);
	int count = 0;
	for (int y = 0; y < m_heightMax; y++)
	{
		for (int x = 0; x < m_widthMax; x++)
		{
			if (++count > m_spellingSize) break;
			m_yellowSpelling->SetTarget({ 150.0f + (80 * x), 170.0f + (80 * y), 190.0f + (80 * x), 230.0f + (80 * y) });
			m_blueSpelling->SetTarget({ 150.0f + (80 * x), 170.0f + (80 * y), 190.0f + (80 * x), 230.0f + (80 * y) });
		}
	}

	// title
	m_title = new CObject(sprite[CResourceManager::GREEN], pBitmap);
	char str[] = { "ENTER NAME" };
	int size = sizeof(str) - 1;
	count = 0;
	//m_title = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
	//	m_title[count++] = str[i] - 'A';
		m_title->SetTarget({ 190.0f + (i * 40), 90.0f, 230.0f + (i * 40), 150.0f });
	}

	//bar
	m_bar = new CObject(new CSprite(m_barRect), pBitmap);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_bar->SetTarget({ 150.0f + (80 * i), 585, 190.0f + (80 * i), 600.0f });
	}

	//select name
	m_name = new CObject(sprite[CResourceManager::BLUE], pBitmap);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_name->SetTarget({ 150.0f + (80 * i), 490, 190.0f + (80 * i), 570 });
	}

	//OK icon
	m_ok = new CObject(sprite[CResourceManager::OK], pRM->GetBitmap(bitmap_t::ICON_OK));
	m_ok->SetTarget({ 670 , 600, 740, 670 });
	m_ok->SetTarget({ 670 , 600, 740, 670 });


	m_rectangle = { 0.0f, 0.0f };
	m_pBuffer = new char[MAX_PATH];
	memset(m_pBuffer, 0, MAX_PATH);
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
	m_bord->Render(_pRT, 1.0f);

	// title (enter name)
	for (int i = 0; i < m_titleSize; i++)
	{
		//m_sprite[CResourceManager::GREEN].at(m_title[i]).Render(_pRT, m_pBitmap, m_target[TITLE].at(i), 1.0f);
	}

	// spelling
	m_yellowSpelling->Render(_pRT, 1.0f);
	m_blueSpelling->Render(_pRT, m_currentSpelling, 1.0f);

	// bar
	m_bar->Render(_pRT, 0, 1.0f);

	// Selection name
	for (int i = 0; i < m_bufferCount; i++)
	{
		//m_name->Render(_pRT, m_pBuffer[i] - 'A', 1.0f);
	}

	// ok icon
	m_ok->Render(_pRT, m_bOK, 1.0f);
	m_bOK = 0;

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	if (m_title) { delete[] m_title; m_title = nullptr; }
	if (m_pBuffer) { delete[] m_pBuffer; m_pBuffer = nullptr; }
}
