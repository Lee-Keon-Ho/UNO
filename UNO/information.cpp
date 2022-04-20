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
	m_pUserList = new wchar_t[USER_MAX * USER_NAME_MAX_SIZE];
	m_pMyName = new WCHAR[MAX];
	memset(m_pMyName, 0, MAX);
	if (m_pMyName == nullptr) return false;

	return true;
}

void CInformation::Cleanup()
{
	if (m_pMyName) { delete[] m_pMyName; m_pMyName = nullptr; }
	if (m_pUserList) { delete[] m_pUserList; m_pUserList = nullptr; }
}

void CInformation::HandlePacket(char* _buffer)
{
	unsigned short type = *(unsigned short*)(_buffer + 2);

	switch (type)
	{
	case CS_PT_LOGIN:
		UserList(_buffer);
		break;
	case CS_PT_CREATEROOM:
		break;
	case CS_PT_USERLIST:
		UserList(_buffer);
		break;
	case CS_PT_ROOMLIST:
		RoomList(_buffer);
		break;
	case CS_PT_INROOM:
		break;
	case CS_PT_ROOMSTATE:
		RoomState(_buffer);
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

void CInformation::UserList(char* _buffer)
{
	unsigned short packetSize = *(unsigned short*)_buffer;
	char* tempBuffer = _buffer + 4;

	memset(m_pUserList, 0, (USER_MAX * USER_NAME_MAX_SIZE) * sizeof(wchar_t));
	memcpy(m_pUserList, tempBuffer, packetSize - 4);
}

void CInformation::RoomList(char* _buffer)
{
	// 2022-04-19 수정 : 완료
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

void CInformation::RoomState(char* _buffer)
{
	unsigned short packetSize = *(unsigned short*)_buffer;
	char* tempBuffer = _buffer + 4;

	memcpy(&m_room, tempBuffer, sizeof(CRoom::stROOM));
}