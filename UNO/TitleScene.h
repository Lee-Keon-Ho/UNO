#pragma once
#include "Scene.h"
#include "Object.h"
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
	ID2D1Bitmap* m_pBitmap;

	CObject* m_pBackground;
	CObject* m_pLogo;
	CObject* m_pRedText;

	int* m_pTextArr;

	D2D1_RECT_F m_logoRect;
	D2D1_RECT_F m_logoTargetRect;
	D2D1_RECT_F m_backGroundRect;
	D2D1_RECT_F m_backGroundTargetRect;

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