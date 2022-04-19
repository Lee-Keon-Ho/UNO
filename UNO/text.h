#pragma once
#include "Object.h"
#include "User.h"
#include "Room.h"
#include <d2d1.h>
#include <vector>

class CText : public CObject
{
public:
	typedef std::vector<wchar_t*> user_t;
	typedef std::vector<CRoom::stROOM> Room_t;

	enum eTEXT_COLOR
	{
		T_WHITE = 0,
		T_BLACK
	};
private:
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
	void Render(ID2D1HwndRenderTarget* _pRT, CUser* _user);
	void Render(ID2D1HwndRenderTarget* _pRT, Room_t _roomList);
	void Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str);
private:
	
};