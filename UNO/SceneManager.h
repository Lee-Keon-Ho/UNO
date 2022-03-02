#pragma once
#include <vector>
#include "Scene.h"

typedef std::vector<CScene*> scenelist_t;

enum class eScene : int
{
	TITLE_SCENE = 0,
	NAME_SCENE,
	LOBBY_SCENE,
	MAX
};

class CSceneManager final
{
private:
	static CSceneManager* pInstance;
	CSceneManager();
	~CSceneManager();

private:
	scenelist_t m_scene;

	CScene* m_currentScene;
	CScene* m_nextScene;

public:
	bool Initialize();
	void Cleanup();

	void ChangeScene(eScene _num);
	bool IsChange();
	void LoadScene();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
private:

public:
	static CSceneManager* GetInstance();
	static void DeleteInstance();
};