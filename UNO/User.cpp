#include "User.h"
#include <string>
CUser::CUser()
{
}

CUser::CUser(char* _name)
{
	int len = strlen(_name) + 1;
	memcpy(m_name, _name, len);
}

CUser::~CUser()
{
}
