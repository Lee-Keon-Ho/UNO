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

private:
	SOCKET m_socket;
	HANDLE m_hThread;

public:
	bool Initialize(const char* _ip, int _port);
	void Cleanup();

	bool Send(char* _buffer, int _type);
	bool Send(CUser* _user, int _type);
	SOCKET GetSocket() { return m_socket; }
public:
	static CClient* GetInstance();
	static void DeleteInstance();
};