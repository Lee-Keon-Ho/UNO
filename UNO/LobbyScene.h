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

class CLobbyScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CButton*> Button_t;
	typedef std::list<CUser*> UserList_t;
	typedef std::list<CRoom*> RoomList;

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

	CText* m_pMyNameText;
	CText* m_pUserListText;

	int m_pontSize1;
	int m_pontSize2;
	int m_textHeight;

	WCHAR* m_pName;
	int m_num;

	UserList_t* m_userList;

	bool m_bOnExit;
	bool m_bOnCreate;
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