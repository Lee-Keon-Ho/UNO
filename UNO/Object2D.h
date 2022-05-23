#pragma once
#include "Sprite.h"
#include <vector>
#include <d2d1.h>
class CObject2D
{
public:
	typedef std::vector<CSprite> spriteList_t;

protected:
	spriteList_t m_sprite;
	D2D1_RECT_F  m_target;
	ID2D1Bitmap* m_bitmap;

public:
	CObject2D();
	~CObject2D();
	CObject2D(spriteList_t _sprite, ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _target);

	D2D1_RECT_F GetTarget() { return m_target; }
	
	virtual void Render(ID2D1HwndRenderTarget* _pRT);
	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int _index, float _alpha);

	void SetTarget(D2D1_RECT_F _test) { m_target = _test; }
private:
};