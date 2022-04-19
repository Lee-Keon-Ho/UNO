#pragma once
#include "Scene.h"
#include "Object.h"
#include "Button.h"
#include "ResourceManager.h"
#include "information.h"
#include "Room.h"
#include "User.h"
#include "text.h"
#include <list>
#include <vector>

class CLobbyScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CButton*> Button_t;
	typedef std::vector<CRoom::stROOM> room_t;

	enum eButton
	{
		LB_CREATE = 0,
		LB_QUICK,
		LB_CHOOSE,
		LB_EXIT,
		LB_BUTTON_MAX
	};
private:
	ID2D1SolidColorBrush* m_pBrush;
	IDWriteTextFormat* m_pWriteTextFormat;
	IDWriteTextFormat* m_pUserListWriteTextFormat;

	CObject* m_pBackGround;
	CObject* m_pCharacter; 
	CObject* m_pExitBackGround;
	CObject* m_pExitTextObject;
	CObject* m_pCreateRoomObject;

	Button_t m_button;

	// 2022-04-18 test
	Button_t m_roomListButton;
	int m_count = 0;
	int m_roomCount = 0;
	//


	CButton* m_pExitOkButton;
	CButton* m_pExitNoButton;
	CButton* m_pCreateOkButton;
	CButton* m_pCreateNoButton;

	D2D1_RECT_F m_backGroundRect;
	D2D1_RECT_F m_createButtonRect;
	D2D1_RECT_F m_quickButtonRect;
	D2D1_RECT_F m_chooseButtonRect;
	D2D1_RECT_F m_exitButtonRect;
	D2D1_RECT_F m_peopleIconRect;
	D2D1_RECT_F m_myNameTextRect;
	D2D1_RECT_F m_userListRect;
	D2D1_RECT_F m_exitTextObject;
	D2D1_RECT_F m_exitOkButtonRect;
	D2D1_RECT_F m_exitNoButtonRect;
	D2D1_RECT_F m_createRoomRect;
	D2D1_RECT_F m_createOkButtonRect;
	D2D1_RECT_F m_createNoButtonRect;
	D2D1_RECT_F m_createRoomTextRect;
	D2D1_RECT_F m_roomListRect;

	CText* m_pMyNameText;
	CText* m_pUserListText;
	CText* m_pCreateRoomText;
	CText* m_pRoomListText;

	wchar_t* m_pRoomName;

	int m_pontSize1;
	int m_pontSize2;
	int m_textHeight;
	int m_roomNameCount;
	int m_roomNameMax;
	wchar_t* m_pName;
	int m_num;

	//2022-04-19
	CUser* m_user;
	room_t m_roomList;

	bool m_bOnExit;
	bool m_bOnCreate;
	bool m_bOnRoom;

	CRoom* m_pRoom;
	
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