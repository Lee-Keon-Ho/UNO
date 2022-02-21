#include "ResourceManager.h"

CResourceManager* CResourceManager::pInstance = nullptr;

CResourceManager* CResourceManager::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CResourceManager();
	return pInstance;
}

void CResourceManager::DeleteInstance()
{
	if (pInstance) delete pInstance;
}

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

bool CResourceManager::Initialize()
{
	m_bitmap.reserve((int)MAX);
	return true;
}

void CResourceManager::Cleanup()
{
	bitmapList_t::iterator iter = m_bitmap.begin();
	for (; iter != m_bitmap.end(); iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
}