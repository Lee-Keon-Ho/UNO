#pragma once
#include "User.h"
#include "Room.h"
#include <windows.h>
#include <list>
class CInformation
{
public:
	typedef std::list<CUser*> UserList_t;
	typedef std::list<CRoom*> RoomList_t;

	enum ePacketType
	{
		CS_PT_NICKNAME = 1,
		CS_PT_CREATEROOM,
		CS_PT_USERLIST,
		CS_PT_ROOMLIST,
		CS_PT_MAX
	};

private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	wchar_t* m_pMyName;

	UserList_t m_userList;
	RoomList_t m_roomList;
public:
	bool Initalize();
	void Cleanup();

	void Recv(char* _buffer);
	void SetName(const wchar_t* _buffer);
	void SetUserList(char* _buffer);
	void SetRoomList(char* _buffer);
	wchar_t* GetName() { return m_pMyName; }
	UserList_t* GetUserList() { return &m_userList; }
	RoomList_t* GetRoomList() { return &m_roomList; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};