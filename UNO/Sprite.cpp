#include "Sprite.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
}

CSprite::CSprite(D2D1_RECT_F _rect, D2D1_POINT_2F _pivot, D2D1_SIZE_F _size) :
	m_rect(_rect), m_pivot(_pivot), m_size(_size)
{
}
