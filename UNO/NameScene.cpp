#include "NameScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 350, 350}
#define RECT	{ 6, 61, 166, 205}
#define MAX_X	6
#define MAX_Y	3
#define NAME_MAX 5

typedef CResourceManager::eBitmap bitmap_t;

CNameScene::CNameScene() : m_count(0), m_bOK(0)
{
	
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	m_pRedBrush = *CResourceManager::GetInstance()->GetRedBrush();
	m_rectangle = { 0.0f, 0.0f };
	m_name = new char[5];
	memset(m_name, 0, NAME_MAX);
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
	Sleep(10);
}

void CNameScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	char str[] = { "ENTER NAME" };

	_pRT->BeginDraw();

	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	// enter name
	int size = sizeof(str) - 1;
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 65 < 0) continue;
		_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
			{ 88.0f + (i * 18), 42.0f, 103.0f + (i * 18), 72.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			pRM->GetGreenText(str[i] - 'A').GetRect());
	}

	// spelling
	int index = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (index > 25) break;
			if (m_rectangle.x + m_rectangle.y * 7 == index)
			{
				_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
					{ 53.0f + (35 * x), 102.0f + (40 * y), 68.0f + (35 * x), 132.0f + (40 * y) },
					1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					pRM->GetBlueText(index++).GetRect());
			}
			else
			{
				_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
					{ 53.0f + (35 * x), 102.0f + (40 * y), 68.0f + (35 * x), 132.0f + (40 * y) },
					1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					pRM->GetYellowText(index++).GetRect());
			}
		}
	}

	// bar
	for (int i = 0; i < 5; i++)
	{
		_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
			{ 88.0f + (35 * i), 296.0f, 103.0f + (35 * i), 304.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			{ 80.0f, 140.0f, 81.0f, 141.0f});
	}

	// Selection name
	for (int i = 0; i < m_count; i++)
	{
		_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
			{ 88.0f + (35 * i), 262.0f, 103.0f + (35 * i), 292.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			pRM->GetBlueText(m_name[i] - 65).GetRect());
	}

	// ok icon
	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::ICON_OK),
		{ 304.0f , 306.0f, 334.0f, 331.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		pRM->GetOKIcon(m_bOK).GetRect()); m_bOK = 0;

	// rectangle
	_pRT->DrawRectangle(
		{51.0f + ( 35 * m_rectangle.x), 100.0f + ( 40 * m_rectangle.y) ,
			70.0f + ( 35 * m_rectangle.x), 134.0f + ( 40 * m_rectangle.y) },
		m_pRedBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
}
