#pragma once
#include "Scene.h"
#include "Object.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Room.h"
#include "UserList.h"
#include <list>
class CLobbyScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::list<CRoom*> RoomList;
	//typedef std::list<CUserList*> UserList;
	enum TARGET
	{
		BACKGROUND,
		OK,
		MAX
	};
private:
	CObject* m_pBackGround;

	CButton* m_pCreateButton;
	CButton* m_pQuickButton;
	CButton* m_pChooseButton;

	D2D1_RECT_F m_backGroundRect;
	D2D1_RECT_F m_createButtonRect;
	D2D1_RECT_F m_quickButtonRect;
	D2D1_RECT_F m_chooseButtonRect;

	RoomList m_roomList;
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