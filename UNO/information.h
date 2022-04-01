#pragma once
#include <windows.h>
#include <list>
class CInformation
{
public:
	typedef std::list<char*> UserList_t;

private:
	static CInformation* pInstance;
	CInformation();
	~CInformation();
private:
	WCHAR* m_pMyName;
	UserList_t m_userList;
public:
	bool Initalize();
	void Cleanup();

	void SetName(const WCHAR* _name);
	void SetUserList(char* _user);
	WCHAR* GetName() { return m_pMyName; }
	UserList_t GetUserList() { return m_userList; }
public:
	static CInformation* GetInstance();
	static void DeleteInstance();
};