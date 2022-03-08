#include "ServerManager.h"
#include "NameScene.h"
#include "SceneManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 350, 350}
#define RECT	{ 6, 61, 166, 205}
#define MAX_X	6
#define MAX_Y	3
#define NAME_MAX 5

CNameScene::CNameScene() : m_count(0), m_bOK(0), m_spellingSize(26),
m_widthMax(7), m_heightMax(4), m_nameSize(5), m_titleSize(0), 
m_barRect({80.0f, 140.0f, 81.0f, 141.0f})
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
	m_pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	m_pOkBitmap = pRM->GetBitmap(bitmap_t::ICON_OK);
	m_sprite = pRM->GetSprite();
	
	//spelling
	m_target[SPELLING].reserve(m_spellingSize);
	int count = 0;
	for (int y = 0; y < m_heightMax; y++)
	{
		for (int x = 0; x < m_widthMax; x++)
		{
			m_target[SPELLING].push_back({ 53.0f + (35 * x), 102.0f + (40 * y), 68.0f + (35 * x), 132.0f + (40 * y) });
		}
	}

	// title
	char str[] = { "ENTER NAME" };
	int size = sizeof(str) - 1;
	m_target[TITLE].reserve(size);
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
		m_target[TITLE].push_back({ 88.0f + (i * 18), 42.0f, 103.0f + (i * 18), 72.0f });
		m_titleSize++;
	}

	//bar
	m_target[BAR].reserve(m_nameSize);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_target[BAR].push_back({ 88.0f + (35 * i), 296.0f, 103.0f + (35 * i), 304.0f });
	}

	//select name
	m_target[NAME].reserve(m_nameSize);
	for (int i = 0; i < m_nameSize; i++)
	{
		m_target[NAME].push_back({ 88.0f + (35 * i), 262.0f, 103.0f + (35 * i), 292.0f });
	}

	//icon
	m_target[OK].reserve(1);
	m_target[OK].push_back({ 304.0f , 306.0f, 334.0f, 331.0f });


	m_rectangle = { 0.0f, 0.0f };
	m_name = new char[40];
	memset(m_name, 0, 40);
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
		if (strlen(m_name) == 5)
		{
			CServerManager::GetInstance()->NickNameSend(m_name);
		}
		CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
	}

	if (KEY_DOWN('A'))
	{
		if (m_count > 4) m_count = 4;
		m_name[m_count] = 'A' + m_rectangle.x + m_rectangle.y * 7;
		m_count++;
	}
	if (KEY_DOWN('S'))
	{
		m_name[m_count] = 0;
		m_count--;
		if (m_count < 0) m_count = 0;
	}

	if (m_rectangle.x < 0) m_rectangle.x = 0;
	if (m_rectangle.x > MAX_X) m_rectangle.x = MAX_X;
	if (m_rectangle.y < 0) m_rectangle.y = 0;
	if (m_rectangle.y > MAX_Y) m_rectangle.y = MAX_Y;

	if (m_rectangle.y == MAX_Y)
	{
		if (m_rectangle.x > 4)
		{
			m_rectangle.x = 4;
		}
	}
}

void CNameScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	char str[] = { "ENTER NAME" };

	_pRT->BeginDraw();

	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	// title (enter name)
	for (int i = 0; i < m_titleSize; i++)
	{
		m_sprite[CResourceManager::GREEN].at(i).Render(_pRT, m_pBitmap, m_target[TITLE].at(i), 1.0f);
	}

	// spelling
	int index = 0;
	for (int i = 0; i < m_spellingSize; i++)
	{
		if (m_rectangle.x + m_rectangle.y * 7 == index)
		{
			m_sprite[CResourceManager::BLUE].at(i).Render(_pRT, m_pBitmap, m_target[SPELLING].at(i), 1.0f);
		}
		else
		{
			m_sprite[CResourceManager::YELLOW].at(i).Render(_pRT, m_pBitmap, m_target[SPELLING].at(i), 1.0f);
		}
		index++;
	}

	// bar
	for (int i = 0; i < 5; i++)
	{
		_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
			m_target[BAR].at(i), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_barRect);
	}

	// Selection name
	for (int i = 0; i < m_count; i++)
	{
		m_sprite[CResourceManager::BLUE].at(m_name[i] - 65).Render(_pRT, m_pBitmap,
			m_target[NAME].at(i), 1.0f);
	}

	// ok icon
	m_sprite[CResourceManager::OK].at(m_bOK).Render(_pRT, m_pOkBitmap, m_target[OK].at(0), 1.0f);

	// rectangle
	_pRT->DrawRectangle(
		{51.0f + ( 35 * m_rectangle.x), 100.0f + ( 40 * m_rectangle.y) ,
			70.0f + ( 35 * m_rectangle.x), 134.0f + ( 40 * m_rectangle.y) },
		m_pRedBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
	if (m_title) { delete[] m_title; m_title = nullptr; }
	if (m_name) { delete[] m_name; m_name = nullptr; }
}
