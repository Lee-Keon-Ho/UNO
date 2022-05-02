#include "Chatting.h"
#include "information.h"

CChatting::CChatting()
{
}

CChatting::CChatting(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color)
	: CText(_layoutRect, _fontSize, _height, _color), m_count(0)
{

}

CChatting::~CChatting()
{
}

void CChatting::SetList()
{
	m_pData = CInformation::GetInstance()->GetChatting();
}

void CChatting::Render(ID2D1HwndRenderTarget* _pRT)
{
	CInformation* pInformation = CInformation::GetInstance();
	wchar_t* temp = m_pData;
	m_count = pInformation->GetChatCount();
	int size = 15 * m_count;
	for (int i = 0; i < m_count; i++)
	{
		_pRT->DrawTextW(temp, CHAT_MAX, m_pWriteTextFormat,
			D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (m_textHeight * i - size),
				m_layoutRect.right, m_layoutRect.bottom + (m_textHeight * i - size)), m_pBrush);
		temp += CHAT_MAX;
	}
}