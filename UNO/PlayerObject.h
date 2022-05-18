#pragma once
#include "text.h"
#include "Room.h"
#include "Button.h"
#include "ResourceManager.h"

class CPlayerObject : public CObject2D, CText
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;
	typedef std::vector<CButton*> card_t;
	typedef std::vector<D2D1_RECT_F> Turn_t;

private:
	player_t m_player;
	player_t m_playerImage;
	player_t m_boss;
	player_t m_turn;
	playerName_t m_pName;

	card_t* m_playersCard;

	// 134 44

	CButton* m_pCurrentCard;

	D2D1_RECT_F m_currentCardRect;

	int m_fontSize;

	bool m_bCard;
	bool m_bStart;
public:
	CPlayerObject();
	~CPlayerObject();

	void Update(CRoom::stUSER* _userinfo, CRoom::stROOM* _roominfo, POINT _mouse, int _key);
	void Render(ID2D1HwndRenderTarget* _pRT, CRoom::stUSER* _userinfo, int _myNum);
};