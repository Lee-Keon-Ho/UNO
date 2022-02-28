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

void CResourceManager::SetText(CSprite* _sprite, int _size, int _index)
{
	switch (_index)
	{
	case RED:
		m_redText.reserve(_size);
		for (int i = 0; i < _size; i++)
		{
			m_redText.push_back(*_sprite);
			_sprite++;
		}
		break;
	case BLUE:
		m_blueText.reserve(_size);
		for (int i = 0; i < _size; i++)
		{
			m_blueText.push_back(*_sprite);
			_sprite++;
		}
		break;
	case YELLOW:
		m_yellowText.reserve(_size);
		for (int i = 0; i < _size; i++)
		{
			m_yellowText.push_back(*_sprite);
			_sprite++;
		}
		break;
	case GREEN:
		m_greenText.reserve(_size);
		for (int i = 0; i < _size; i++)
		{
			m_greenText.push_back(*_sprite);
			_sprite++;
		}
		break;
	case OK:
		m_OK.reserve(_size);
		for (int i = 0; i < _size; i++)
		{
			m_OK.push_back(*_sprite);
			_sprite++;
		}
		break;
	}
}