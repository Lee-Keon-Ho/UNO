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

void CText::Render(ID2D1HwndRenderTarget* _pRT, wchar_t* _str)
{
	_pRT->DrawTextW(_str, wcslen(_str), m_pWriteTextFormat, m_layoutRect, m_pBrush);
}

void CText::init(D2D1_RECT_F _layoutRect, int _fontSize, int _height, int _color)
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
