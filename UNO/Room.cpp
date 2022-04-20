#include "Room.h"
#include "information.h"
#include <memory>
CRoom::CRoom()
{

}

CRoom::CRoom(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color) :
	m_nameRect({ 350.0f, 0.0f, 500.0f, 0.0f }), m_numberRect({222.0f, 0.0f, 300.0f, 0.0f}),
	m_playerCountRect({ 605.0f, 0.0f, 700.0f, 0.0f }), m_stateRect({767.0f, 0.0f, 900.0f, 0.0f})
{
	CText::init(_layoutRect, _fontSize, _height, _color); // 질문 생성자를 호출해서 사용하고 싶다.
}

CRoom::~CRoom()
{
	
}

void CRoom::Render(ID2D1HwndRenderTarget* _pRT)
{
	if (m_list.size() > 0)
	{
		room_t::iterator iter = m_list.begin();
		for (int i = 0; iter != m_list.end(); iter++, i++)
		{
			wchar_t number[4];
			wchar_t temp[10] = L" / 5";
			wchar_t playercount[32];
			CRoom::stROOM pRoom = *iter;
			_itow_s(pRoom.number, number, 10);
			_itow_s(pRoom.playerCount, playercount, 10);
			wcscat_s(playercount, temp);
			
			_pRT->DrawTextW(number, wcslen(number) + 1, CText::m_pWriteTextFormat,
				D2D1::Rect(m_numberRect.left, m_layoutRect.top + (m_textHeight * i),
					m_numberRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);

			_pRT->DrawTextW(pRoom.name, wcslen(pRoom.name), m_pWriteTextFormat,
				D2D1::Rect(m_nameRect.left, m_layoutRect.top + (m_textHeight * i),
					m_nameRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);

			_pRT->DrawTextW(playercount, wcslen(playercount) + 1, m_pWriteTextFormat,
				D2D1::Rect(m_playerCountRect.left, m_layoutRect.top + (m_textHeight * i),
					m_playerCountRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);

			if (pRoom.state)
			{
				_pRT->DrawTextW(L"대기중", wcslen(L"대기중") + 1, m_pWriteTextFormat,
					D2D1::Rect(m_stateRect.left, m_layoutRect.top + (m_textHeight * i),
						m_stateRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);
			}
			else
			{
				_pRT->DrawTextW(L"게임중", wcslen(L"게임중") + 1, m_pWriteTextFormat,
					D2D1::Rect(m_stateRect.left, m_layoutRect.top + (m_textHeight * i),
						m_stateRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);
			}
		}
	}
}

void CRoom::SetRoomList()
{
	m_list = CInformation::GetInstance()->GetRoomList();
}