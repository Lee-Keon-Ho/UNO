#include "GameOver.h"
#include "ResourceManager.h"
#include "information.h"

#define SIZE_MAX 5

CGameOver::CGameOver()
{

}

CGameOver::CGameOver(spriteList_t _sprite, ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _target)
	: CObject2D(_sprite, _bitmap, _target)
{
}

CGameOver::~CGameOver()
{

}

void CGameOver::Render(ID2D1HwndRenderTarget* _pRT)
{
	CObject2D::Render(_pRT, 1.0f);
}