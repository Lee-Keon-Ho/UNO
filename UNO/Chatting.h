#pragma once
#include "text.h"
#include <vector>
#define CHAT_MAX 32

class CChatting : public CText
{
public:
private:

public:
	CChatting();
	CChatting(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color);
	~CChatting();

	void Render(ID2D1HwndRenderTarget* _pRT);
};