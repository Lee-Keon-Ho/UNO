#pragma once
#include "User.h"
#include "Room.h"
#include <windows.h>
#include <list>
#include <vector>

#define ROOM_MAX 8
#define USER_MAX 15

class CInformation
{
public:
	typedef std::vector<CRoom::stROOM> room_t;

	enum ePacketType
	{
		CS_PT_LOGIN = 1,
		CS_PT_CREATEROOM,
		CS_PT_USERLIST,
		CS_PT_ROOMLIST,
		CS_PT_DESTROYROOM,
		CS_PT_INROOM,
		CS_PT_MAX
	};

private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	wchar_t* m_pMyName;

	// 2022-04-19 : 수정 필요
	room_t m_roomList;

	CRoom::stROOM m_room[ROOM_MAX];
	CUser* m_pUser;

	int m_roomCount;
	int m_userCount;

public:
	bool Initalize();
	void Cleanup();

	void HandlePacket(char* _buffer);
	void CreateRoom(char* _buffer);
	void SetName(const wchar_t* _buffer);
	void SetUserList(char* _buffer);
	void SetRoomList(char* _buffer);
	wchar_t* GetName() { return m_pMyName; }
	room_t GetRoomList() { return m_roomList; }
	CUser* GetUser() { return m_pUser; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};