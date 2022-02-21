#pragma once
#include <vector>
#include "Direct.h"

class CResourceManager
{
private:
	static CResourceManager* pInstance;
	CResourceManager();
	~CResourceManager();

public:
	typedef std::vector<ID2D1Bitmap*> bitmapList_t;

	enum eBitmap
	{
		MENU_AND_TEXT = 0,
		MAX
	};

private:
	bitmapList_t m_bitmap;

public:
	bool Initialize();
	void Cleanup();

	ID2D1Bitmap* GetBitmap(eBitmap _index) { return m_bitmap[_index]; }
	void SetBitmap(ID2D1Bitmap* _pBitmap) { m_bitmap.push_back(_pBitmap); }

public:
	static CResourceManager* GetInstance();
	static void DeleteInstance();
};