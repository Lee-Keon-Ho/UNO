#include "ResourceManager.h"

CResourceManager* CResourceManager::pInstance = nullptr;

CResourceManager* CResourceManager::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CResourceManager();
	return pInstance;
}

void CResourceManager::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CResourceManager::CResourceManager()
{
	
}

CResourceManager::~CResourceManager()
{
	
}

bool CResourceManager::Initialize()
{
	m_sprite = new spriteList_t[eICON::ICON_MAX];
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
	if (m_sprite) { delete[] m_sprite; m_sprite = nullptr; }
}

void CResourceManager::SetSprite(CSprite* _sprite, int _size, int _index)
{
	m_sprite[_index].reserve(_size);
	for (int i = 0; i < _size; i++)
	{
		m_sprite[_index].push_back(*_sprite);
		_sprite++;
	}
}

ID2D1SolidColorBrush** CResourceManager::GetBrush(int _color)
{
	switch (_color)
	{
	case 0:
		return &m_pWhiteBrush;
	case 1:
		return &m_pBlackBrush;
	case 2:
		return &m_pRedBrush;
	default:
		return nullptr;
	}
}
