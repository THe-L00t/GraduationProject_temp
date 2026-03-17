#pragma once

static constexpr UINT BACK_BUFFER_COUNT = 2;

class SwapChain
{
public:
	bool Initialize(IDXGIFactory6*,
		ID3D12Device*,
		ID3D12CommandQueue*,
		HWND,
		uint32_t,
		uint32_t);
	void Destroy();

	void Present(bool vsync = true);
	void Resize(ID3D12Device*, uint32_t, uint32_t);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentRTV() const;
	ID3D12Resource* GetCurrentBackBuffer() const;
	UINT GetCurrentIndex() const;

private:
	void CreateRTVs(ID3D12Device*);
	void ReleaseBackBuffers();

	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12Resource> backBuffers[BACK_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

	UINT rtvDescriptorSize{ 0 };
	UINT currentIndex{ 0 };
};

