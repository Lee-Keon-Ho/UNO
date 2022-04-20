#include "Client.h"
#include "waitingRoomScene.h"
#include "timer.h"
#include "Input.h"
#include "SceneManager.h"
#include "information.h"

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
	ID2D1Bitmap* pPlayerCountBitmap = pRM->GetBitmap(bitmap_t::ROOM_IN_PLAYER);
	CResourceManager::spriteList_t* sprite = pRM->GetSprite();

	m_pBackGround = new CObject(sprite[CResourceManager::WAITING_ROOM], pBitmap, m_backGroundRect);

	m_pExitButton = new CButton(sprite[CResourceManager::WATTING_ROOM_EXIT], pButtonBitmap, { 1179.0f, 686.0f, 1280.0f, 720.0f });

	//2022-04-20 ¼öÁ¤ : test
	m_pRoominfo = CInformation::GetInstance()->GetRoomInfo();
	m_player.reserve(PLAYER_MAX);
	m_player.push_back(new CObject(sprite[CResourceManager::ROOM_PLAYER], pPlayerCountBitmap, { 413.0f, 450.0f, 867.0f, 698.0f }));
	m_player.push_back(new CObject(sprite[CResourceManager::ROOM_PLAYER], pPlayerCountBitmap, { 13.0f, 150.0f, 413.0f, 500.0f }));
	m_player.push_back(new CObject(sprite[CResourceManager::ROOM_PLAYER], pPlayerCountBitmap, { 913.0f, 450.0f, 1280.0f, 698.0f }));
	m_player.push_back(new CObject(sprite[CResourceManager::ROOM_PLAYER], pPlayerCountBitmap, { 13.0f, 500.0f, 413.0f, 698.0f }));
	m_player.push_back(new CObject(sprite[CResourceManager::ROOM_PLAYER], pPlayerCountBitmap, { 913.0f, 450.0f, 1280.0f, 698.0f }));
}

void CWaitingRoomScene::Start()
{
}

void CWaitingRoomScene::Update()
{
	CInput* pInput = CInput::GetInstance();
	CTimer* pTimer = CTimer::GetInstance();
	POINT mouse = pInput->GetMousePosition();
	int key = pInput->GetKey();

	m_pExitButton->OnButton(mouse);

	if (key == VK_LBUTTON)
	{
		if (m_pExitButton->OnButton(mouse))
		{
			char buffer[] = "destroy";
			m_pExitButton->OnButtonUp();
			CClient::GetInstance()->Send(buffer, CClient::CS_PT_DESTROYROOM);
			CSceneManager::GetInstance()->ChangeScene(eScene::LOBBY_SCENE);
		}
	}

	if (pTimer->GetTime() >= 1)
	{
		char buffer[] = "game";
		CClient::GetInstance()->Send(buffer, CInformation::CS_PT_ROOMSTATE);
		m_pRoominfo = CInformation::GetInstance()->GetRoomInfo();
		pTimer->ResetTimer();
	}
}

void CWaitingRoomScene::Render(ID2D1HwndRenderTarget* _pRT)
{
	_pRT->BeginDraw();

	m_pBackGround->Render(_pRT, 1.0f);

	for (int i = 0; i < m_pRoominfo->playerCount; i++)
	{
		m_player[i]->Render(_pRT, 1.0f);
	}

	m_pExitButton->Render(_pRT, 1.0f);

	

	_pRT->EndDraw();
}

void CWaitingRoomScene::Destroy()
{
}
