#pragma once
#include <d2d1.h>

class CSprite
{
public:
private:
	D2D1_RECT_F m_rect;
	D2D1_POINT_2F m_pivot;
	D2D1_SIZE_F m_size;

public:
	CSprite();
	~CSprite();
	CSprite(D2D1_RECT_F _rect);
	CSprite(D2D1_RECT_F _rect, D2D1_POINT_2F _pivot, D2D1_SIZE_F _size);
	D2D1_RECT_F GetRect() { return m_rect; }

	void Render(ID2D1HwndRenderTarget* _pRT, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target, float _alpha);
private:
};