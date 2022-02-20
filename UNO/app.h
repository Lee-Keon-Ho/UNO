#pragma once
#include "GameWnd.h"
class CApp
{
public:
private:
	CGameWnd* m_pGameWnd;

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