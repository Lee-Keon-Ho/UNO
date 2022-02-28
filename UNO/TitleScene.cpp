#include "TitleScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 50, 50, 300, 200}
#define RECT	{ 177, 61, 241, 101}

typedef CResourceManager::eBitmap bitmap_t;

CTitleScene::CTitleScene() : m_bOnRender(true), m_tick(0)
{

}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Awake()
{
}

void CTitleScene::Start()
{
}

void CTitleScene::Update()
{
	m_tick += 1;
	if (m_tick > 15)
	{
		m_bOnRender = !m_bOnRender;
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
	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 0, 0, 450, 450 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 9, 10, 10, 11 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	if (m_bOnRender)
	{
		int size = sizeof(str) - 1;
		for (int i = 0; i < size; i++)
		{
			if (str[i] - 65 < 0) continue;
			_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
				{ 70.0f + (i * 20), 250.0f, 84.0f + (i * 20), 274.0f }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				pRM->GetRedText(str[i] - 'A').GetRect());
		}
	}

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
}
