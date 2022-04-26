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

private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	wchar_t* m_pMyName;
	int m_MyImage;
	wchar_t* m_pUserList;
	room_t m_roomList;
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
	void SetImage(int _num) { m_MyImage = _num; }

	wchar_t* GetName() { return m_pMyName; }
	room_t GetRoomList() { return m_roomList; }
	wchar_t* GetUserList() { return m_pUserList; }
	CRoom::stROOM* GetRoomInfo() { return &m_room; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};