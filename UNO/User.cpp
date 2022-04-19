#include "User.h"
#include <string>

#define NAME_MAX 32
#define USER_MAX 15

CUser::CUser()
{
	m_pData = new wchar_t[USER_MAX * NAME_MAX];
	memset(m_pData, 0, (USER_MAX * NAME_MAX) * sizeof(wchar_t));
}

CUser::~CUser()
{
	if (m_pData) { delete[] m_pData; }
}

void CUser::SetData(char* _name, int _size)
{
	memset(m_pData, 0, (USER_MAX * NAME_MAX) * sizeof(wchar_t));
	memcpy(m_pData, _name, _size);
}