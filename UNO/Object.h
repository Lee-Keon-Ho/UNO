#pragma once
#include "Sprite.h"
#include <vector>
#include <d2d1.h>
class CObject // 2022-04-23 ¼öÁ¤ : Object2D
{
public:
	typedef std::vector<CSprite> spriteList_t;

protected:
	spriteList_t m_sprite;
	D2D1_RECT_F  m_target;
	ID2D1Bitmap* m_bitmap;

public:
	CObject();
	~CObject();
	CObject(spriteList_t _sprite, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target);

	virtual void Rneder(ID2D1HwndRenderTarget* _pRT);
	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int _index, float _alpha);

	void SetTarget(D2D1_RECT_F _target);
private:
};