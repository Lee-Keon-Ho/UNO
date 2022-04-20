#pragma once
#include "Scene.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Room.h"

class CWaitingRoomScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject*> player_t;

	enum ePlayer
	{
		P_ONE = 0,
		P_TWO,
		P_THREE,
		P_FOUR,
		P_FIVE,
		PLAYER_MAX
	};
private:
	CObject* m_pBackGround;

	player_t m_player;

	CButton* m_pExitButton;

	D2D1_RECT_F m_backGroundRect;

	//2022-04-22 ¼öÁ¤ : test
	CRoom::stROOM* m_pRoominfo;
public:
	CWaitingRoomScene();
	~CWaitingRoomScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
};