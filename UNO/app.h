#pragma once
#include "GameWnd.h"
#include "FPS.h"

class CApp
{
public:
private:
	CGameWnd* m_pGameWnd;
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