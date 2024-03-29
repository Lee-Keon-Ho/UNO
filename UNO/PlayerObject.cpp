#include "Client.h"
#include "PlayerObject.h"
#include "Input.h"
#include "PacketType.h"
#include "Timer.h"
#include "information.h"

#define PLAYER_MAX 5
#define CARD_MAX 9
#define COLOR_CARD_MAX 4
#define BUFFER_MAX 100
#define GAME_OVER 19

CPlayerObject::CPlayerObject()
	: CText({ 0.0f,0.0f,0.0f,0.0f }, 0, 0, T_WHITE), m_fontSize(15), m_bCard(false), m_bChoice(false)
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pPlayerImage = pRM->GetBitmap(bitmap_t::CHARCTER);
	ID2D1Bitmap* pPlayerCountBitmap = pRM->GetBitmap(bitmap_t::ROOM_IN_PLAYER);
	ID2D1Bitmap* pCardBitmap = pRM->GetBitmap(bitmap_t::CARD);
	ID2D1Bitmap* pBossBitmap = pRM->GetBitmap(bitmap_t::BOSS);
	ID2D1Bitmap* pTurnBitmap = pRM->GetBitmap(bitmap_t::TURN);
	ID2D1Bitmap* pChoiceBitmap = pRM->GetBitmap(bitmap_t::CHOICE);
	ID2D1Bitmap* pboardBitmap = pRM->GetBitmap(bitmap_t::BOARD);
	ID2D1Bitmap* pGameOverBitmap = pRM->GetBitmap(bitmap_t::GAMEOVER);
	ID2D1Bitmap* pWinnerBitmap = pRM->GetBitmap(bitmap_t::WINNER);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pCardBoard = new CObject2D(sprite[CResourceManager::CARD_BOARD], pboardBitmap, { 490.0f, 483.0f, 1140.0f, 715.0f });
	m_pChoiceCardBoard = new CObject2D(sprite[CResourceManager::CARD_BOARD], pboardBitmap, { 446.0f, 209.0f, 836.0f, 346.0f });
	
	m_player.reserve(PLAYER_MAX);
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_ONE], pPlayerCountBitmap, { 384.0f, 472.0f, 838.0f, 720.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_TWO], pPlayerCountBitmap, { 0.0f, 69.0f, 440.0f, 250.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_THREE], pPlayerCountBitmap, { 837.0f, 69.0f, 1280.0f, 250.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FOUR], pPlayerCountBitmap, { 0.0f, 285.0f, 440.0f, 466.0f }));
	m_player.push_back(new CObject2D(sprite[CResourceManager::PLAYER_FIVE], pPlayerCountBitmap, { 837.0f, 285.0f, 1280.0f, 466.0f }));


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

	m_boss.reserve(PLAYER_MAX);
	m_boss.push_back(new CObject2D(sprite[CResourceManager::BOSS_ICON], pBossBitmap, { 430.0f, 490.0f, 450.0f, 510.0f }));
	m_boss.push_back(new CObject2D(sprite[CResourceManager::BOSS_ICON], pBossBitmap, { 110.0f, 90.0f, 130.0f, 110.0f }));
	m_boss.push_back(new CObject2D(sprite[CResourceManager::BOSS_ICON], pBossBitmap, { 1159.0f, 90.0f, 1179.0f, 110.0f }));
	m_boss.push_back(new CObject2D(sprite[CResourceManager::BOSS_ICON], pBossBitmap, { 110.0f, 306.0f, 130.0f, 326.0f }));
	m_boss.push_back(new CObject2D(sprite[CResourceManager::BOSS_ICON], pBossBitmap, { 1159.0f, 306.0f, 1179.0f, 326.0f }));

	m_turn.reserve(PLAYER_MAX);
	m_turn.push_back(new CObject2D(sprite[CResourceManager::MYTURN], pTurnBitmap, { 491.0f, 457.0f, 541.0f, 482.0f }));
	m_turn.push_back(new CObject2D(sprite[CResourceManager::MYTURN], pTurnBitmap, { 440.0f, 71.0f, 490.0f, 96.0f }));
	m_turn.push_back(new CObject2D(sprite[CResourceManager::MYTURN], pTurnBitmap, { 789.0f, 71.0f, 839.0f, 96.0f }));
	m_turn.push_back(new CObject2D(sprite[CResourceManager::MYTURN], pTurnBitmap, { 440.0f, 287.0f, 490.0f, 312.0f }));
	m_turn.push_back(new CObject2D(sprite[CResourceManager::MYTURN], pTurnBitmap, { 789.0f, 287.0f, 839.0f, 312.0f }));

	m_pChoiceColor.reserve(4);
	m_pChoiceColor.push_back(new CButton(sprite[CResourceManager::CHOICE_COLOR], pChoiceBitmap, { 456.0f, 219.0f, 526.0f, 336.0f }));
	m_pChoiceColor.push_back(new CButton(sprite[CResourceManager::CHOICE_COLOR], pChoiceBitmap, { 556.0f, 219.0f, 626.0f, 336.0f }));
	m_pChoiceColor.push_back(new CButton(sprite[CResourceManager::CHOICE_COLOR], pChoiceBitmap, { 655.0f, 219.0f, 726.0f, 336.0f }));
	m_pChoiceColor.push_back(new CButton(sprite[CResourceManager::CHOICE_COLOR], pChoiceBitmap, { 756.0f, 219.0f, 826.0f, 336.0f }));

	m_gameOver.reserve(PLAYER_MAX);
	m_gameOver.push_back(new CTextObject(sprite[CResourceManager::GAME_OVER_ICON], pGameOverBitmap, { 496.0f, 485.0f, 787.0f, 670.0f }));
	m_gameOver.push_back(new CTextObject(sprite[CResourceManager::GAME_OVER_ICON], pGameOverBitmap, { 169.0f, 71.0f, 440.0f, 255.0f }));
	m_gameOver.push_back(new CTextObject(sprite[CResourceManager::GAME_OVER_ICON], pGameOverBitmap, { 839.0f, 71.0f, 1110.0f, 255.0f }));
	m_gameOver.push_back(new CTextObject(sprite[CResourceManager::GAME_OVER_ICON], pGameOverBitmap, { 169.0f, 287.0f, 440.0f, 471.0f }));
	m_gameOver.push_back(new CTextObject(sprite[CResourceManager::GAME_OVER_ICON], pGameOverBitmap, { 839.0f, 287.0f, 1110.0f, 471.0f }));

	m_winner.reserve(PLAYER_MAX);
	m_winner.push_back(new CTextObject(sprite[CResourceManager::WINNER_ICON], pWinnerBitmap, { 531.0f, 514.0f, 752.0f, 580.0f }));
	m_winner.push_back(new CTextObject(sprite[CResourceManager::WINNER_ICON], pWinnerBitmap, { 194.0f, 114.0f, 415.0f, 180.0f }));
	m_winner.push_back(new CTextObject(sprite[CResourceManager::WINNER_ICON], pWinnerBitmap, { 864.0f, 114.0f, 1085.0f, 180.0f }));
	m_winner.push_back(new CTextObject(sprite[CResourceManager::WINNER_ICON], pWinnerBitmap, { 194.0f, 330.0f, 415.0f, 396.0f }));
	m_winner.push_back(new CTextObject(sprite[CResourceManager::WINNER_ICON], pWinnerBitmap, { 864.0f, 330.0f, 1085.0f, 396.0f }));

	m_playersCard = new card_t[PLAYER_MAX];

	m_pCard = CInformation::GetInstance()->GetUserCard();

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
					if (player == 2) rect = { 1050.0f - (23.0f * i), 80.0f + (52.0f * y), 1120.0f - (23.0f * i), 187.0f + (52.0f * y) };
					if (player == 3) rect = { 171.0f + (23.0f * i), 301.0f + (52.0f * y), 241.0f + (23.0f * i), 408.0f + (52.0f * y) };
					if (player == 4) rect = { 1050.0f - (23.0f * i), 301.0f + (52.0f * y), 1120.0f - (23.0f * i), 408.0f + (52.0f * y) };
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

	GameOver_t::iterator gameOverIter = m_gameOver.begin();
	GameOver_t::iterator gameOverEndIter = m_gameOver.end();
	for (; gameOverIter != gameOverEndIter; gameOverIter++)
	{
		if (*gameOverIter) { delete* gameOverIter; *gameOverIter = nullptr; }
	}
	m_gameOver.clear();

	card_t::iterator colorIter = m_pChoiceColor.begin();
	card_t::iterator colorEndIter = m_pChoiceColor.end();
	for (; colorIter != colorEndIter; colorIter++)
	{
		if (*colorIter) { delete* colorIter; *colorIter = nullptr; }
	}
	m_pChoiceColor.clear();

	player_t::iterator iter = m_turn.begin();
	player_t::iterator endIter = m_turn.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_turn.clear();

	iter = m_boss.begin();
	endIter = m_boss.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_boss.clear();

	iter = m_player.begin();
	endIter = m_player.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_player.clear();

	iter = m_playerImage.begin();
	endIter = m_playerImage.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_playerImage.clear();

	playerName_t::iterator nameIter = m_pName.begin();
	playerName_t::iterator nameEndIter = m_pName.end();
	for (; nameIter != nameEndIter; nameIter++)
	{
		if (*nameIter) { delete* nameIter; *nameIter = nullptr; }
	}
	m_pName.clear();

	iter = m_player.begin();
	endIter = m_player.end();
	for (; iter != endIter; iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
	m_player.clear();
}

void CPlayerObject::Update(CUser::stUserInfo* _userinfo, CRoom::stROOM* _roominfo, POINT _mouse, int _key)
{
	m_bStart = !_roominfo->state;

	// 2022-05-24 ����
	if (_roominfo->victory)
	{
		m_currentCardRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	}
	else if (_userinfo->cardCount < GAME_OVER)
	{
		if (_userinfo->choiceColor)
		{
			for (int i = 0; i < COLOR_CARD_MAX; i++)
			{
				if (m_pChoiceColor[i]->OnButton(_mouse))
				{
					m_currentCardRect = m_pChoiceColor[i]->GetTarget();
					if (_key == VK_LBUTTON)
					{
						char buffer[BUFFER_MAX];
						char* temp = buffer;
						memcpy(temp, &i, sizeof(unsigned short));
						PlaySound(L"card_flip.wav", 0, SND_FILENAME | SND_ASYNC);
						CClient::GetInstance()->Send(buffer, CS_PT_CHOISECOLOR);
						m_currentCardRect = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
					m_bChoice = true;
					break;
				}
				else
				{
					m_bChoice = false;
					m_currentCardRect = { 0.0f, 0.0f, 0.0f, 0.0f };
				}
			}
		}
		else
		{
			for (int i = 0; i < _userinfo->cardCount; i++)
			{
				if (m_playersCard[0][i]->OnButton(_mouse))
				{
					m_currentCardRect = m_playersCard[0][i]->GetTarget();
					if (_key == VK_LBUTTON && _userinfo->turn)
					{
						char buffer[BUFFER_MAX];
						char* temp = buffer;
						memcpy(temp, &m_pCard[i], sizeof(unsigned short));
						temp += sizeof(unsigned short);
						memcpy(temp, &i, sizeof(unsigned short));
						PlaySound(L"card_flip.wav", 0, SND_FILENAME | SND_ASYNC);
						CClient::GetInstance()->Send(buffer, CS_PT_DRAWCARD);
						_userinfo->turn = false;
						m_currentCardRect = { 0.0f, 0.0f, 0.0f, 0.0f };

						// 2022-05-24 ����
						CTimer::GetInstance()->ResetTimer();
					}
					m_bCard = true;
					break;
				}
				else
				{
					m_bCard = false;
					m_currentCardRect = { 0.0f, 0.0f, 0.0f, 0.0f };
				}
			}
		}
	}
}

void CPlayerObject::Render(ID2D1HwndRenderTarget* _pRT, CUser::stUserInfo* _userinfo, int _playerCount, int _myNum)
{
	int myUserinfoNum = _myNum - 1;

	for (int iObject = 1, iUserInfo = 0; iUserInfo < _playerCount; iUserInfo++)
	{
		int count = _userinfo[iUserInfo].number;
		if (count != 0)
		{
			if (_myNum == count)
			{
				m_player[0]->Render(_pRT, 1.0f);
				m_playerImage[0]->Render(_pRT, _userinfo[iUserInfo].image, 1.0f);
				m_pName[0]->Render(_pRT, _userinfo[iUserInfo].name);
				if (_userinfo[iUserInfo].boss)
				{
					m_boss[0]->Render(_pRT, 1.0f);
				}
				if (_userinfo[iUserInfo].cardCount == 0)
				{
					m_winner[0]->Render(_pRT);
				}
				else if (_userinfo[iUserInfo].cardCount >= GAME_OVER)
				{
					m_gameOver[0]->Render(_pRT);
				}
				else
				{
					if (m_bStart) m_pCardBoard->Render(_pRT, 1.0f);

					for (int i = 0; i < _userinfo[iUserInfo].cardCount; i++)
					{
						m_playersCard[0][i]->Render(_pRT, m_pCard[i], 1.0f);
					}
					if (_userinfo[iUserInfo].turn && m_bStart)
					{
						m_turn[0]->Render(_pRT, 1.0f);
					}
					if (_userinfo[iUserInfo].choiceColor)
					{
						m_pChoiceCardBoard->Render(_pRT, 1.0f);
						for (int i = 0; i < 4; i++)
						{
							m_pChoiceColor[i]->Render(_pRT, i, 1.0f);
						}
					}
				}
			}
			else
			{
				m_player[iObject]->Render(_pRT, 1.0f);
				m_playerImage[iObject]->Render(_pRT, _userinfo[iUserInfo].image, 1.0f);
				m_pName[iObject]->Render(_pRT, _userinfo[iUserInfo].name);
				if (_userinfo[iUserInfo].boss)
				{
					m_boss[iObject]->Render(_pRT, 1.0f);
				}
				if (_userinfo[iUserInfo].cardCount == 0)
				{
					m_winner[iObject]->Render(_pRT);
				}
				else if (_userinfo[iUserInfo].cardCount >= GAME_OVER)
				{
					m_gameOver[iObject]->Render(_pRT);
				}
				else
				{	
					for (int i = 0; i < _userinfo[iUserInfo].cardCount; i++)
					{
						m_playersCard[iObject][i]->Render(_pRT, 1.0f);
					}
					if (_userinfo[iUserInfo].turn && m_bStart)
					{
						m_turn[iObject]->Render(_pRT, 1.0f);
					}
				}
				iObject++;
			}
		}
		else iObject++;
	}

	if (m_bCard) _pRT->DrawRectangle(m_currentCardRect, m_pBrush, 1.0f);
	if (m_bChoice) _pRT->DrawRectangle(m_currentCardRect, m_pBrush, 1.0f);
}