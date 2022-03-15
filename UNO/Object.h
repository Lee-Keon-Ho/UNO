#pragma once
#include "Sprite.h"
#include <vector>
#include <d2d1.h>
class CObject
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;
	typedef std::vector<CSprite> spriteList_t;
private:
	spriteList_t m_sprite;
	targetList_t m_target;
	ID2D1Bitmap* m_bitmap;

public:
	CObject();
	~CObject();
	CObject(spriteList_t _sprite, ID2D1Bitmap* _bitmap);
	CObject(CSprite* _sprite, ID2D1Bitmap* _bitmap);

	void Render(ID2D1HwndRenderTarget* _pRT);
	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int _index, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int* _index, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int* _index, int _size, float _alpha);

	void SetTarget(D2D1_RECT_F _target);
private:
};