#pragma once
#include <Windows.h>

class CFps
{
public:
private:
	DWORD m_prevTick;		// ���� �ð�
	DWORD m_nowTick;		// ���� �ð�
	DWORD m_elapsedTick;	// ��� �ð�

	DWORD m_FrameTick;		// ������ Ȯ��
	DWORD m_NowFrame;		// ���� ������

	DWORD m_Tick;            // ��� tick 

public:
	CFps();
	CFps(DWORD _frame);
	~CFps();

	bool IsFrame();
private:
};