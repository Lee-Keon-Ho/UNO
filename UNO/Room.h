#pragma once
#include "Object.h"

class CRoom
{
public:
	struct stROOM
	{
		int number;
		wchar_t name[64];
		int playerCount;
		bool state;
	};
private:
	stROOM m_room;

public:
	CRoom();
	~CRoom();

	void SetRoom(wchar_t* _name);
	stROOM* GetRoom() { return &m_room; }
private:
};

// 한번의 요구는 한번에 보내준다.