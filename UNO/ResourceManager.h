#pragma once
#include <vector>
#include "Direct.h"
#include "Sprite.h"

class CResourceManager
{
private:
	static CResourceManager* pInstance;
	CResourceManager();
	~CResourceManager();

public:
	typedef std::vector<ID2D1Bitmap*> bitmapList_t;
	typedef std::vector<CSprite> spriteList_t;

	enum eBitmap
	{
		LOGIN = 0,
		LOBBY,
		BUTTON,
		CHARCTER,
		WAITING,
		EXIT,
		CREATE,
		ROOM_IN_PLAYER,
		CARD,
		READY,
		MAX
	};

	enum eICON
	{
		LOBBY_BACKGROUND = 0,
		LOGIN_BACKGROUND,
		LOGIN_BUTTON,
		LOGIN_OBJECT,
		CREATE_BUTTON,
		QUICK_BUTTON,
		CHOOSE_BUTTON,
		LOBYY_EXIT_BUTTON,
		CHARCTER_ICON,
		WAITING_ROOM,
		WATTING_ROOM_EXIT,
		EXIT_BUTTON_OK,
		EXIT_BUTTON_NO,
		EXIT_BACKGROUND,
		EXIT_TEXT_OBJECT,
		CREATE_ROOM,
		CREATE_BUTTON_NO,
		CREATE_BUTTON_OK,
		ROOM_LIST_BUTTON,
		PLAYER_ONE,
		PLAYER_TWO,
		PLAYER_THREE,
		PLAYER_FOUR,
		PLAYER_FIVE,
		UNO_CARD,
		READY_BUTTON,
		START_BUTTON,
		SECRET_CARD,
		ICON_MAX
	};

private:
	bitmapList_t m_bitmap;
	spriteList_t* m_sprite;

	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;
public:
	bool Initialize();
	void Cleanup();

	void SetBitmap(ID2D1Bitmap* _pBitmap) { m_bitmap.push_back(_pBitmap); }
	void SetSprite(CSprite* _sprite, int _size, int _index);

	ID2D1Bitmap* GetBitmap(eBitmap _index) { return m_bitmap[_index]; }
	spriteList_t* GetSprite() { return m_sprite; }
	ID2D1SolidColorBrush** GetBrush(int _color);

public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};