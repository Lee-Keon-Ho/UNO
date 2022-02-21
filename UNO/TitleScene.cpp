#include "TitleScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define TARGET	{ 50, 50, 300, 200}
#define RECT	{ 177, 61, 241, 101}

typedef CResourceManager::eBitmap bitmap_t;

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

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		TARGET, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RECT);

	//
	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 50, 250, 64, 274}, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 139, 7, 146, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 70, 250, 84, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 157, 7, 164, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 90, 250, 104, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 42, 7, 49, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 110, 250, 124, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 130, 250, 144, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 170, 250, 184, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 190, 250, 204, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 210, 250, 224, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 230, 250, 244, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->DrawBitmap(CResourceManager::GetInstance()->GetBitmap(bitmap_t::MENU_AND_TEXT),
		{ 250, 250, 264, 274 }, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, { 166, 7, 173, 19 });

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
}
