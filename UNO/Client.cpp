#include "Client.h"
#include "ResourceManager.h"
#include "information.h"
#include "PacketType.h"
#include "Room.h"
#include <stdio.h>
#include <process.h>

#pragma comment( lib, "ws2_32.lib")

#define MAX 10000

unsigned int __stdcall ThreadFunc(void* _pArgs)
{
	SOCKET socket = *(SOCKET*)_pArgs;
	char recvBuffer[MAX];
	int recvedSize = 0;
	while (1)
	{
		int recvLen = 0;
		recvLen = recv(socket, recvBuffer + recvedSize, MAX - recvedSize, 0);
		if (recvLen < 1) break;

		recvedSize += recvLen;

		if (recvedSize < 2)	break;

		unsigned short packetSize = *(unsigned short*)recvBuffer;
		unsigned short type = *(unsigned short*)(recvBuffer + 2);

		while (recvedSize >= packetSize)
		{
			CInformation::GetInstance()->HandlePacket(recvBuffer);
			recvedSize -= packetSize;
			if (recvedSize > 0)
			{
				memcpy(recvBuffer, recvBuffer + packetSize, recvedSize);
				// 2022-04-25 수정
				if (recvedSize > 1)
				{
					packetSize = *(unsigned short*)recvBuffer;
				}
				// 2022-04-25 수정
				if (recvedSize > 3)
				{
					type = *(unsigned short*)(recvBuffer + 2);
				}
			}
		}
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
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CClient::CClient()
{
}

CClient::~CClient()
{
	Cleanup();
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
	CloseHandle(m_hThread);
	closesocket(m_socket);
	WSACleanup();
}

bool CClient::Send(void* _buffer, int _type)
{
	char sendBuffer[MAX];
	char* tempBuffer = sendBuffer;

	int size = 0;
	switch (_type)
	{
	case CS_PT_LOGIN:
		size = sizeof(WCHAR) * USER_NAME_MAX_SIZE; // 2022-04-19 수정
		break;
	case CS_PT_CREATEROOM:
		size = sizeof(WCHAR) * ROOM_NAME_MAX_SIZE; // 2022-04-25 수정
		break;
	case CS_PT_USERLIST:
		break;
	case CS_PT_ROOMLIST:
		break;
	case CS_PT_OUTROOM:
		break;
	case CS_PT_INROOM:
		// 2022-04-26
		size = 2 + 2 + 32; // unsigned short + unsigned short + buffer Size 
		break;
	}
	
	*(unsigned short*)tempBuffer = 2 + 2 + size;
	tempBuffer += sizeof(unsigned short);
	*(unsigned short*)tempBuffer = _type;
	tempBuffer += sizeof(unsigned short);
	
	memcpy(tempBuffer, _buffer, size);

	int len = tempBuffer - sendBuffer + size;
	int sendSize = send(m_socket, sendBuffer, len, 0);
	if (sendSize < 0)
	{
		return false;
	}
}