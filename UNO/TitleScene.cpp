#include "TitleScene.h"
#include "SceneManager.h"

#define STR_MAX 20

CTitleScene::CTitleScene()
	: m_bOnRender(true), m_tick(0), 
	m_logoRect({ 652, 236, 870, 373 }), m_logoTargetRect({ 100, 30, 670, 430 }),
	m_backGroundRect({ 104, 80, 105, 81 }), m_backGroundTargetRect({ 0, 0, 770, 695 })
{

}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::MENU_AND_TEXT);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	//background
	m_pBackground = new CObject(new CSprite(m_backGroundRect), pBitmap);
	m_pBackground->SetTarget(m_backGroundTargetRect);

	//logo
	m_pLogo = new CObject(new CSprite(m_logoRect), pBitmap);
	m_pLogo->SetTarget(m_logoTargetRect);

	// text
	m_pRedText = new CObject(sprite[CResourceManager::RED], pBitmap);
	char str[] = { "A KEY START" };
	int size = sizeof(str) - 1;
	m_pTextArr = new int[size];
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (str[i] - 'A' < 0) continue;
		m_pTextArr[count++] = str[i] - 'A';
		m_pRedText->SetTarget({ 120.0f + (i * 50), 550.0f, 160.0f + (i * 50), 600.0f });
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
	m_pBackground->Render(_pRT, 0, 1.0f);

	// LOGO
	m_pLogo->Render(_pRT, 0, 1.0f);

	if (m_bOnRender)
	{
		m_pRedText->Render(_pRT, m_pTextArr, 1.0f);
	}

	_pRT->EndDraw();
}

void CTitleScene::Destroy()
{
	if (m_pTextArr) { delete[] m_pTextArr; m_pTextArr = nullptr; }
	if (m_pRedText) { delete m_pRedText; m_pRedText = nullptr; }
	if (m_pLogo) { delete m_pLogo; m_pLogo = nullptr; }
	if (m_pBackground) { delete m_pBackground; m_pBackground = nullptr; }
}
