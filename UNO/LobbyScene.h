#pragma once
#include "Scene.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Room.h"
#include "User.h"
#include <list>
class CLobbyScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::list<CRoom*> RoomList;
	typedef std::list<CUser*> UserList;
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
	

	CObject* m_pBord;
	CObject* m_pOk;
	CObject* m_pRoomList;
	CObject* m_pUserList;
	CObject* m_pChatting;
	CObject* m_pNumText;
	CObject* m_pRoomNameText;
	CObject* m_pStateText;
	CObject* m_pCreateButton;
	CObject* m_pQuickButton;

	/*CRoom* room;
	CRoom* room1;
	CRoom* room2;*/
	RoomList m_roomList;
	UserList m_userList;

	D2D1_RECT_F m_okRect;
	D2D1_RECT_F m_bordRect;
	D2D1_RECT_F m_roomRect;
	D2D1_RECT_F m_userRect;
	D2D1_RECT_F m_chatRect;
	D2D1_RECT_F m_createButtonRect;
	D2D1_RECT_F m_quickButtonRect;

	unsigned int m_bOK;

	unsigned int m_numTextSize;
	unsigned int m_roomNameTextSize;
	unsigned int m_stateTextSize;
	unsigned int m_createTextSize;
	unsigned int m_quickTextSize;

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