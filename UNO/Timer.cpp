#include "Timer.h"
#include <d2d1.h>

CTimer* CTimer::pInstance = nullptr;

CTimer* CTimer::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CTimer();
	return pInstance;
}

void CTimer::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}


CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

void CTimer::Update()
{
	
}

