#include "TitleScene.h"
#include "SceneManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 50, 50, 300, 200}
#define RECT	{ 177, 61, 241, 101}

CTitleScene::CTitleScene() : m_bOnRender(true), m_tick(0)
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
	m_str = new int[20];
	char str[] = { "A KEY START" };
	int size = sizeof(str) - 1;
	int count = 0;
	m_target.reserve(size);
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
		m_str[count++] = str[i] - 'A';
		m_target.push_back({ 70.0f + (i * 20), 250.0f, 84.0f + (i * 20), 274.0f });
		m_titleSize++;
	}
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
		{ 0, 0, 350, 350 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 9, 10, 10, 11 });

	_pRT->DrawBitmap(pRM->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	if (m_bOnRender)
	{
		for (int i = 0; i < m_titleSize; i++)
		{
			m_sprite[CResourceManager::RED].at(m_str[i]).Render(_pRT, m_pBitmap, m_target.at(i), 1.0f);
		}
	}

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
	if (m_str) { delete m_str; m_str = nullptr; }
}
