#pragma once
#include "Scene.h"
#include "ResourceManager.h"
#include <d2d1.h>
 
class CNameScene : public CScene
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;
	typedef CResourceManager::eBitmap bitmap_t;

	enum TARGET
	{
		SPELLING = 0,
		BACKGROUND,
		TITLE,
		BAR,
		NAME,
		OK,
		MAX
	};

private:
	ID2D1SolidColorBrush* m_pRedBrush;
	D2D1_POINT_2F m_rectangle;
	D2D1_RECT_F m_barRect;
	D2D1_RECT_F m_backgroundRect;
	targetList_t* m_target;

	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pOkBitmap;

	CResourceManager::spriteList_t* m_sprite;

	unsigned int m_spellingSize;
	unsigned int m_widthMax;
	unsigned int m_heightMax;
	unsigned int m_bOK;

	int* m_title;

	char* m_name; // test
	int m_count;
	unsigned int m_nameSize;
	unsigned int m_titleSize;
public:
	CNameScene();
	~CNameScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};