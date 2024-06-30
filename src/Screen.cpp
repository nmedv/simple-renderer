#include "Screen.h"

#include <Windows.h>
#include <cstdio>


#define PTR(a, b) reinterpret_cast<b>(a)


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Screen::Screen(int width, int height, const char* title)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "SimpleRenderer_Window";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wcex)) return;

	if (!(_data.hwnd = CreateWindowEx(
		0,
		"SimpleRenderer_Window",
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL))) return;

	RECT r;
	GetClientRect(PTR(_data.hwnd, HWND), &r);
	_bufferWidth = r.right - r.left;
	_bufferHeight = r.bottom - r.top;

	BITMAPINFO bmi = {};	
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = _bufferWidth;
	bmi.bmiHeader.biHeight = _bufferHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(NULL);

	_data.hbm = CreateDIBSection(
		hdc,
		&bmi,
		DIB_RGB_COLORS,
		reinterpret_cast<void**>(&_buffer),
		NULL,
		0);

	ReleaseDC(NULL, hdc);

	SetWindowLongPtr(PTR(_data.hwnd, HWND), GWLP_USERDATA, PTR(this, LONG_PTR));
	ShowWindow(PTR(_data.hwnd, HWND), SW_SHOWDEFAULT);
}


Screen::~Screen()
{
	DeleteObject(_data.hbm);
}


void Screen::setWindowTitle(const char* title)
{
	SetWindowTextA(PTR(_data.hwnd, HWND), title);
}


void Screen::pollEvents()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			_shouldClose = true;
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void Screen::flush()
{
	InvalidateRect(PTR(_data.hwnd, HWND), NULL, FALSE);
	PAINTSTRUCT paint;
	HDC hdc = BeginPaint(PTR(_data.hwnd, HWND), &paint);
	HDC hdc_bmp = CreateCompatibleDC(hdc);
	auto old_bmp = SelectObject(hdc_bmp, _data.hbm);
	RECT r;
	GetClientRect(PTR(_data.hwnd, HWND), &r);
	BitBlt(hdc, 0, 0, _bufferWidth, _bufferHeight, hdc_bmp, 0, 0, SRCCOPY);
	SelectObject(hdc, old_bmp);
	DeleteDC(hdc_bmp);
	EndPaint(PTR(_data.hwnd, HWND), &paint);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	
	case WM_DESTROY:
		PostQuitMessage(0); break;

	case WM_CLOSE:
		PostQuitMessage(0); break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0); break;
		}
		break;
	}

	default:
		return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}