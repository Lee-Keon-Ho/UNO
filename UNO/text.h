#pragma once
#include "Object.h"
#include "User.h"
#include "Room.h"
#include <d2d1.h>
#include <list>

class CText : public CObject
{
public:
	typedef std::list<CUser*> UserList_t;
	typedef std::list<CRoom*> RoomList_t;
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
	void Render(ID2D1HwndRenderTarget* _pRT, UserList_t _userList);
	void Render(ID2D1HwndRenderTarget* _pRT, RoomList_t _roomList);
	void Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str);
private:
	
};