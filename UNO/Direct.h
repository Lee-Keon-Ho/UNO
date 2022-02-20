#pragma once
#include <d2d1.h>
#include <wincodec.h>

class CDirect
{
private:
	static CDirect* pInstance;

private:
	IWICImagingFactory* m_pWICFactory;
	ID2D1Factory* m_pD2DFactory;
	IWICBitmap* m_pWICBitmap;

private:
	CDirect();
	~CDirect();

public:
	bool Initialize();
	void Cleanup();

	HRESULT LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap, ID2D1HwndRenderTarget* _hWndRT);

	ID2D1Factory* GetD2DFactory() { return m_pD2DFactory; }
public:
	static CDirect* GetInstance();
	static void DeleteInstance();
};