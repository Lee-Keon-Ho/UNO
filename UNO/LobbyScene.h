#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class CLobbyScene : public CScene
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;

	enum TARGET
	{
		BACKGROUND,
		OK,
		MAX
	};
private:
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pOkBitmap;
	targetList_t* m_target;

	CResourceManager::spriteList_t* m_sprite;
	
	unsigned int m_bOK;

public:
	CLobbyScene();
	~CLobbyScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};