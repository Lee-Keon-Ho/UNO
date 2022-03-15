#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

CObject::CObject(spriteList_t _sprite, ID2D1Bitmap* _bitmap)
	: m_sprite(_sprite), m_bitmap(_bitmap)
{
}

CObject::CObject(CSprite* _sprite, ID2D1Bitmap* _bitmap)
	: m_bitmap(_bitmap)
{
	m_sprite.push_back(*_sprite);
}

void CObject::Render(ID2D1HwndRenderTarget* _pRT) // 하나의 sprite 여러 타겟
{
	int size = m_target.size();
	for (int i = 0; i < size; i++)
	{
		m_sprite[0].Render(_pRT, m_bitmap, m_target[i], 1.0f);
	}
}

void CObject::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{
	int size = m_target.size();
	for (int i = 0; i < size; i++)
	{
		m_sprite[i].Render(_pRT, m_bitmap, m_target[i], _alpha);
	}
}

void CObject::Render(ID2D1HwndRenderTarget* _pRT, int _index, float _alpha)
{
	m_sprite[_index].Render(_pRT, m_bitmap, m_target[_index], _alpha);
}

void CObject::Render(ID2D1HwndRenderTarget* _pRT, int* _index, float _alpha)
{
	int size = m_target.size();
	for (int i = 0; i < size; i++)
	{
		m_sprite[_index[i]].Render(_pRT, m_bitmap, m_target[i], 1.0f);
	}
}

void CObject::Render(ID2D1HwndRenderTarget* _pRT, int* _index, int _size, float _alpha)
{
	for (int i = 0; i < _size; i++)
	{
		m_sprite[_index[i]].Render(_pRT, m_bitmap, m_target[i], 1.0f);
	}
}

void CObject::SetTarget(D2D1_RECT_F _target)
{
	m_target.push_back(_target);
}