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
	UserList_t::iterator iter = _userList.begin();

	for (int i = 0; iter != _userList.end(); iter++, i++)
	{
		wchar_t* pStr = iter.operator*()->GetName();
		_pRT->DrawTextW(pStr, wcslen(pStr), m_pWriteTextFormat,
			D2D1::Rect(m_layoutRect.left, m_layoutRect.top + (i * m_textHeight),
				m_layoutRect.right, m_layoutRect.bottom + (i * m_textHeight)), m_pBrush);
	}
}

void CText::Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str)
{
	_pRT->DrawTextW(_str, wcslen(_str), m_pWriteTextFormat, m_layoutRect, m_pBrush);
}