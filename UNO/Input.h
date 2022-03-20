#pragma once
#include <Windows.h>

class CInput
{
private:
	static CInput* pInstance;
	CInput();
	~CInput();

private:
	int m_key;
	POINT m_mousePosition;
public:
	void SetKey(DWORD _key) { m_key = _key; }
	void SetMousePosition(POINT _mouse) { m_mousePosition = _mouse; }

	int GetKey() { return m_key; }
	POINT GetMousePosition() { return m_mousePosition; }
public:
	static CInput* GetInstance();
	static void DeleteInstance();
};