#pragma once
#include "Scene.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Room.h"
#include "Chatting.h"

class CWaitingRoomScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;

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
	CObject2D* m_pBackGround;
	CObject2D* m_pChatBackGround;

	player_t m_player;
	player_t m_playerImage;
	playerName_t m_pName;

	int fontSize;
	int m_MyNumber;
	int m_chatCount;

	// 2022-04-28 ����
	wchar_t* m_chatBuffer;

	CButton* m_pExitButton;

	CText* m_pChatText;
	CChatting* m_pChatting;
	CObject2D* m_pCard;

	D2D1_RECT_F m_backGroundRect;
	D2D1_RECT_F m_chatBackGroundRect;

	D2D1_RECT_F m_player1Rect;
	D2D1_RECT_F m_player2Rect;
	D2D1_RECT_F m_player3Rect;
	D2D1_RECT_F m_player4Rect;
	D2D1_RECT_F m_player5Rect;
	
	D2D1_RECT_F m_player1ImageRect;
	D2D1_RECT_F m_player2ImageRect;
	D2D1_RECT_F m_player3ImageRect;
	D2D1_RECT_F m_player4ImageRect;
	D2D1_RECT_F m_player5ImageRect;

	D2D1_RECT_F m_player1NameRect;
	D2D1_RECT_F m_player2NameRect;
	D2D1_RECT_F m_player3NameRect;
	D2D1_RECT_F m_player4NameRect;
	D2D1_RECT_F m_player5NameRect;


	// 2022-04-27 ���� : test
	CRoom::stROOM* m_pRoomInfo;
	CRoom::stUSER* m_pUserInfo;
	
	bool m_bChatting;
public:
	CWaitingRoomScene();
	~CWaitingRoomScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
};