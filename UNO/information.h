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
	CRoom::stUSER m_user[5]; // 2022-04-27 수정
	wchar_t* m_pChatting;

	// 2022-05-02 수정 : test
	int m_chatCount;
public:
	bool Initalize();
	void Cleanup();

	void HandlePacket(char* _buffer);
	void CreateRoom(char* _bCreate);
	void UserList(char* _userList);
	void RoomList(char* _roomList);
	void RoomIn(char* _roomin);
	void RoomState(char* _roomState);
	void Chatting(char* _chat);

	void ReSetChatting();

	void SetName(const wchar_t* _buffer);
	void SetImage(int _num) { m_MyImage = _num; }

	wchar_t* GetName() { return m_pMyName; }
	room_t GetRoomList() { return m_roomList; }
	wchar_t* GetUserList() { return m_pUserList; }
	wchar_t* GetChatting() { return m_pChatting; }
	int GetChatCount() { return m_chatCount; }
	CRoom::stROOM* GetRoomInfo() { return &m_room; }
	CRoom::stUSER* GetUserInfo() { return m_user; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};