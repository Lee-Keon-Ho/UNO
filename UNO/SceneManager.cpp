#include "SceneManager.h"
#include "NameScene.h"
#include "LobbyScene.h"
#include "RoomScene.h"
#include "waitingRoomScene.h"
#include "Input.h"
CSceneManager* CSceneManager::pInstance = nullptr;

CSceneManager* CSceneManager::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CSceneManager();
	return pInstance;
}

void CSceneManager::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CSceneManager::CSceneManager() : m_currentScene(nullptr), m_nextScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	Cleanup();
}

bool CSceneManager::Initialize()
{
	m_scene.reserve((int)eScene::MAX);
	m_scene.push_back(new CNameScene());
	m_scene.push_back(new CLobbyScene());
	m_scene.push_back(new CRoomScene());
	m_scene.push_back(new CWaitingRoomScene());

	m_nextScene = m_scene[(int)eScene::NAME_SCENE];

	return true;
}

void CSceneManager::Cleanup()
{
	scenelist_t::iterator iter = m_scene.begin();
	for (; iter != m_scene.end(); iter++)
	{
		if (*iter) { delete* iter; *iter = nullptr; }
	}
}

void CSceneManager::ChangeScene(eScene _num)
{
	m_nextScene = m_scene[(int)_num];
}

bool CSceneManager::IsChange()
{
	return (m_nextScene != nullptr);
}

void CSceneManager::LoadScene()
{
	if (m_currentScene) m_currentScene->Destroy();
	m_currentScene = m_nextScene;
	m_currentScene->Awake();
	m_nextScene = nullptr;
}

void CSceneManager::Update()
{
	if (IsChange())
	{
		LoadScene();
	}
	m_currentScene->Update();
	CInput::GetInstance()->SetKey(0);
	
}

void CSceneManager::Render(ID2D1HwndRenderTarget* _pRT)
{
	if (m_currentScene) m_currentScene->Render(_pRT);
}