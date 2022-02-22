#include "app.h"
#include "Direct.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#define FRAME 10

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
	if (!CDirect::GetInstance()->Initialize()) return false;
	if (!CResourceManager::GetInstance()->Initialize()) return false;
	if (!CSceneManager::GetInstance()->Initialize()) return false;
	if (!m_pGameWnd->Initialize()) return false;
	return true;
}

void CApp::Cleanup()
{
	if (m_pFps) { delete m_pFps; m_pFps = nullptr; }
	if (m_pGameWnd) { delete m_pGameWnd; m_pGameWnd = nullptr; }
	if (CSceneManager::GetInstance()) { CSceneManager::DeleteInstance(); }
	if (CResourceManager::GetInstance()) { CResourceManager::DeleteInstance(); }
	if (CDirect::GetInstance()) { CDirect::GetInstance()->DeleteInstance(); }
}

int CApp::MessageLoop()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); // ==> WndProc() È£Ãâ
		}
		if (m_pFps->IsFrame())
		{
			Update();
			Render();
		}
		
	}
	Cleanup();
	return (int)msg.wParam;
}

void CApp::Update()
{
	CSceneManager::GetInstance()->Update();
}

void CApp::Render()
{
	CSceneManager::GetInstance()->Render(m_pGameWnd->GetRT());
}
