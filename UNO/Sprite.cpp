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

void CSprite::Render(ID2D1HwndRenderTarget* _pRT, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target, float _alpha)
{
	_pRT->DrawBitmap(_bitmap, _target, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_rect);
}
