#include "Client.h"
#include "app.h"
#include "Direct.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Input.h"
#include "information.h"
#include "Timer.h"
#define FRAME 15

CApp::CApp()
{
	m_pGameWnd = new CGameWnd();
	m_pFps = new CFps(FRAME);
}

CApp::~CApp()
{

}

bool CApp::Initialize()
{
	if (!CClient::GetInstance()->Initialize("192.168.123.17", 30002))return false;
	if (!CDirect::GetInstance()->Initialize()) return false;
	if (!CResourceManager::GetInstance()->Initialize()) return false;
	if (!CInformation::GetInstance()->Initalize()) return false;
	if (!CSceneManager::GetInstance()->Initialize()) return false;
	if (!CInput::GetInstance()) return false;
	if (!m_pGameWnd->Initialize()) return false;
	return true;
}

void CApp::Cleanup()
{
	if (m_pFps) { delete m_pFps; m_pFps = nullptr; }
	if (m_pGameWnd) { delete m_pGameWnd; m_pGameWnd = nullptr; }
	if (CInput::GetInstance()) { CInput::GetInstance()->DeleteInstance(); }
	if (CSceneManager::GetInstance()) { CSceneManager::GetInstance()->DeleteInstance(); }
	if (CResourceManager::GetInstance()) { CResourceManager::GetInstance()->DeleteInstance(); }
	if (CClient::GetInstance()) { CClient::GetInstance()->DeleteInstance(); }
	if (CDirect::GetInstance()) { CDirect::GetInstance()->DeleteInstance(); }
}

int CApp::MessageLoop()
{
	MSG msg = { 0 };

	// gpm
	CTimer::GetInstance()->Start();

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); // ==> WndProc() È£Ãâ
		}
		if (m_pFps->IsFrame())
		{
			// gpm
			CTimer::GetInstance()->Update();
			Update();
			Render();
		}
	}
	Cleanup();
	return (int)msg.wParam;
}

void CApp::Update()
{
	m_pGameWnd->Update();
}

void CApp::Render()
{
	m_pGameWnd->Render();
}
