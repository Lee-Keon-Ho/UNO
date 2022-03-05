#pragma once
#include "Scene.h"



class CNameScene : public CScene
{
public:

private:

	ID2D1SolidColorBrush* m_pRedBrush;
	D2D1_POINT_2F m_rectangle;

	char* m_name;
	int	m_count;
	unsigned int m_bOK;
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