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
	wchar_t m_wchar[4];
	POINT m_mousePosition;
public:
	void SetKey(DWORD _key) { m_key = _key; }
	void SetMousePosition(POINT _mouse) { m_mousePosition = _mouse; }
	void SetWkey(wchar_t* _str) { memcpy(m_wchar, _str, 8); }

	int GetKey() { return m_key; }
	POINT GetMousePosition() { return m_mousePosition; }
	wchar_t* GetWKey() { return m_wchar; }
public:
	static CInput* GetInstance();
	static void DeleteInstance();
};