#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "User.h"

class CClient
{
private:
	static CClient* pInstance;
	CClient();
	~CClient();
public:
	enum ePacketType
	{
		CS_PT_LOGIN = 1,
		CS_PT_CREATEROOM,
		CS_PT_USERLIST,
		CS_PT_ROOMLIST,
		CS_PT_DESTROYROOM,
		CS_PT_INROOM,
		CS_PT_ROOMSTATE,
		CS_PT_MAX
	};
private:
	SOCKET m_socket;
	HANDLE m_hThread;

public:
	bool Initialize(const char* _ip, int _port);
	void Cleanup();

	bool Send(void* _buffer, int _type);
	SOCKET GetSocket() { return m_socket; }
public:
	static CClient* GetInstance();
	static void DeleteInstance();
};