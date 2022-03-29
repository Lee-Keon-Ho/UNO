#pragma once
#include <windows.h>

class CInformation
{
private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	WCHAR* m_pMyName;

public:
	bool Initalize();
	void Cleanup();

	void SetName(const WCHAR* _name);
	WCHAR* GetName() { return m_pMyName; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};