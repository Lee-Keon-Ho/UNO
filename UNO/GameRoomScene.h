#pragma once
#include "Scene.h"
#include "Button.h"
#include "ResourceManager.h"
#include "User.h"
#include "Room.h"
#include "Chatting.h"
#include "PlayerObject.h"

class CGameRoomScene : public CScene
{
public:
	typedef CResourceManager::eBitmap bitmap_t;
	typedef std::vector<CObject2D*> player_t;
	typedef std::vector<CText*> playerName_t;

	enum ePlayer
	{
		P_ONE = 0,
		P_TWO,
		P_THREE,
		P_FOUR,
		P_FIVE,
		PLAYER_MAX
	};
private:
	CObject2D* m_pBackGround;
	CObject2D* m_pChatBackGround;
	CObject2D* m_pCurrentCard;

	CPlayerObject* m_pPlayerObject;

	int fontSize;
	int m_MyNumber;
	int m_chatCount;

	wchar_t* m_chatBuffer;

	CButton* m_pExitButton;
	CButton* m_pReadyButton;
	CButton* m_pStartButton;
	CButton* m_pCurrentButton;
	CButton* m_pCenterCard;

	CText* m_pChatText;
	CChatting* m_pChatting;

	CRoom::stROOM* m_pRoomInfo;
	CUser::stUserInfo* m_pUserInfo;
	
	bool m_bChatting;
	bool m_bStart;
	bool m_bBoss;

public:
	CGameRoomScene();
	~CGameRoomScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
};