#pragma once
#include "Object2D.h"

class CGameOver : public CObject2D
{
public:
	typedef std::vector<CObject2D*> GameOver_t;

private:

public:
	CGameOver();
	CGameOver(spriteList_t _sprite, ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _target);
	~CGameOver();

	void Render(ID2D1HwndRenderTarget* _pRT);
};