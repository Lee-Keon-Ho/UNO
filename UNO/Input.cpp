#include "Input.h"

CInput* CInput::pInstance = nullptr;

CInput* CInput::GetInstance()
{
	if (pInstance == nullptr) pInstance = new CInput();
	return pInstance;
}

void CInput::DeleteInstance()
{
	if (pInstance) { delete pInstance; pInstance = nullptr; }
}

CInput::CInput()
{
}

CInput::~CInput()
{
}
