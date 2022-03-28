#pragma once
#include <vector>
#include "Direct.h"
#include "Sprite.h"

//#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
//#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class CResourceManager
{
private:
	static CResourceManager* pInstance;
	CResourceManager();
	~CResourceManager();

public:
	typedef std::vector<ID2D1Bitmap*> bitmapList_t;
	typedef std::vector<CSprite> spriteList_t;

	enum TYPE
	{
		NICK_NAME = 1,
		CHATTING
	};

	enum eBitmap
	{
		LOGIN = 0,
		LOBBY,
		BUTTON,
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
		ICON_MAX
	};

private:
	bitmapList_t m_bitmap;
	spriteList_t* m_sprite;

	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;

	IDWriteTextFormat* m_pWriteTextFormat;
public:
	bool Initialize();
	void Cleanup();

	void SetBitmap(ID2D1Bitmap* _pBitmap) { m_bitmap.push_back(_pBitmap); }
	void SetSprite(CSprite* _sprite, int _size, int _index);

	ID2D1Bitmap* GetBitmap(eBitmap _index) { return m_bitmap[_index]; }
	spriteList_t* GetSprite() { return m_sprite; }
	IDWriteTextFormat** GetWriteFormat() { return &m_pWriteTextFormat; }
	ID2D1SolidColorBrush** GetRedBrush() { return &m_pRedBrush; }
	ID2D1SolidColorBrush** GetYellowBrush() { return &m_pYellowBrush; }
	ID2D1SolidColorBrush** GetBlackBrush() { return &m_pBlackBrush; }

public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};