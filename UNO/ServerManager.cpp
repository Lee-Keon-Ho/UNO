#include <stdio.h>
#include <process.h>
#include "ServerManager.h"
#include "ResourceManager.h"

#pragma comment( lib, "ws2_32.lib")

#define MAX 255

unsigned int __stdcall ThreadFunc(void* _pArgs)
{
	SOCKET socket = (SOCKET)_pArgs;
	int recvSize = 0;

	while (1)
	{
		char* recvData = new char[MAX];
		recvSize = recv(socket, recvData, MAX, 0);
		if (recvSize <= 0)break;

		CResourceManager::GetInstance()->SetDate(recvData);
	}
	return 0;
}

CServerManager* CServerManager::pInstance = nullptr;

CServerManager* CServerManager::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CServerManager();
	return pInstance;
}

void CServerManager::DeleteInstance()
{
}

CServerManager::CServerManager()
{
}

CServerManager::~CServerManager()
{
}


bool CServerManager::Initialize(const char* _ip, int _port)
{
	WSADATA wsaData;
	SOCKADDR_IN servAddr;

	HANDLE m_hThread;
	unsigned int m_threadID;

	int sendSize;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) return false;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, _ip, &servAddr.sin_addr);
	servAddr.sin_port = htons(_port);


	if (connect(m_socket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		return false;

	return true;
}

void CServerManager::Cleanup()
{
	closesocket(m_socket);
	WSACleanup();
}

bool CServerManager::NickNameSend(const char* _name)
{
	unsigned int threadID;
	char sendBuffer[100];
	char* tempBuffer = sendBuffer;

	*(unsigned short*)tempBuffer = 2 + 2 + strlen(_name) + 1; // sizeof(unsigned short) == 2
	tempBuffer += sizeof(unsigned short);
	*(unsigned short*)tempBuffer = 1;
	tempBuffer += sizeof(unsigned short);

	strcpy_s(tempBuffer, strlen(_name) + 1, _name);
	int len = tempBuffer - sendBuffer + strlen(_name) + 1;
	int sendSize = send(m_socket, sendBuffer, len, 0);
	if (sendSize < 0)
	{
		return false;
	}

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunc, &m_socket, 0, &threadID);
	Sleep(10);
	return true;
}