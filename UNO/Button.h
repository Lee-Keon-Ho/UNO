#pragma once
#include "Object2D.h"

class CButton : public CObject2D
{
public:
private:
	int m_OnButton;
public:
	CButton();
	~CButton();
	CButton(spriteList_t _sprite, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target);

	void Render(ID2D1HwndRenderTarget* _pRT, float _alpha);
	void Render(ID2D1HwndRenderTarget* _pRT, int _num, float _alpha);

	bool OnButton(POINT _mouse);
	void OnButtonDown();
	void OnButtonUp();
	void ButtonPosition(POINT _position);
private:
};