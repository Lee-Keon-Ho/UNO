#pragma once
#include "text.h"
#include "User.h"
#include "Room.h"
#include "Button.h"	
#include "TextObject.h"
#include "ResourceManager.h"

class CPlayerObject : public CObject2D, CText
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;
	typedef std::vector<CButton*> card_t;
	typedef std::vector<D2D1_RECT_F> Turn_t;
	typedef std::vector<CTextObject*> GameOver_t;
	typedef std::vector<CTextObject*> Winner_t;

private:
	player_t m_player;
	player_t m_playerImage;
	player_t m_boss;
	player_t m_turn;
	playerName_t m_pName;
	GameOver_t m_gameOver;
	Winner_t m_winner;

	card_t m_pChoiceColor;
	card_t* m_playersCard;

	CObject2D* m_pCardBoard;
	CObject2D* m_pChoiceCardBoard;

	CButton* m_pCurrentCard;

	D2D1_RECT_F m_currentCardRect;
	D2D1_RECT_F m_ChoiceColorCardRect;

	int* m_pCard;

	int m_fontSize;

	bool m_bCard;
	bool m_bStart;
	bool m_bChoice;
public:
	CPlayerObject();
	~CPlayerObject();

	void Update(CUser::stUserInfo* _userinfo, CRoom::stROOM* _roominfo, POINT _mouse, int _key);
	void Render(ID2D1HwndRenderTarget* _pRT, CUser::stUserInfo* _userinfo, int _playerCount,int _myNum);
};