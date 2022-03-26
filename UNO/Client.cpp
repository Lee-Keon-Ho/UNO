#include "Client.h"
#include "ResourceManager.h"
#include <stdio.h>
#include <process.h>

#pragma comment( lib, "ws2_32.lib")

#define MAX 255

unsigned int __stdcall ThreadFunc(void* _pArgs)
{
	SOCKET socket = *(SOCKET*)_pArgs;
	int recvSize = 0;
	

	while (1)
	{
		char recvBuffer[MAX];
		recvSize = recv(socket, recvBuffer, MAX, 0);
		if (recvSize <= 0)
		{
			closesocket(socket);
			break;
		}
		//recvSize = CClient::GetInstance()->Recv(socket);
		//if (recvSize <= 0)break;

		//CResourceManager::GetInstance()->SetData(recvBuffer);
	}
	return 0;
}

CClient* CClient::pInstance = nullptr;

CClient* CClient::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CClient();
	return pInstance;
}

void CClient::DeleteInstance()
{
}

CClient::CClient()
{
}

CClient::~CClient()
{
}


bool CClient::Initialize(const char* _ip, int _port)
{
	WSADATA wsaData;
	SOCKADDR_IN servAddr;
	HANDLE m_hThread;
	unsigned int threadID;

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

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunc, &m_socket, 0, &threadID);

	return true;
}

void CClient::Cleanup()
{
	closesocket(m_socket);
	WSACleanup();
}

bool CClient::Send(char* _data, int _type)
{
	char sendBuffer[MAX];
	char* tempBuffer = sendBuffer;

	*(unsigned short*)tempBuffer = 2 + 2 + strlen(_data) + 1;
	tempBuffer += sizeof(unsigned short);
	*(unsigned short*)tempBuffer = _type;
	tempBuffer += sizeof(unsigned short);

	strcpy_s(tempBuffer, strlen(_data) + 1, _data);
	int len = tempBuffer - sendBuffer + strlen(_data) + 1;
	int sendSize = send(m_socket, sendBuffer, len, 0);
	if (sendSize < 0)
	{
		return false;
	}
}

int CClient::Recv(SOCKET _socket)
{
	char recvBuffer[MAX];
	int recvSize = recv(_socket, recvBuffer, MAX, 0);



	return recvSize;
}