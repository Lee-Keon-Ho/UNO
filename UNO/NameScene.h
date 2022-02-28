#pragma once
#include "Scene.h"

class CNameScene : public CScene
{
public:
private:
	ID2D1SolidColorBrush* m_pRedBrush;
	D2D1_POINT_2F m_rectangle;

	char m_name[5] = { 0 };
	int m_count = 0;
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