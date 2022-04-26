#pragma once
#include "Scene.h"
#include "Button.h"
#include "text.h"
#include "ResourceManager.h"
#include <d2d1.h>
 
class CLoginScene : public CScene
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;
	typedef CResourceManager::eBitmap bitmap_t;

	enum TARGET
	{
		SPELLING = 0,
		BACKGROUND,
		TITLE,
		BAR,
		NAME,
		OK,
		MAX
	};

private:
	ID2D1SolidColorBrush* m_pBrush;
	IDWriteTextFormat* m_pWriteTextFormat;

	CObject2D* m_pBackGround;
	CObject2D* m_pLogin;
	CButton* m_pButton;
	CText* m_pName;
	D2D1_RECT_F m_buttonRect;
	D2D1_RECT_F m_nameRect;

	wchar_t* m_pBuffer;

	int m_bufferCount;

	unsigned m_nameMAX;
public:
	CLoginScene();
	~CLoginScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};