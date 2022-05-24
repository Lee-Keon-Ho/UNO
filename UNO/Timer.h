#pragma once
#include <Windows.h>

// deltaTime¿ª ¿ß«— timer

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
	void UpTime() { m_time += 1; }
	void ResetTimer() { m_time = 0; }
	//=================================

public:
	static CTimer* GetInstance();
	static void DeleteInstance();
};

/*
class CMessageTimer
{
private :
	std::vector<DWORD> m_timerIDs;

public :
	void Add(HWND _hWnd, DWORD _id, DWORD _timer)
	{
		SetTimer(_hWnd, _id, _timer, NULL);
	}

	void Alert(DWORD _id)
	{

	}
};
*/