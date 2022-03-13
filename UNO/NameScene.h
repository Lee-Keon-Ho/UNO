#pragma once
#include "Scene.h"
#include "Object.h"
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
	targetList_t* m_target;

	CObject* m_bord;
	CObject* m_yellowSpelling;
	CObject* m_blueSpelling;
	CObject* m_title;
	CObject* m_bar;
	CObject* m_ok;
	CObject* m_name;

	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pOkBitmap;

	CResourceManager::spriteList_t* m_sprite;

	unsigned int m_spellingSize;
	unsigned int m_widthMax;
	unsigned int m_heightMax;
	unsigned int m_bOK;
	unsigned int m_currentSpelling;
	unsigned int m_nameSize;
	unsigned int m_titleSize;


	char* m_pBuffer; // test
	int m_bufferCount;

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