#include "text.h"
#include "Direct.h"
#include "ResourceManager.h"

#define USER_NAME_MAX 32
#define USER_MAX_COUNT 15
CText::CText()
{
	
}

CText::CText(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color)
{
	HRESULT hr;
	const wchar_t font[] = L"Consolas";

	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		font, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"en-us", &m_pWriteTextFormat);

	m_layoutRect = _layoutRect;
	m_textHeight = _height;

	if (_color == 0)
	{
		m_pBrush = *CResourceManager::GetInstance()->GetWhiteBrush();
	}
	else
	{
		m_pBrush = *CResourceManager::GetInstance()->GetBlackBrush();
	}
	
}

CText::CText(wchar_t* _pStr, D2D1_RECT_F _layoutRect, int _fontSize, int _color)
{
	HRESULT hr;
	const wchar_t font[] = L"Consolas";

	hr = CDirect::GetInstance()->GetWriteFactory()->CreateTextFormat(
		font, NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"en-us", &m_pWriteTextFormat);

	m_pStr = _pStr;
	m_size = wcslen(_pStr);
	m_layoutRect = _layoutRect;
	m_textHeight = 0.0f;
	m_pBrush = *CResourceManager::GetInstance()->GetWhiteBrush();
}

CText::~CText()
{
	CObject::~CObject();
}

void CText::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->DrawTextW(m_pStr, m_size, m_pWriteTextFormat, m_layoutRect, m_pBrush);
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, CUser* _user)
{
	// 2022-04-19 수정 : type 1 room 이랑 비슷하게 만들자 + InRoom까지 진행하자
	wchar_t* temp = _user->GetData();

	for (int i = 0; i < USER_MAX_COUNT; i++)
	{
		_pRT->DrawTextW(temp, USER_NAME_MAX, m_pWriteTextFormat,
			D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (m_textHeight * i),
				m_layoutRect.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);
		temp += USER_NAME_MAX;
	}
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, Room_t _roomList)
{
	// 2022-04-19 수정 : room class에서 나머지를 가지고 있고 render을 만들어서 text render을 하자 
	if (_roomList.size() > 0)
	{
		Room_t::iterator iter = _roomList.begin();
		D2D1_RECT_F name = { 350.0f, m_layoutRect.top, 500.0f, m_layoutRect.bottom };
		D2D1_RECT_F num = { 222.0f, m_layoutRect.top, 300.0f, m_layoutRect.bottom };
		D2D1_RECT_F playercountrect = { 605.0f , m_layoutRect.top, 700.0f, m_layoutRect.bottom };
		D2D1_RECT_F play = { 767.0f , m_layoutRect.top, 900.0f, m_layoutRect.bottom };
		for (int i = 0; iter != _roomList.end(); iter++, i++)
		{
			wchar_t number[4];
			wchar_t temp[10] = L" / 5";
			wchar_t playercount[32];
			CRoom::stROOM pRoom = *iter;
			_itow_s(pRoom.number, number, 10);
			_itow_s(pRoom.playerCount, playercount, 10);
			wcscat_s(playercount, temp);

			_pRT->DrawTextW(number, wcslen(number) + 1, m_pWriteTextFormat,
				D2D1::Rect(num.left, num.top + (m_textHeight * i),
					num.right, num.bottom + (m_textHeight * i)), m_pBrush);

			_pRT->DrawTextW(pRoom.name, wcslen(pRoom.name), m_pWriteTextFormat,
				D2D1::Rect(name.left, m_layoutRect.top + (m_textHeight * i),
					name.right, m_layoutRect.bottom + (m_textHeight * i)), m_pBrush);

			_pRT->DrawTextW(playercount, wcslen(playercount) + 1, m_pWriteTextFormat,
				D2D1::Rect(playercountrect.left, playercountrect.top + (m_textHeight * i),
					playercountrect.right, playercountrect.bottom + (m_textHeight * i)), m_pBrush);

			if (pRoom.state)
			{
				_pRT->DrawTextW(L"대기중", wcslen(L"대기중") + 1, m_pWriteTextFormat,
					D2D1::Rect(play.left, play.top + (m_textHeight * i),
						play.right, play.bottom + (m_textHeight * i)), m_pBrush);
			}
			else
			{
				_pRT->DrawTextW(L"게임중", wcslen(L"게임중") + 1, m_pWriteTextFormat,
					D2D1::Rect(play.left, play.top + (m_textHeight * i),
						play.right, play.bottom + (m_textHeight * i)), m_pBrush);
			}
		}
	}
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str)
{
	_pRT->DrawTextW(_str, wcslen(_str), m_pWriteTextFormat, m_layoutRect, m_pBrush);
}