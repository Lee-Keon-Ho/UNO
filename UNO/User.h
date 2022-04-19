#pragma once
#include "Room.h"

class CUser
{
public:
private:
	wchar_t* m_pData;

public:
	CUser();
	~CUser();

	void SetData(char* _name, int _size);
	wchar_t* GetData() { return m_pData; }
};