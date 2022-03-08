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
	targetList_t* m_target;

	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pOkBitmap;

	CResourceManager::spriteList_t* m_sprite;

	unsigned int m_spellingSize;
	unsigned int m_widthMax;
	unsigned int m_heightMax;
	unsigned int m_bOK;

	int* m_title;

	char* m_name;
	int	m_count;
	int m_nameSize;
	int m_titleSize;
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