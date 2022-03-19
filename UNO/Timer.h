#pragma once


// deltaTime¿ª ¿ß«— timer

class CTimer
{
private:
	static CTimer* pInstance;
	CTimer();
	~CTimer();

private:
	int m_afterTimer;
	int m_beforeTime;
	int m_periodFrequency;
	double m_timeScale;
	double m_time;


	//=================================
	// gpm 
	DWORD	m_prevTick;
	float	m_deltaTime;
	int     m_deltaTick;
	DWORD   m_secTick;
	int		m_fps;
	int		m_fpsAvg;

public :
	void Start(void);
	void End(void);

public:
	void Update();
	int GetFps(void) { return m_fpsAvg; }
	//=================================

public:
	static CTimer* GetInstance();
	static void DeleteInstance();
};