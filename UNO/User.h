#pragma once
#include "text.h"

#define USER_NAME_MAX_SIZE 32
#define USER_MAX 15

class CUser : public CText 
{
public:
private:
	wchar_t* m_pData;

public:
	CUser();
	CUser(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color);
	~CUser();

	void SetUserList();
	wchar_t* GetData() { return m_pData; }

	void Render(ID2D1HwndRenderTarget* _pRT);
};