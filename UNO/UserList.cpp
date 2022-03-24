#include "UserList.h"
#include <string>
CUserList::CUserList()
{
}

CUserList::CUserList(char* _name)
{
	int len = strlen(_name) + 1;
	m_pName = new char[len];
	memcpy(m_pName, _name, len);
}

CUserList::~CUserList()
{
	if (m_pName) { delete[] m_pName; m_pName = nullptr; }
}
