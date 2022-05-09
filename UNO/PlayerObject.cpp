#include "PlayerObject.h"

#define PLAYER_MAX 5

CPlayerObject::CPlayerObject() :
	m_player1Rect({ 384.0f, 472.0f, 838.0f, 720.0f }), m_player2Rect({ 0.0f, 69.0f, 440.0f, 250.0f }), 
	m_player3Rect({ 837.0f, 69.0f, 1280.0f, 250.0f }), m_player4Rect({ 10.0f, 285.0f, 450.0f, 466.0f }), 
	m_player5Rect({ 837.0f, 275.0f, 1280.0f, 456.0f }), m_player1ImageRect({ 400.0f, 514.0f, 480.0f, 594.0f }), 
	m_player2ImageRect({ 80.0f, 114.0f, 160.0f, 194.0f }), m_player3ImageRect({ 1129.0f, 114.0f, 1209.0f, 194.0f }), 
	m_player4ImageRect({ 80.0f, 330.0f, 160.0f, 410.0f }), m_player5ImageRect({ 1129.0f, 330.0f, 1209.0f, 410.0f }), 
	m_player1NameRect({ 424.0f, 602.0f, 504.0f, 682.0f }), m_player2NameRect({ 103.0f, 197.0f, 183.0f, 277.0f }), 
	m_player3NameRect({ 1153.0f, 197.0f, 1233.0f, 277.0f }), m_player4NameRect({ 103.0f, 412.0f, 183.0f, 492.0f }), 
	m_player5NameRect({ 1153.0f, 412.0f, 1233.0f, 492.0f }), fontSize(15)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pPlayerImage = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pPlayerCountBitmap = pRM->GetBitmap(bitmap_t::ROOM_IN_PLAYER);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_player.reserve(PLAYER_MAX);
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_ONE], pPlayerCountBitmap, m_player1Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_TWO], pPlayerCountBitmap, m_player2Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_THREE], pPlayerCountBitmap, m_player3Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FOUR], pPlayerCountBitmap, m_player4Rect));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FIVE], pPlayerCountBitmap, m_player5Rect));


	m_playerImage.reserve(PLAYER_MAX);
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player1ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player2ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player3ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player4ImageRect));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, m_player5ImageRect));

	m_pName.reserve(PLAYER_MAX);
	m_pName.push_back(new CText(m_player1NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player2NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player3NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player4NameRect, fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText(m_player5NameRect, fontSize, 0, CText::T_WHITE));
}

CPlayerObject::~CPlayerObject()
{
	player_t::iterator iter = m_player.begin();
	player_t::iterator endIter = m_player.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_player.clear();

	player_t::iterator imageIter = m_playerImage.begin();
	player_t::iterator imageEndIter = m_playerImage.end();
	for (; imageIter != imageEndIter; imageIter++)
	{
		if (*imageIter) { delete* imageIter; *imageIter = nullptr; }
	}
	m_playerImage.clear();

	playerName_t::iterator nameIter = m_pName.begin();
	playerName_t::iterator nameEndIter = m_pName.end();
	for (; nameIter != nameEndIter; nameIter++)
	{
		if (*nameIter) { delete* nameIter; *nameIter = nullptr; }
	}
	m_pName.clear();
}

void CPlayerObject::Render(ID2D1HwndRenderTarget* _pRT, CRoom::stROOM* _roominfo, CRoom::stUSER* _userinfo, int _myNum)
{
	for (int iObject = 1, iUserInfo = 0; iUserInfo < PLAYER_MAX; iUserInfo++)
	{
		int count = _userinfo[iUserInfo].number;
		if (count != 0)
		{
			if (_myNum == count)
			{
				m_player[0]->Render(_pRT, 1.0f);
				m_playerImage[0]->Render(_pRT, _userinfo[iUserInfo].image, 1.0f);
				m_pName[0]->Render(_pRT, _userinfo[iUserInfo].playerName);
			}
			else
			{
				m_player[iObject]->Render(_pRT, 1.0f);
				m_playerImage[iObject]->Render(_pRT, _userinfo[iUserInfo].image, 1.0f);
				m_pName[iObject]->Render(_pRT, _userinfo[iUserInfo].playerName);
				iObject++;
			}
		}
		else iObject++;
	}
}