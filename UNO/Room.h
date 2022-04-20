#pragma once
#include "text.h"

#define ROOM_NAME_MAX_SIZE 64

class CRoom : public CText
{
public:
	struct stROOM
	{
		int number;
		wchar_t name[ROOM_NAME_MAX_SIZE];
		int playerCount;
		bool state;
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
	void SetRoomList(); //2022-04-20 ���� : test

	int GetSize() { return m_list.size(); }
	room_t GetRoomList() { return m_list; }
private:
};