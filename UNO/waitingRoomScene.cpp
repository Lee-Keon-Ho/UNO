#include "waitingRoomScene.h"
#include "Input.h"
#include "SceneManager.h"

CWaitingRoomScene::CWaitingRoomScene() : m_backGroundRect({0.0f, 0.0f, 1280.0f, 720.0f})
{
}

CWaitingRoomScene::~CWaitingRoomScene()
{
}

void CWaitingRoomScene::Awake()
{
	CResourceManager* pRM = CResourceManager::GetInstance();
	ID2D1Bitmap* pBitmap = pRM->GetBitmap(bitmap_t::WAITING);
	ID2D1Bitmap* pButtonBitmap = pRM->GetBitmap(bitmap_t::BUTTON);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject(sprite[CResourceManager::WAITING_ROOM], pBitmap, m_backGroundRect);



	m_pExitButton = new CButton(sprite[CResourceManager::WATTING_ROOM_EXIT], pButtonBitmap, { 1179.0f, 688.0f, 1280.0f, 720.0f });
}

void CWaitingRoomScene::Start()
{
}

void CWaitingRoomScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pExitButton->OnButton(mouse);

	if (key == VK_LBUTTON)
	{
		if (m_pExitButton->OnButton(mouse))
		{
			m_pExitButton->OnButtonUp();
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}
}

void CWaitingRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);

	m_pExitButton->Render(_pRT, 1.0f);

	_pRT->EndDraw();
}

void CWaitingRoomScene::Destroy()
{
}
