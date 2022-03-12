#pragma once

class CTimer
{
public:
	static CTimer* pInstance;
	CTimer();
	~CTimer();

private:
	int m_afterTimer;
	int m_beforeTime;
	int m_periodFrequency;
	double m_timeScale;
	double m_time;

public:
	void Update();

public:
	static CTimer* GetInstance();
	static void DeleteInstance();
};