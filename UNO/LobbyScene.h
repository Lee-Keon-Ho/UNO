#pragma once
#include "Scene.h"
#include "Object.h"
#include "Button.h"
#include "ResourceManager.h"
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

	enum BUTTON
	{
		CREATE = 0,
		QUICK,
		CHOOSE,
		EXIT,
		BUTTON_MAX
	};

private:
	ID2D1SolidColorBrush* m_pBrush;
	IDWriteTextFormat* m_pWriteTextFormat;
	IDWriteTextFormat* m_pUserListWriteTextFormat;

	CObject* m_pBackGround;
	CObject* m_pCharacter; 

	Button_t m_button;

	CButton* m_pCreateButton;
	CButton* m_pQuickButton;
	CButton* m_pChooseButton;
	CButton* m_pExitButton;

	D2D1_RECT_F m_backGroundRect;
	D2D1_RECT_F m_createButtonRect;
	D2D1_RECT_F m_quickButtonRect;
	D2D1_RECT_F m_chooseButtonRect;
	D2D1_RECT_F m_exitButtonRect;
	D2D1_RECT_F m_peopleIconRect;
	D2D1_RECT_F m_myNameTextRect;
	D2D1_RECT_F m_userListRect;

	CText* m_pMyNameText;
	CText* m_pUserListText;
	CText* m_pTimeText;

	//test
	RoomList m_roomList; 
	UserList_t* m_pUserList; // 특정 시간마다 Update에서 새로 갱신 하도록 만들자
	//

	int m_pontSize1;
	int m_pontSize2;
	int m_textHeight;

	WCHAR* m_pName;
	int m_num;
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