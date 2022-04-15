#include "text.h"
#include "Direct.h"
#include "ResourceManager.h"

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

}

void CText::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->DrawTextW(m_pStr, m_size, m_pWriteTextFormat, m_layoutRect, m_pBrush);
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, UserList_t _userList)
{
	if (_userList.size() > 0)
	{
		UserList_t::iterator iter = _userList.begin();

		for (int i = 0; iter != _userList.end(); iter++, i++)
		{
			wchar_t* pStr = iter.operator*()->GetName();
			_pRT->DrawTextW(pStr, wcslen(pStr), m_pWriteTextFormat,
				D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (i * m_textHeight),
					m_layoutRect.right, m_layoutRect.bottom + (i * m_textHeight)), m_pBrush);
		}
	}
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, RoomList_t _roomList) 
{
	// 2022-04-15 수정 : test중
	if (_roomList.size() > 0)// 721
	{
		RoomList_t::iterator iter = _roomList.begin();
		D2D1_RECT_F name = { 350.0f, m_layoutRect.top, 500.0f, m_layoutRect.bottom };
		D2D1_RECT_F num = { 222.0f, m_layoutRect.top, 300.0f, m_layoutRect.bottom };
		D2D1_RECT_F playercountrect = { 605.0f , m_layoutRect.top, 700.0f, m_layoutRect.bottom };
		D2D1_RECT_F play = { 767.0f , m_layoutRect.top, 900.0f, m_layoutRect.bottom };
		for (int i = 0; iter != _roomList.end(); iter++, i++)
		{
			wchar_t number[4];
			wchar_t temp[10] = L" / 5";
			wchar_t playercount[32];
			CRoom::stROOM* pRoom = iter.operator*()->GetRoom();
			_itow_s(pRoom->number, number, 10);
			_itow_s(pRoom->playerCount, playercount, 10);
			wcscat_s(playercount, temp);

			_pRT->DrawTextW(number, wcslen(number) + 1, m_pWriteTextFormat,
				D2D1::Rect(num.left, num.top + (46 * (pRoom->number - 1)),
					num.right, num.bottom + (46 * (pRoom->number - 1))), m_pBrush);

			_pRT->DrawTextW(pRoom->name, wcslen(pRoom->name), m_pWriteTextFormat,
				D2D1::Rect(name.left, m_layoutRect.top + (46 * (pRoom->number - 1)),
					name.right, m_layoutRect.bottom + (46 * (pRoom->number - 1))), m_pBrush);

			_pRT->DrawTextW(playercount, wcslen(playercount) + 1, m_pWriteTextFormat,
				D2D1::Rect(playercountrect.left, playercountrect.top + (46 * (pRoom->number - 1)),
					playercountrect.right, playercountrect.bottom + (46 * (pRoom->number - 1))), m_pBrush);

			if (pRoom->state)
			{
				_pRT->DrawTextW(L"대기중", wcslen(L"대기중") + 1, m_pWriteTextFormat,
					D2D1::Rect(play.left, play.top + (46 * (pRoom->number - 1)),
						play.right, play.bottom + (46 * (pRoom->number - 1))), m_pBrush);
			}
			else
			{
				_pRT->DrawTextW(L"게임중", wcslen(L"게임중") + 1, m_pWriteTextFormat,
					D2D1::Rect(play.left, play.top + (46 * (pRoom->number - 1)),
						play.right, play.bottom + (46 * (pRoom->number - 1))), m_pBrush);
			}
		}
	}
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str)
{
	_pRT->DrawTextW(_str, wcslen(_str), m_pWriteTextFormat, m_layoutRect, m_pBrush);
}