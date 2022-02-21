#include "Direct.h"
#pragma comment( lib, "d2d1.lib")

CDirect* CDirect::pInstance = nullptr;

CDirect* CDirect::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CDirect();
	return pInstance;
}

void CDirect::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CDirect::CDirect()
{

}

CDirect::~CDirect()
{

}

bool CDirect::Initialize()
{
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) return false;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (FAILED(hr)) return false;
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return false;

	return true;
}

void CDirect::Cleanup()
{
	if (m_pWICBitmap) { m_pWICBitmap->Release(); m_pWICBitmap = nullptr; }
	if (m_pWICFactory) { m_pWICFactory->Release(); m_pWICFactory = nullptr; }
	if (m_pD2DFactory) { m_pD2DFactory->Release(); m_pD2DFactory = nullptr; }
}

HRESULT CDirect::LoadBitmapFromFile(PCWSTR _wcFileName, ID2D1Bitmap** _ppBitmap, ID2D1HwndRenderTarget* _hWndRT)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	hr = m_pWICFactory->CreateDecoderFromFilename(
		_wcFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr))return hr;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr))return hr;

	hr = m_pWICFactory->CreateBitmapFromSource(pFrame, WICBitmapCacheOnDemand, &m_pWICBitmap);
	if (FAILED(hr))return hr;

	IWICFormatConverter* pConverter = nullptr;
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr))return hr;

	hr = pConverter->Initialize(pFrame,
		GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
		NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr))return hr;

	hr = _hWndRT->CreateBitmapFromWicBitmap(
		pConverter, NULL, _ppBitmap);
	if (FAILED(hr))return hr;

	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return hr;
}