#pragma once
#include "Scene.h"

class CNameScene : public CScene
{
public:
private:
	ID2D1SolidColorBrush* m_pRedBrush;
	D2D1_RECT_F m_target;

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