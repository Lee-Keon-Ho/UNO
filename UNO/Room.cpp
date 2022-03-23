#include "Room.h"
#include <memory>
CRoom::CRoom()
{

}

CRoom::CRoom(spriteList_t _sprite, ID2D1Bitmap* _bitmap)
{
	m_sprite = _sprite;
	m_bitmap = _bitmap;
}

CRoom::~CRoom()
{
	
}

void CRoom::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{
	int size = m_target.size();
	for (int i = 0; i < size; i++)
	{
		m_sprite[i].Render(_pRT, m_bitmap, m_target[i], _alpha);
	}
}

void CRoom::SetTarget(D2D1_RECT_F _target)
{
	D2D1_RECT_F rect = _target;
	rect.top = rect.top + (51.0f * m_room.number - 1);
	rect.bottom = rect.bottom + (51.0f * m_room.number - 1);;
	m_target.push_back(rect);
}
