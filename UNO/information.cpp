#include "information.h"
#include "PacketType.h"
#include "SceneManager.h"

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

	memset(m_user, 0, sizeof(CUser::stUserInfo) * USRE_MAX);

	m_pCard = new int[USER_CARD_MAX];
	memset(m_pCard, -1, USER_CARD_MAX);
	return true;
}

void CInformation::Cleanup()
{
	chatting_t::iterator iter = m_chat.begin();
	chatting_t::iterator endIter = m_chat.end();
	for (; iter != endIter; iter++)
	{
		delete* iter; *iter = nullptr;
	}
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
		CreateRoom(_buffer);
		break;
	case CS_PT_USERLIST:
		UserList(_buffer);
		break;
	case CS_PT_ROOMLIST:
		RoomList(_buffer);
		break;
	case CS_PT_INROOM:
		RoomIn(_buffer);
		break;
	case CS_PT_OUTROOM:
		RoomOut(_buffer);
		break;
	case CS_PT_ROOMSTATE:
		RoomState(_buffer);
		break;
	case CS_PT_CHATTING:
		Chatting(_buffer);
		break;
	case CS_PT_START:
		Start(_buffer);
		break;
	case CS_PT_RESET:
		CSceneManager::GetInstance()->ChangeScene(eScene::WAITING_SCENE);
		break;
	}
}

void CInformation::CreateRoom(char* _create)
{
	char* tempBuffer = _create;
	unsigned short packetSize = *(unsigned short*)tempBuffer;
	tempBuffer += sizeof(unsigned short) * 2;
	bool bCreate = tempBuffer;
	tempBuffer += sizeof(unsigned short);
	m_room.playerCount = *(unsigned short*)tempBuffer;
	tempBuffer += sizeof(unsigned short);

	memcpy(&m_room, tempBuffer, sizeof(CRoom::stROOM));
	tempBuffer += sizeof(CRoom::stROOM);
	memcpy(m_user, tempBuffer, sizeof(CUser::stUserInfo) * m_room.playerCount);

	if (bCreate)
	{
		CSceneManager::GetInstance()->ChangeScene(eScene::WAITING_SCENE);
	}
}

void CInformation::SetName(const wchar_t* _buffer)
{
	memset(m_pMyName, 0, MAX);
	int len = wcslen(_buffer) * sizeof(WCHAR);
	memcpy(m_pMyName, _buffer, len);
}

void CInformation::UserList(char* _userList)
{
	unsigned short packetSize = *(unsigned short*)_userList;
	char* tempBuffer = _userList + 4;

	memset(m_pUserList, 0, (USERLIST_MAX * USER_NAME_MAX_SIZE) * sizeof(wchar_t));
	memcpy(m_pUserList, tempBuffer, packetSize - 4);
}

void CInformation::RoomList(char* _roomList)
{
	unsigned short packetSize = *(unsigned short*)_roomList;
	char* tempBuffer = _roomList + 4;

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

void CInformation::RoomIn(char* _roomin)
{
	char* tempBuffer = _roomin;
	unsigned short packetSize = *(unsigned short*)tempBuffer;
	tempBuffer += sizeof(unsigned short) * 2;
	bool bRoomIn = tempBuffer;
	tempBuffer += sizeof(unsigned short);

	memcpy(&m_room, tempBuffer, sizeof(CRoom::stROOM));
	tempBuffer += sizeof(CRoom::stROOM);
	
	memcpy(m_user, tempBuffer, sizeof(CUser::stUserInfo) * m_room.playerCount);

	if (bRoomIn)
	{
		CSceneManager::GetInstance()->ChangeScene(eScene::WAITING_SCENE);
	}
}

void CInformation::RoomOut(char* _roomOut)
{
	CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
}

void CInformation::RoomState(char* _roomState)
{
	char* tempBuffer = _roomState;
	unsigned short packetSize = *(unsigned short*)tempBuffer;
	tempBuffer += sizeof(unsigned short) + 2;

	m_currentCard = *(unsigned short*)tempBuffer;
	tempBuffer += sizeof(unsigned short);

	memcpy(m_pCard, tempBuffer, sizeof(int) * USER_CARD_MAX);
	tempBuffer += sizeof(int) * USER_CARD_MAX;

	memcpy(&m_room, tempBuffer, sizeof(CRoom::stROOM));
	tempBuffer += sizeof(CRoom::stROOM);

	memcpy(m_user, tempBuffer, sizeof(CUser::stUserInfo) * m_room.playerCount);
}

void CInformation::Chatting(char* _chat)
{
	unsigned short packetSize = *(unsigned short*)_chat;
	char* tempBuffer = _chat + 4;
	WCHAR* chat = new WCHAR[CHAT_MAX];
	memset(chat, 0, sizeof(WCHAR) * CHAT_MAX);
	memcpy(chat, tempBuffer, packetSize - 4);
	if (m_chat.size() > 13) m_chat.pop_front();
	m_chat.push_back(chat);
}

void CInformation::Start(char* _card)
{
	unsigned short packetSize = *(unsigned short*)_card;
	char* tempBuffer = _card + 4;

	memcpy(m_pCard, tempBuffer, sizeof(int) * USER_CARD_MAX);
}

void CInformation::ReSetChatting()
{
	chatting_t::iterator iter = m_chat.begin();
	chatting_t::iterator endIter = m_chat.end();
	for (; iter != endIter; iter++)
	{
		delete* iter; *iter = nullptr;
	}
	m_chat.clear();
}