#include "Button.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

CButton::CButton(spriteList_t _sprite, ID2D1Bitmap* _bitmap, D2D1_RECT_F _target)
{
	m_sprite = _sprite;
	m_bitmap = _bitmap;
	m_target = _target;
}

void CButton::Render(ID2D1HwndRenderTarget* _pRT, float _alpha)
{
	CObject2D::Render(_pRT, m_OnButton, _alpha);
}

bool CButton::OnButton(POINT _mouse)
{
	if (_mouse.x >= m_target.left && _mouse.x <= m_target.right &&
		_mouse.y >= m_target.top && _mouse.y <= m_target.bottom)
	{
		m_OnButton = 1;
		return true;
	}
	else m_OnButton = 0;
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
