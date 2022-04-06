#pragma once
#include "Object.h"

#define NAME_MAX 16

class CUser
{
public:
private:
	char m_name[NAME_MAX];
	// 추가 사항으로 뭘 넣을까?
public:
	CUser();
	CUser(char* _name);
	~CUser();

	char* GetName() { return m_name; }
};