#pragma once
#include "Object.h"

class CRoom : public CObject
{
public:
	struct Room
	{
		int number;
		wchar_t name[32];
		int playerCount;
		bool state;
	};
private:
	Room m_room;

public:
	CRoom();
	CRoom(spriteList_t _sprite, ID2D1Bitmap* _bitmap);
	~CRoom();

	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void SetTarget(D2D1_RECT_F _target);
	void SetName(wchar_t* _name);
private:
};

// 한번의 요구는 한번에 보내준다.