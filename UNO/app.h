#pragma once
#include "UnoWnd.h"
#include "FPS.h"

class CApp
{
public:
private:
	CUnoWnd* m_pUnoWnd;
	CFps* m_pFps;
public:
	CApp();
	~CApp();

	bool	Initialize();
	void	Cleanup();
	int		MessageLoop();

	void Update();
	void Render();
private:
};