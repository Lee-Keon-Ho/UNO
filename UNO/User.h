#pragma once
#include "Object.h"

#define NAME_MAX 16

class CUser
{
public:
private:
	wchar_t m_name[NAME_MAX];
	// �߰� �������� �� ������?
public:
	CUser();
	~CUser();

	wchar_t* GetName() { return m_name; }
	void SetName(wchar_t* _name);
};