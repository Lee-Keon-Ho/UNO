#pragma once
#include "Room.h"

#define NAME_MAX 32

class CUser
{
public:
private:
	wchar_t m_name[NAME_MAX];
	CRoom* m_pRoom;
	// �߰� �������� �� ������?
public:
	CUser();
	~CUser();

	wchar_t* GetName() { return m_name; }
	void SetName(wchar_t* _name);
};