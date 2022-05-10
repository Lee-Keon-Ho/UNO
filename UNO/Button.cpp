#include "Button.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

CButton::CButton(spriteList_t _sprite, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target) : m_OnButton(0)
{
	m_sprite = _sprite;
	m_bitmap = _bitmap;
	m_target = _target;
}

void CButton::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{
	CObject2D::Render(_pRT, m_OnButton, _alpha);
}

void CButton::Render(ID2D1HwndRenderTarget* _pRT, int _num, float _alpha)
{
	CObject2D::Render(_pRT, _num, _alpha);
}

bool CButton::OnButton(POINT _mouse)
{
	if (_mouse.x >= m_target.left && _mouse.x <= m_target.right &&
		_mouse.y >= m_target.top && _mouse.y <= m_target.bottom)
	{
		m_OnButton = !m_OnButton;
		return true;
	}
	return false;
}

void CButton::OnButtonDown()
{
	m_OnButton = 1;
}

void CButton::OnButtonUp()
{
	m_OnButton = 0;
}

void CButton::ButtonPosition(POINT _position)
{
	if (_position.x >= m_target.left && _position.x <= m_target.right &&
		_position.y >= m_target.top && _position.y <= m_target.bottom)
	{
		m_OnButton = 1;
	}
	else m_OnButton = 0;
}
