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
	D2D1_RECT_F m_okRect;

	CObject* m_pBord;
	CObject* m_pYellowSpelling;
	CObject* m_pBlueSpelling;
	CObject* m_pTitle;
	CObject* m_pBar;
	CObject* m_pName;
	CObject* m_pOk;

	unsigned int m_spellingSize;
	unsigned int m_widthMax;
	unsigned int m_heightMax;
	unsigned int m_bOK;
	unsigned int m_currentSpelling;
	unsigned int m_nameSize;
	unsigned int m_titleSize;
	unsigned int m_bufferCount;

	char* m_pBuffer; // test
	int* m_pTextArr;
	int* m_pNameArr;

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