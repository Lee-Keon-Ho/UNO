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

void CInformation::HandlePacket(char* _buffer)
{
	unsigned short type = *(unsigned short*)(_buffer + 2);

	switch (type)
	{
	case CS_PT_LOGIN:
		SetUserList(_buffer);
		break;
	case CS_PT_CREATEROOM:
		break;
	case CS_PT_USERLIST:
		SetUserList(_buffer);
		break;
	case CS_PT_ROOMLIST:
		SetRoomList(_buffer);
		break;
	}
}

void CInformation::CreateRoom(char* _buffer)
{

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

	// 2022-04-18 여긴 list가 아니라 전광판이다! + 번호로 몇번 방인지 확인한다
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
	// 2022-04-16 수정 : 수업중 말씀해주신 방향으로 생각해서.
	// 이건 전광판이다 
	unsigned short packetSize = *(unsigned short*)_buffer;
	char* tempBuffer = _buffer + 4;

	int size = sizeof(CRoom::stROOM);
	int count = 0;

	m_roomList.clear();

	packetSize -= 4;
	while (count < packetSize)
	{
		CRoom::stROOM temp;

		memcpy(&temp, tempBuffer, size);

		tempBuffer += size;
		count += size;

		m_roomList.push_back(temp);
	}
}