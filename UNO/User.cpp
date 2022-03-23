#include "User.h"
#include <string>
CUser::CUser()
{
}

CUser::CUser(char* _name)
{
	int len = strlen(_name) + 1;
	m_pName = new char[len];
	memcpy(m_pName, _name, len);
}

CUser::~CUser()
{
	if (m_pName) { delete[] m_pName; m_pName = nullptr; }
}
