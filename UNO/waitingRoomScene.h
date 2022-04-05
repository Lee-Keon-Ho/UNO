#pragma once
#include "Scene.h"
#include "Button.h"
#include "ResourceManager.h"

class CWaitingRoomScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;

private:
	CObject* m_pBackGround;

	CButton* m_pExitButton;

	D2D1_RECT_F m_backGroundRect;


public:
	CWaitingRoomScene();
	~CWaitingRoomScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
};