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
	case CS_PT_ROOMLIST:
		SetRoomList(_buffer);
		break;
	}
}

void CInformation::SetName(const wchar_t* _buffer)
{
	memset(m_pMyName, 0, MAX);
	int len = wcslen(_buffer) * sizeof(WCHAR);
	memcpy(m_pMyName, _buffer, len);
}

void CInformation::SetUserList(char* _buffer)
{
	unsigned short packetSize = *(unsigned short*)_buffer;
	char* tempBuffer = _buffer + 4;

	int size = sizeof(CUser);
	int count = 0;

	// 2022-04-13 요청 받을 때 마다 delete를 하면 안좋은데...
	UserList_t::iterator iter = m_userList.begin();
	for (; iter != m_userList.end(); iter++)
	{
		delete *iter;
	}
	m_userList.clear(); //
	packetSize -= 4;

	while (count < packetSize)
	{
		CUser* temp = new CUser();

		memcpy(temp, tempBuffer, size);

		tempBuffer += size;
		count += size;

		m_userList.push_back(temp);
	}
}

void CInformation::SetRoomList(char* _buffer)
{
	unsigned short packetSize = *(unsigned short*)_buffer;
	char* tempBuffer = _buffer + 4;

	int size = sizeof(CRoom);
	int count = 0;

	RoomList_t::iterator iter = m_roomList.begin();
	for (; iter != m_roomList.end(); iter++)
	{
		delete* iter;
	}
	m_roomList.clear();

	packetSize -= 4;
	while (count < packetSize)
	{
		CRoom* temp = new CRoom();

		memcpy(temp, tempBuffer, size);

		tempBuffer += size;
		count += size;

		m_roomList.push_back(temp);
	}
}