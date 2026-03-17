#include "pch.h"
#include "SwapChain.h"

bool SwapChain::Initialize(IDXGIFactory6*, ID3D12Device*, ID3D12CommandQueue*, HWND, uint32_t, uint32_t)
{
    return false;
}

void SwapChain::Destroy()
{
}

void SwapChain::Present(bool vsync)
{
}

void SwapChain::Resize(ID3D12Device*, uint32_t, uint32_t)
{
}

D3D12_CPU_DESCRIPTOR_HANDLE SwapChain::GetCurrentRTV() const
{
    return D3D12_CPU_DESCRIPTOR_HANDLE();
}

ID3D12Resource* SwapChain::GetCurrentBackBuffer() const
{
    return nullptr;
}

UINT SwapChain::GetCurrentIndex() const
{
    return 0;
}

void SwapChain::CreateRTVs(ID3D12Device*)
{
}

void SwapChain::ReleaseBackBuffers()
{
}
