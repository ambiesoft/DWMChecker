#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	BOOL isNCRenderingEnabled{ FALSE };
	HRESULT hr = ::DwmGetWindowAttribute(hWnd,
		DWMWA_NCRENDERING_ENABLED,
		&isNCRenderingEnabled,
		sizeof(isNCRenderingEnabled));

	return 0;
}
