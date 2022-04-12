#include "User.h"
#include <string>
CUser::CUser()
{
	memset(m_name, 0, NAME_MAX);
}

CUser::~CUser()
{
}

void CUser::SetName(wchar_t* _name)
{
	int len = sizeof(wchar_t) * wcslen(_name);
	memcpy(m_name, _name, len);
}