#pragma once
#include "Object.h"

class CUserList
{
public:
private:
	char* m_pName;
	// 추가 사항으로 뭘 넣을까?
public:
	CUserList();
	CUserList(char* _name);
	~CUserList();
};