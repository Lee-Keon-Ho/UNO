#include "information.h"

CInformation* CInformation::pInstance = nullptr;

CInformation* CInformation::GetInstance()
{
	if (pInstance == nullptr) { pInstance = new CInformation(); }
	return pInstance;
}

void CInformation::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CInformation::CInformation() : m_pMyName(nullptr)
{
	
}

CInformation::~CInformation()
{
	Cleanup();
}

bool CInformation::Initalize()
{
	m_pMyName = new WCHAR[255];
	memset(m_pMyName, 0, 255);
	if (m_pMyName == nullptr) return false;

	return true;
}

void CInformation::Cleanup()
{
	if (m_pMyName) { delete[] m_pMyName; m_pMyName = nullptr; }
}

void CInformation::SetName(const WCHAR* _name)
{
	int len = wcslen(_name) * sizeof(WCHAR);
	memcpy(m_pMyName, _name, len);
}

void CInformation::SetUserList(char* _user)
{
	unsigned short packetSize = *(unsigned short*)_user;
	unsigned short type = *(unsigned short*)(_user + 2);
	char* tempBuffer = _user + 4;

	int count = 0;

	while (count < packetSize - 4)
	{
		char* temp = new char[16];
		int i = 0;
		while (tempBuffer[count] != '\0')
		{
			temp[i] = tempBuffer[count];
			count++; i++;
		}
		temp[i] = tempBuffer[count];
		count++; i++;
		m_userList.clear();
		m_userList.push_back(temp);
	}
}