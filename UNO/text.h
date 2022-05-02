#pragma once
#include "Object2D.h"
#include <d2d1.h>
#include <vector>

class CText : public CObject2D
{
public:
	typedef std::vector<wchar_t*> user_t;

	enum eTEXT_COLOR
	{
		T_WHITE = 0,
		T_BLACK
	};
protected:
	IDWriteTextFormat* m_pWriteTextFormat;
	ID2D1SolidColorBrush* m_pBrush;

	wchar_t* m_pStr;
	size_t m_size;
	int m_textHeight;
	D2D1_RECT_F m_layoutRect;
public:
	CText();
	CText(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color);
	CText(wchar_t* _pStr, D2D1_RECT_F _layoutRect, int _fontSize, int _color);
	~CText();

	void Render(ID2D1HwndRenderTarget* _pRT);
	void Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str);

	// 2022-05-02 ¼öÁ¤ test
	void setlayout(D2D1_RECT_F _test) { m_layoutRect = _test; }
private:
	
};