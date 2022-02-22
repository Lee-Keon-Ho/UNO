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
		MENU_AND_TEXT = 0,
		MAX
	};

	enum eColor
	{
		RED = 0,
		BLUE,
		YELLOW,
	};

private:
	bitmapList_t m_bitmap;
	spriteList_t m_redText;
	spriteList_t m_blueText;
	spriteList_t m_yellowText;

	ID2D1SolidColorBrush* m_pRedBrush;

public:
	bool Initialize();
	void Cleanup();

	void SetBitmap(ID2D1Bitmap* _pBitmap) { m_bitmap.push_back(_pBitmap); }
	void SetText(CSprite* _sprite, int _size, int _index);

	ID2D1Bitmap* GetBitmap(eBitmap _index) { return m_bitmap[_index]; }
	CSprite GetRedText(int _index) { return m_redText.at(_index); }
	CSprite GetBlueText(int _index) { return m_blueText.at(_index); }
	CSprite GetYellowText(int _index) { return m_yellowText.at(_index); }
	ID2D1SolidColorBrush** GetRedBrush() { return &m_pRedBrush; }
public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};