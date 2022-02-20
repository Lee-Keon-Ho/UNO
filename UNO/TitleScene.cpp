#include "TitleScene.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 0, 0, 450, 450}
#define RECT	{ 0, 0, 450, 450}

CTitleScene::CTitleScene()
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
}

void CTitleScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	if (!_pRT) return;
	_pRT->BeginDraw();

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::TITLE),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
}
