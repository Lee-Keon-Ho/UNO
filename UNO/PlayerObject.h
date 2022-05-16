#pragma once
#include "text.h"
#include "Room.h"
#include "Button.h"
#include "ResourceManager.h"

class CPlayerObject : public CObject2D
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;
	typedef std::vector<CButton*> card_t;

private:
	player_t m_player;
	player_t m_playerImage;
	playerName_t m_pName;

	card_t* m_playersCard;

	CButton* m_pCurrentCard;

	int m_fontSize;

public:
	CPlayerObject();
	~CPlayerObject();

	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT, CRoom::stROOM* _roominfo, CRoom::stUSER* _userinfo, int _myNum);
};