#include "Object2D.h"

CObject2D::CObject2D()
{
}

CObject2D::~CObject2D()
{
}

CObject2D::CObject2D(spriteList_t _sprite, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target)
	: m_sprite(_sprite), m_bitmap(_bitmap), m_target(_target)
{
}

void CObject2D::Rneder(ID2D1HwndRenderTarget* _pRT)
{
}

void CObject2D::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{
	m_sprite[0].Render(_pRT, m_bitmap, m_target, _alpha);
}

void CObject2D::Render(ID2D1HwndRenderTarget* _pRT, int _index, float _alpha)
{
	m_sprite[_index].Render(_pRT, m_bitmap, m_target, _alpha);
}