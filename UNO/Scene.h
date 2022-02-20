#pragma once
#include <d2d1.h>

class CScene
{
public:
protected:

public:
	CScene();
	~CScene();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render(ID2D1HwndRenderTarget* _pRT);
	virtual void Destroy();
};