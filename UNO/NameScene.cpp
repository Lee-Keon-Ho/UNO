#include "NameScene.h"
#include "ResourceManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 350, 350}
#define RECT	{ 6, 61, 166, 205}

typedef CResourceManager::eBitmap bitmap_t;

CNameScene::CNameScene()
{
}

CNameScene::~CNameScene()
{
}

void CNameScene::Awake()
{
	m_pRedBrush = *CResourceManager::GetInstance()->GetRedBrush();
	m_target = { 53.0f, 102.0f, 68.0f, 132.0f };
}

void CNameScene::Start()
{
}

void CNameScene::Update()
{
	if (KEY_DOWN(VK_LEFT))
	{
		m_target.left -= 35.0f;
		m_target.right -= 35.0f;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		m_target.left += 35.0f;
		m_target.right += 35.0f;
	}
	if (KEY_DOWN(VK_UP))
	{
		m_target.top -= 40.0f;
		m_target.bottom -= 40.0f;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		m_target.top += 40.0f;
		m_target.bottom += 40.0f;
	}

	if (m_target.left < 53.0f)
	{
		m_target.left = 53.0f;
		m_target.right = 68.0f;
	}
	if (m_target.left > 263.0f)
	{
		m_target.left = 263.0f;
		m_target.right = 278.0f;
	}
	if (m_target.top < 102.0f)
	{
		m_target.top = 102.0f;
		m_target.bottom = 132.0f;
	}
	if (m_target.top > 222.0f)
	{
		m_target.top = 222.0f;
		m_target.bottom = 252.0f;
	}
}

void CNameScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	_pRT->BeginDraw();

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	int index = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (index > 25) break;
			_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
				{ 53.0f + (35 * x), 102.0f + y * 40, 68.0f + (35 * x), 132.0f + y * 40 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				pRM->GetYellowText(index++).GetRect());
		}
	}

	for (int i = 0; i < 5; i++)
	{
		_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
			{ 88.0f + (35 * i), 296.0f, 103.0f + (35 * i), 304.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			{ 80.0f, 140.0f, 81.0f, 141.0f});
	}

	_pRT->DrawRectangle(m_target, m_pRedBrush);

	_pRT->EndDraw();
}

void CNameScene::Destroy()
{
}
