#pragma once
#include "Object.h"

class CRoom
{
public:
	struct stROOM
	{
		int number;
		wchar_t name[32];
		int playerCount;
		bool state;
	};
private:
	stROOM m_room;

public:
	CRoom();
	~CRoom();

	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void SetTarget(D2D1_RECT_F _target);
	stROOM* GetRoom() { return &m_room; }
private:
};

// �ѹ��� �䱸�� �ѹ��� �����ش�.