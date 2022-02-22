#pragma once
#include <Windows.h>

class CFps
{
public:
private:
	DWORD m_prevTick;		// 이전 시간
	DWORD m_nowTick;		// 현재 시간
	DWORD m_elapsedTick;	// 경과 시간

	DWORD m_FrameTick;		// 프레임 확인
	DWORD m_NowFrame;		// 현재 프레임

	DWORD m_Tick;            // 희망 tick 

public:
	CFps();
	CFps(DWORD _frame);
	~CFps();

	bool IsFrame();
private:
};