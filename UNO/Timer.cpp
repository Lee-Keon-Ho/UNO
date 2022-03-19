#include "Timer.h"
#include <d2d1.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")

CTimer* CTimer::pInstance = nullptr;

CTimer* CTimer::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CTimer();
	return pInstance;
}

void CTimer::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}


CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

void CTimer::Update()
{
	
}



void CTimer::Start(void)
{
	m_prevTick = timeGetTime();;
	m_deltaTime = 0.0f;
	m_deltaTick = 0;
	m_fps = 0;
	m_fpsAvg = 0;
	m_secTick = 0;
}

void CTimer::End(void)
{
}

void CTimer::Update()
{
	DWORD nowTick = timeGetTime();

	m_deltaTick = nowTick - m_prevTick;
	m_deltaTime = (float)m_deltaTick / 1000.0f;


	m_fps++;

	// 1초를 알기 위해서
	m_secTick += m_deltaTick;
	if (m_secTick > 999)
	{
		m_secTick -= 1000;
		m_fpsAvg = m_fps;
		m_fps = 0;
	}

	m_prevTick = nowTick;
}

