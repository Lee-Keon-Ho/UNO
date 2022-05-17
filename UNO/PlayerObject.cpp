#include "Client.h"
#include "PlayerObject.h"
#include "Input.h"
#include "PacketType.h"

#define PLAYER_MAX 5
#define CARD_MAX 9

CPlayerObject::CPlayerObject() 
	: CText({0.0f,0.0f,0.0f,0.0f}, 0, 0, T_RED), m_fontSize(15), m_bCard(false)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pPlayerImage = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pPlayerCountBitmap = pRM->GetBitmap(bitmap_t::ROOM_IN_PLAYER);
	ID2D1Bitmap* pCardBitmap = pRM->GetBitmap(bitmap_t::CARD);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_player.reserve(PLAYER_MAX);
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_ONE], pPlayerCountBitmap, { 384.0f, 472.0f, 838.0f, 720.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_TWO], pPlayerCountBitmap, { 0.0f, 69.0f, 440.0f, 250.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_THREE], pPlayerCountBitmap, { 837.0f, 69.0f, 1280.0f, 250.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FOUR], pPlayerCountBitmap, { 10.0f, 285.0f, 450.0f, 466.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FIVE], pPlayerCountBitmap, { 837.0f, 275.0f, 1280.0f, 456.0f }));


	m_playerImage.reserve(PLAYER_MAX);
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, { 400.0f, 514.0f, 480.0f, 594.0f }));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, { 80.0f, 114.0f, 160.0f, 194.0f }));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, { 1129.0f, 114.0f, 1209.0f, 194.0f }));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, { 80.0f, 330.0f, 160.0f, 410.0f }));
	m_playerImage.push_back(new CObject2D(sprite[CResourceManager::CHARCTER_ICON], pPlayerImage, { 1129.0f, 330.0f, 1209.0f, 410.0f }));

	m_pName.reserve(PLAYER_MAX);
	m_pName.push_back(new CText({ 424.0f, 602.0f, 504.0f, 682.0f }, m_fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText({ 103.0f, 197.0f, 183.0f, 277.0f }, m_fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText({ 1153.0f, 197.0f, 1233.0f, 277.0f }, m_fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText({ 103.0f, 412.0f, 183.0f, 492.0f }, m_fontSize, 0, CText::T_WHITE));
	m_pName.push_back(new CText({ 1153.0f, 412.0f, 1233.0f, 492.0f }, m_fontSize, 0, CText::T_WHITE));

	m_playersCard = new card_t[PLAYER_MAX];

	D2D1_RECT_F rect;
	for (int player = 0; player < PLAYER_MAX; player++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int i = 0; i < CARD_MAX; i++)
			{
				if (player == 0)
				{
					rect = { 500.0f + (70.0f * i), 492.0f + (107.0f * y), 570.0f + (70.0f * i), 599.0f + (107.0f * y) };
					m_playersCard[player].push_back(new CButton(sprite[CResourceManager::UNO_CARD], pCardBitmap, rect));
				}
				else
				{
					if (player == 1) rect = { 171.0f + (23.0f * i), 80.0f + (52.0f * y), 241.0f + (23.0f * i), 187.0f + (52.0f * y) };
					if (player == 2) rect = { 1050.0f - (20.0f * i), 80.0f + (52.0f * y), 1120.0f - (20.0f * i), 187.0f + (52.0f * y) };
					if (player == 3) rect = { 171.0f + (20.0f * i), 301.0f + (52.0f * y), 241.0f + (20.0f * i), 408.0f + (52.0f * y) };
					if (player == 4) rect = { 1050.0f - (20.0f * i), 301.0f + (52.0f * y), 1120.0f - (15.0f * i), 408.0f + (52.0f * y) };
					m_playersCard[player].push_back(new CButton(sprite[CResourceManager::SECRET_CARD], pCardBitmap, rect));
				}

			}
		}
	}
}

CPlayerObject::~CPlayerObject()
{
	if (m_playersCard)
	{
		for (int player = 0; player < PLAYER_MAX; player++)
		{
			card_t::iterator cardIter = m_playersCard[player].begin();
			card_t::iterator cardEndIter = m_playersCard[player].end();
			for (; cardIter != cardEndIter; cardIter++)
			{
				delete* cardIter;
			}
		}
		delete[] m_playersCard;
	}

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

void CPlayerObject::Update(CRoom::stUSER* _userinfo, POINT _mouse, int _key)
{
	for (int i = 0; i < _userinfo->cardCount; i++)
	{
		if (m_playersCard[0][i]->OnButton(_mouse))
		{
			if (_key == VK_LBUTTON && _userinfo->turn)
			{
				char buffer[100];
				char* temp = buffer;
				memcpy(temp, &_userinfo->card[i], sizeof(unsigned short));
				temp += sizeof(unsigned short);
				memcpy(temp, &i, sizeof(unsigned short));
				CClient::GetInstance()->Send(buffer, CS_PT_DRAWCARD);
			}
			m_cruuentCardRect = m_playersCard[0][i]->GetTarget();
			m_bCard = true;
			break;
		}
		m_bCard = false;
	}
}

void CPlayerObject::Render(ID2D1HwndRenderTarget* _pRT, CRoom::stUSER* _userinfo, int _myNum)
{
	int myUserinfoNum = _myNum - 1;
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
				for (int i = 0; i < _userinfo[iUserInfo].cardCount; i++)
				{
					m_playersCard[0][i]->Render(_pRT, _userinfo[myUserinfoNum].card[i], 1.0f);
				}
			}
			else
			{
				m_player[iObject]->Render(_pRT, 1.0f);
				m_playerImage[iObject]->Render(_pRT, _userinfo[iUserInfo].image, 1.0f);
				m_pName[iObject]->Render(_pRT, _userinfo[iUserInfo].playerName);
				for (int i = 0; i < _userinfo[iUserInfo].cardCount; i++)
				{
					m_playersCard[iObject][i]->Render(_pRT, 1.0f);
				}
				iObject++;
			}
		}
		else iObject++;
	}

	// 2022-05-17 ¼öÁ¤
	if (m_bCard) _pRT->DrawRectangle(m_cruuentCardRect, m_pBrush, 1.0f);
}