#pragma once
#include "Scene.h"
#include "Button.h"
#include "ResourceManager.h"
#include <d2d1.h>
 
class CNameScene : public CScene
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

	CObject* m_pBackGround;
	CObject* m_pLogin;
	CButton* m_pButton;

	D2D1_RECT_F m_buttonRect;

	char* m_pBuffer;
	WCHAR* m_pName;

	int m_bufferCount;

	unsigned m_nameMAX;
public:
	CNameScene();
	~CNameScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};