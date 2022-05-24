#include "TextObject.h"
#include "ResourceManager.h"
#include "information.h"

#define SIZE_MAX 5

CTextObject::CTextObject()
{

}

CTextObject::CTextObject(spriteList_t _sprite, ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _target)
	: CObject2D(_sprite, _bitmap, _target)
{
}

CTextObject::~CTextObject()
{

}

void CTextObject::Render(ID2D1HwndRenderTarget* _pRT)
{
	CObject2D::Render(_pRT, 1.0f);
}