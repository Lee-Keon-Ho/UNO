#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class CTitleScene : public CScene
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;
	typedef CResourceManager::eBitmap bitmap_t;

	enum TARGET
	{
		TEXT = 0,
		BACKGROUND,
		LOGO,
		MAX
	};

private:
	CResourceManager::spriteList_t* m_sprite;
	ID2D1Bitmap* m_pBitmap;
	targetList_t* m_target;
	D2D1_RECT_F m_logoRect;
	D2D1_RECT_F m_backGroundRect;
	int* m_str;

	int m_titleSize;
	int m_bOnRender;
	int m_tick;

public:
	CTitleScene();
	~CTitleScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};