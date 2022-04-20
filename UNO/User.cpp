#include "User.h"
#include "information.h"

CUser::CUser()
{

}

CUser::CUser(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color)
{
	CText::init(_layoutRect, _fontSize, _height, _color);
}

CUser::~CUser()
{

}

void CUser::SetUserList()
{
	m_pData = CInformation::GetInstance()->GetUserList();
}

void CUser::Render(ID2D1HwndRenderTarget* _pRT)
{
	wchar_t* temp = m_pData;
	for (int i = 0; i < USER_MAX; i++)
	{
		_pRT->DrawTextW(temp, USER_NAME_MAX_SIZE, m_pWriteTextFormat,
			D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (m_textHeight * i),
				m_layoutRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);
		temp += USER_NAME_MAX_SIZE;
	}
}
