#pragma once
#include "Scene.h"

class CTitleScene : public CScene
{
public:
private:

public:
	CTitleScene();
	~CTitleScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};