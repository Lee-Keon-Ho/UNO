#include "information.h"

#define MAX 255

CInformation* CInformation::pInstance = nullptr;

CInformation* CInformation::GetInstance()
{
	if (pInstance == nullptr) { pInstance = new CInformation(); }
	return pInstance;
}

void CInformation::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CInformation::CInformation() : m_pMyName(nullptr)
{
	
}

CInformation::~CInformation()
{
	Cleanup();
}

bool CInformation::Initalize()
{
	m_pMyName = new WCHAR[MAX];
	memset(m_pMyName, 0, MAX);
	if (m_pMyName == nullptr) return false;

	return true;
}

void CInformation::Cleanup()
{
	if (m_pMyName) { delete[] m_pMyName; m_pMyName = nullptr; }
}

void CInformation::Recv(char* _buffer)
{
	unsigned short packetSize = *(unsigned short*)_buffer;
	unsigned short type = *(unsigned short*)(_buffer + 2);

	switch (type)
	{
	case CS_PT_NICKNAME:
		SetUserList(_buffer);
		break;
	case CS_PT_CREATEROOM:
		SetRoomList(_buffer);
		break;
	case CS_PT_USERLIST:
		SetUserList(_buffer);
		break;
	}
}

void CInformation::SetName(const WCHAR* _name)
{
	memset(m_pMyName, 0, MAX);
	int len = wcslen(_name) * sizeof(WCHAR);
	memcpy(m_pMyName, _name, len);
}

void CInformation::SetUserList(char* _user)
{
	unsigned short packetSize = *(unsigned short*)_user;
	char* tempBuffer = _user + 4;

	int size = sizeof(CUser);
	int count = 0;

	// 2022-04-13 ��û ���� �� ���� delete�� �ϸ� ��������...
	UserList_t::iterator iter = m_userList.begin();
	for (; iter != m_userList.end(); iter++)
	{
		delete *iter;
	}
	m_userList.clear(); //

	while (count < packetSize - 4)
	{
		CUser* temp = new CUser();

		memcpy(temp, tempBuffer, size);

		tempBuffer += size;
		count += size;

		m_userList.push_back(temp);
	}
}

// 2022-04-13 ������� ����
void CInformation::SetRoomList(char* _room)
{
	
}