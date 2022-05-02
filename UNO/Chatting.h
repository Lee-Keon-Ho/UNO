#pragma once
#include "text.h"

#define CHAT_MAX 32

class CChatting : public CText
{
private:
	wchar_t* m_pData;
	int m_count;
public:
	CChatting();
	CChatting(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color);
	~CChatting();

	void SetList();
	void Render(ID2D1HwndRenderTarget* _pRT);
};