#pragma once
#include "Scene.h"
#include "Object.h"
#include "ResourceManager.h"

class CLobbyScene : public CScene
{
public:
	typedef std::vector<D2D1_RECT_F> targetList_t;

	enum TARGET
	{
		BACKGROUND,
		OK,
		MAX
	};
private:
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1Bitmap* m_pBitmap;
	ID2D1Bitmap* m_pOkBitmap;

	CObject* m_pBord;
	CObject* m_pOk;
	CObject* m_pRoomList;
	CObject* m_pUserList;
	CObject* m_pChatting;
	CObject* m_pNumText;
	CObject* m_pRoomNameText;
	CObject* m_pStateText;

	D2D1_RECT_F m_okRect;
	D2D1_RECT_F m_bordRect;
	D2D1_RECT_F m_roomRect;
	D2D1_RECT_F m_userRect;
	D2D1_RECT_F m_chatRect;

	unsigned int m_bOK;

	unsigned int m_numTextSize;
	unsigned int m_roomNameTextSize;
	unsigned int m_stateTextSize;

public:
	CLobbyScene();
	~CLobbyScene();

	void Awake();
	void Start();
	void Update();
	void Render(ID2D1HwndRenderTarget* _pRT);
	void Destroy();
private:
};