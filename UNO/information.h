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
		CS_PT_OUTROOM,
		CS_PT_ROOMSTATE,
		CS_PT_MAX
	};

private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	wchar_t* m_pMyName;

	// 2022-04-19 : 수정
	room_t m_roomList;
	// 2022-04-20 : 수정
	wchar_t* m_pUserList;
	// 2022-04-20 : 수정 test
	CRoom::stROOM m_room;
public:
	bool Initalize();
	void Cleanup();

	void HandlePacket(char* _buffer);
	void CreateRoom(char* _buffer);
	void UserList(char* _buffer);
	void RoomList(char* _buffer);
	void RoomState(char* _buffer);

	void SetName(const wchar_t* _buffer);

	wchar_t* GetName() { return m_pMyName; }
	room_t GetRoomList() { return m_roomList; }
	wchar_t* GetUserList() { return m_pUserList; }
	CRoom::stROOM* GetRoomInfo() { return &m_room; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};