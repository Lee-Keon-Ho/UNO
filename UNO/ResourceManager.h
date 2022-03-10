#pragma once
#include <vector>
#include "Direct.h"
#include "Sprite.h"

#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

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
		MENU_AND_TEXT = 0,
		ICON_OK,
		MAX
	};

	enum eICON
	{
		RED = 0,
		BLUE,
		YELLOW,
		GREEN,
		OK,
		ICON_MAX
	};

private:
	bitmapList_t m_bitmap;
	spriteList_t m_redText;
	spriteList_t m_blueText;
	spriteList_t m_yellowText;
	spriteList_t m_greenText;
	spriteList_t m_OK;
	spriteList_t* m_sprite;

	ID2D1SolidColorBrush* m_pRedBrush;

public:
	bool Initialize();
	void Cleanup();

	void SetBitmap(ID2D1Bitmap* _pBitmap) { m_bitmap.push_back(_pBitmap); }
	void SetSprite(CSprite* _sprite, int _size, int _index);

	ID2D1Bitmap* GetBitmap(eBitmap _index) { return m_bitmap[_index]; }
	CSprite GetRedText(int _index) { return m_redText.at(_index); }
	CSprite GetOKIcon(int _index) { return m_OK.at(_index); }
	spriteList_t* GetSprite() { return m_sprite; }
	ID2D1SolidColorBrush** GetRedBrush() { return &m_pRedBrush; }

	void SetData(const char* _data); // 절대하지 않는다
public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};