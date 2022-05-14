#pragma once
#include "text.h"
#include "Room.h"
#include "ResourceManager.h"

class CPlayerObject : public CObject2D
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;
	typedef std::vector<CObject2D*> card_t;

private:
	player_t m_player;
	player_t m_playerImage;
	playerName_t m_pName;

	card_t* m_playersCard;

	int m_fontSize;

	D2D1_RECT_F m_player1Rect; // vector로 변환
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

	//변수 상시로 필요한 변수
	//임시 변수
public:
	CPlayerObject();
	~CPlayerObject();

	void Render(ID2D1HwndRenderTarget* _pRT, CRoom::stROOM* _roominfo, CRoom::stUSER* _userinfo, int _myNum);
};