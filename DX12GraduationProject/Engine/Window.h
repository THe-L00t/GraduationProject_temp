#pragma once
class Window
{
public:
	bool Initialize(HINSTANCE, uint32_t, uint32_t, const std::wstring&);
	void Destroy();

	bool ProcessMessages();

	HWND GetHwnd() const;
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	bool IsClosed() const;
	bool IsResized() const;
	void ClearResizeFlag();

private:
	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT WndProc(HWND , UINT , WPARAM , LPARAM );

	HWND         hwnd = nullptr;
	HINSTANCE    hInstance = nullptr;
	uint32_t     width = 0;
	uint32_t     height = 0;
	std::wstring title;

	bool         isClosed = false;
	bool         isMinimized = false;
	bool         isResized = false;  
};

