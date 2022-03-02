#pragma once
#include "Scene.h"

class CLobbyScene : public CScene
{
public:
private:
	ID2D1SolidColorBrush* m_pRedBrush;
	unsigned int m_bOK;

public:
	CLobbyScene();
	~CLobbyScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};