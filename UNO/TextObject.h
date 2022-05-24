#pragma once
#include "Object2D.h"

class CTextObject : public CObject2D
{
public:
	typedef std::vector<CObject2D*> GameOver_t;

private:

public:
	CTextObject();
	CTextObject(spriteList_t _sprite, ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _target);
	~CTextObject();

	void Render(ID2D1HwndRenderTarget* _pRT);
};