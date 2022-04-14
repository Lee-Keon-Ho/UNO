#include "Room.h"
#include <memory>
CRoom::CRoom()
{

}

CRoom::~CRoom()
{
	
}

void CRoom::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{

}

void CRoom::SetTarget(D2D1_RECT_F _target)
{
	D2D1_RECT_F rect = _target;
	rect.top = rect.top + (51.0f * m_room.number - 1);
	rect.bottom = rect.bottom + (51.0f * m_room.number - 1);;
}