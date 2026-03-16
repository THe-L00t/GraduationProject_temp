#include "pch.h"
#include "Window.h"

bool Window::Initialize(HINSTANCE hInst, uint32_t w, uint32_t h, const std::wstring& titleStr)
{
	hInstance = hInst;
	width = w;
	height = h;
	title = titleStr;
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"DX12EngineWindow";

	if (not RegisterClassEx(&wc))
		return false;

	RECT rect = { 0,0,(LONG)width, (LONG)height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr,
		hInstance,
		this
	);

	if (!hwnd)
		return false;

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	return true;
}

void Window::Destroy()
{
	if (hwnd)
	{
		DestroyWindow(hwnd);
		hwnd = nullptr;
	}
	UnregisterClass(title.c_str(), hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HWND Window::GetHwnd() const
{
	return hwnd;
}

uint32_t Window::GetWidth() const
{
	return width;
}

uint32_t Window::GetHeight() const
{
	return height;
}

bool Window::IsClosed() const
{
	return isClosed;
}

bool Window::IsResized() const
{
	return isResized;
}

void Window::ClearResizeFlag()
{
	isResized = false;
}

LRESULT Window::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* self = nullptr;

	if (msg == WM_NCCREATE) {
		auto* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		self = reinterpret_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
	}
	else {
		self = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (self)
		return self->WndProc(hWnd, msg, wParam, lParam);

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_SIZE:
	{
		uint32_t newW = LOWORD(lParam);
		uint32_t newH = HIWORD(lParam);

		isMinimized = (wParam == SIZE_MINIMIZED);

		if (not isMinimized && (newW not_eq width || newH not_eq height)) {
			width = newW;
			height = newH;
			isResized = true;
		}
		return 0;
	}
	case WM_GETMINMAXINFO:
	{
		auto* info = reinterpret_cast<MINMAXINFO*>(lParam);
		info->ptMinTrackSize = { 200,150 };
		return 0;
	}
	case WM_CLOSE:
		isClosed = true;
		return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
