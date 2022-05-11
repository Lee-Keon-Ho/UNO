#pragma once
#include "User.h"
#include "Room.h"
#include <windows.h>
#include <list>
#include <vector>
#include <deque>

#define ROOM_MAX 8
#define USERLIST_MAX 15
#define CHAT_MAX 32
#define USRE_MAX 5

class CInformation
{
public:
	typedef std::vector<CRoom::stROOM> room_t;
	typedef std::deque<wchar_t*> chatting_t;

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
	CRoom::stUSER m_user[USRE_MAX]; // 2022-04-27 ����
	chatting_t m_chat;

public:
	bool Initalize();
	void Cleanup();

	void HandlePacket(char* _buffer);
	void CreateRoom(char* _create);
	void UserList(char* _userList);
	void RoomList(char* _roomList);
	void RoomIn(char* _roomin);
	void RoomOut(char* _roomOut);
	void RoomState(char* _roomState);
	void Chatting(char* _chat);
	void Start(char* _card);

	void ReSetChatting();

	void SetName(const wchar_t* _buffer);
	void SetImage(int _num) { m_MyImage = _num; }

	wchar_t* GetName() { return m_pMyName; }
	room_t GetRoomList() { return m_roomList; }
	wchar_t* GetUserList() { return m_pUserList; }
	chatting_t GetChatting() { return m_chat; }
	CRoom::stROOM* GetRoomInfo() { return &m_room; }
	CRoom::stUSER* GetUserInfo() { return m_user; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};