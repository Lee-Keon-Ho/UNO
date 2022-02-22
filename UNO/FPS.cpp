#include "FPS.h"
#pragma comment( lib, "winmm.lib")
CFps::CFps() :
	m_prevTick(0), m_nowTick(0),
	m_elapsedTick(0), m_NowFrame(0),
	m_FrameTick(0), m_Tick(1000 / 20)
{

}

CFps::CFps(DWORD _frame) :
	m_prevTick(0), m_nowTick(0),
	m_elapsedTick(0), m_NowFrame(0),
	m_FrameTick(0), m_Tick(1000 / _frame)
{
	if (m_prevTick == 0) m_prevTick = timeGetTime();
}

CFps::~CFps()
{

}

bool CFps::IsFrame()
{
	m_nowTick = timeGetTime();

	m_elapsedTick = m_nowTick - m_prevTick;
	// 1000 / n << n이 프레임 설정
	if (m_elapsedTick >= m_Tick)  // m_Tick
	{
		m_FrameTick++;
		m_prevTick += m_Tick;
		return true;
	}
	return false;
}