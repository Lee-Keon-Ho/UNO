#pragma once
#include "text.h"

#define ROOM_NAME_MAX_SIZE 64
#define USER_NAME_MAX 32
#define USER_CARD_MAX 20

class CRoom : public CText
{
public:
	struct stROOM
	{
		int number;
		wchar_t name[ROOM_NAME_MAX_SIZE];
		int playerCount;
		bool state;
		bool victory;
	};

	struct stUSER
	{
		int number;
		wchar_t playerName[USER_NAME_MAX];
		int image;
		SOCKET socket;
		bool boss;
		bool ready;
		int card[USER_CARD_MAX];
		int cardCount;
		bool turn;
		bool choiceColor;
	};

	typedef std::vector<CRoom::stROOM> room_t;

private:
	room_t m_list;

	D2D1_RECT_F m_nameRect;
	D2D1_RECT_F m_numberRect;
	D2D1_RECT_F m_playerCountRect;
	D2D1_RECT_F m_stateRect;
public:
	CRoom();
	CRoom(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color);
	~CRoom();

	void Render(ID2D1HwndRenderTarget* _pRT);
	void SetList();

	int GetSize() { return m_list.size(); }
	room_t GetRoomList() { return m_list; }
private:
};