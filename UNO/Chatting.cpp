#include "Chatting.h"
#include "information.h"

CChatting::CChatting()
{
}

CChatting::CChatting(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color)
	: CText(_layoutRect, _fontSize, _height, _color)
{

}

CChatting::~CChatting()
{
}

void CChatting::Render(ID2D1HwndRenderTarget* _pRT)
{
	CInformation* pInformation = CInformation::GetInstance();
	CInformation::chatting_t chat = pInformation->GetChatting();
	
	CInformation::chatting_t::iterator iter = chat.begin();
	CInformation::chatting_t::iterator endIter = chat.end();
	int size = m_textHeight * chat.size();
	for (int i = 0; iter != endIter; i++)
	{
		_pRT->DrawTextW(*iter, CHAT_MAX, m_pWriteTextFormat,
			D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (m_textHeight * i - size),
				m_layoutRect.right, m_layoutRect.bottom + (m_textHeight * i - size)), m_pBrush);
		iter++;
	}
}