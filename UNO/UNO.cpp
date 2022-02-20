#include <windows.h>
#include "app.h"

HINSTANCE hInst;

int CALLBACK wWinMain(
	_In_ HINSTANCE _hInstance,
	_In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPTSTR _lpCmdLine,
	_In_ int _nCmdShow
)
{
	CApp pApp;

	if (!pApp.Initialize()) return -1;
	return pApp.MessageLoop();
}