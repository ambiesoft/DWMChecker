#include <Windows.h>
#include <dwmapi.h>

#include <string>
#include <sstream>
#include "../../lsMisc/CreateSimpleWindow.h"
#include "../../lsMisc/GetLastErrorString.h"

#pragma comment(lib, "DWMApi.lib")

using namespace Ambiesoft;
using namespace std;


#define APP_NAME L"DWMChecker"

void FatalExit(HRESULT hr)
{
	wstring message = GetLastErrorString(hr);
	MessageBox(NULL, message.c_str(), APP_NAME, MB_ICONERROR);
	exit(1);
}

ostream& operator<<(ostream& os, const RECT& rect)
{
	os << rect.top << ',' << rect.left << ',' << rect.right << ',' << rect.bottom;
	return os;
}
wostream& operator<<(wostream& os, const RECT& rect)
{
	os << rect.top << L',' << rect.left << L',' << rect.right << L',' << rect.bottom;
	return os;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	wstringstream message;
	HWND hWnd = CreateSimpleWindow();
	HRESULT hr;
	BOOL isNCRenderingEnabled{ FALSE };
	hr = DwmGetWindowAttribute(hWnd,
		DWMWA_NCRENDERING_ENABLED,
		&isNCRenderingEnabled,
		sizeof(isNCRenderingEnabled));
	if (FAILED(hr))
	{
		FatalExit(hr);
	}

	message << L"DWMWA_NCRENDERING_ENABLED=";
	message << isNCRenderingEnabled; // ? L"TRUE" : L"FALSE";
	message << endl;// CRLF;


	RECT extendedFrameBounds{ 0, 0, 0, 0 };
	hr = DwmGetWindowAttribute(hWnd,
		DWMWA_EXTENDED_FRAME_BOUNDS,
		&extendedFrameBounds,
		sizeof(extendedFrameBounds));
	if (FAILED(hr))
	{
		FatalExit(hr);
	}


	// https://docs.microsoft.com/en-us/windows/win32/dwm/thumbnail-ovw

	message << L"DWMWA_EXTENDED_FRAME_BOUNDS=";
	message << extendedFrameBounds;
	message << endl;
	MessageBox(NULL, message.str().c_str(), APP_NAME, MB_ICONINFORMATION);
	return 0;
}
