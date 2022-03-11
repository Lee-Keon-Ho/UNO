#include "TitleScene.h"
#include "SceneManager.h"

#define STR_MAX 20

CTitleScene::CTitleScene() : m_bOnRender(true), m_tick(0), m_backGroundRect({ 104, 80, 105, 81 }),
m_logoRect({ 652, 236, 870, 373 })
{

}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	m_sprite = pRM->GetSprite();
	m_pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	m_str = new int[STR_MAX];
	m_target = new targetList_t[MAX];

	// text
	char str[] = { "A KEY START" };
	int size = sizeof(str) - 1;
	int count = 0;
	m_target[TEXT].reserve(size);
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
		m_str[count++] = str[i] - 'A';
		m_target[TEXT].push_back({ 120.0f + (i * 50), 550.0f, 160.0f + (i * 50), 600.0f });
		m_titleSize++;
	}

	m_target[LOGO].push_back({ 100, 30, 670, 430 });
	m_target[BACKGROUND].push_back({ 0, 0, 770, 695 });
}

void CTitleScene::Start()
{
}

void CTitleScene::Update()
{
	m_tick += 1;
	if (m_tick > 15)
	{
		m_bOnRender = !m_bOnRender; // deltaTime
		m_tick = 0;
	}
	if (KEY_DOWN('A'))
	{
		CSceneManager::GetInstance()->ChangeScene(eScene::NAME_SCENE);
	}
}

void CTitleScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	CResourceManager* pRM = CResourceManager::GetInstance();

	char str[] = { "A KEY START" };
	if (!_pRT) return;
	_pRT->BeginDraw();

	// background
	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		m_target[BACKGROUND].at(0), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_backGroundRect);

	// LOGO
	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		m_target[LOGO].at(0), 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_logoRect);

	if (m_bOnRender)
	{
		for (int i = 0; i < m_titleSize; i++)
		{
			m_sprite[CResourceManager::RED].at(m_str[i]).Render(_pRT, m_pBitmap, m_target[TEXT].at(i), 1.0f);
		}
	}

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
	if (m_str) { delete m_str; m_str = nullptr; }
}
