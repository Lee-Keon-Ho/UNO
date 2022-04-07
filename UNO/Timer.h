#pragma once
#include <Windows.h>

// deltaTime�� ���� timer

class CTimer
{
private:
	static CTimer* pInstance;
	CTimer();
	~CTimer();

private:
	//=================================
	// gpm 
	DWORD	m_prevTick;
	float	m_deltaTime;
	int     m_deltaTick;
	DWORD   m_secTick;
	int		m_fps;
	int		m_fpsAvg;
	int		m_time;
public :
	void Start(void);
	void End(void);

public:
	void Update();
	int GetFps(void) { return m_fpsAvg; }
	float GetTime() { return m_time; }
	void ResetTimer() { m_time = 0; }
	//=================================

public:
	static CTimer* GetInstance();
	static void DeleteInstance();
};