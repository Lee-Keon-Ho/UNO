#pragma once
#include "Scene.h"
#include <d2d1.h>

class CNameScene : public CScene
{
public:

private:
	ID2D1SolidColorBrush* m_pRedBrush;
	D2D1_POINT_2F m_rectangle;

	D2D1_RECT_F* m_spellingTarget;
	D2D1_RECT_F* m_nameTarget;

	ID2D1Bitmap* m_pBitmap;

	unsigned int m_spellingCount;
	unsigned int m_widthMax;
	unsigned int m_heightMax;
	unsigned int m_bOK;

	char* m_name;
	int	m_count;
	int m_nameMaxSize;
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