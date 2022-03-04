#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

class CServerManager
{
private:
	static CServerManager* pInstance;
	CServerManager();
	~CServerManager();
public:

private:
	SOCKET m_socket;
	HANDLE m_hThread;

public:
	bool Initialize(const char* _ip, int _port);
	void Cleanup();

	bool NickNameSend(const char* _name);

	SOCKET GetSocket() { return m_socket; }
public:
	static CServerManager* GetInstance();
	static void DeleteInstance();
};