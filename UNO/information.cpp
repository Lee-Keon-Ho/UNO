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