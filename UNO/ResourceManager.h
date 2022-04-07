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
		EXIT_BUTTON,
		CHARCTER_ICON,
		WAITING_ROOM,
		EXIT_BUTTON2,
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
	ID2D1SolidColorBrush** GetWhiteBrush() { return &m_pWhiteBrush; }
	ID2D1SolidColorBrush** GetBlackBrush() { return &m_pBlackBrush; }

public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};