#pragma once
#include "Scene.h"
#include "Object.h"
#include "ResourceManager.h"
#include <d2d1.h>

class CRoomScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
private:


	D2D1_RECT_F m_gameBordRECT;
public:
	CRoomScene();
	~CRoomScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:

};