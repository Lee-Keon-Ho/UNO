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

private:
	ID2D1SolidColorBrush* m_pBrush;
	IDWriteTextFormat* m_pWriteTextFormat;

	CObject* m_pBackGround;
	CObject* m_pCharacter;

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

	RoomList m_roomList;

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