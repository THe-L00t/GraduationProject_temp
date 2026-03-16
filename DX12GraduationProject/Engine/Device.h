#pragma once
class Device
{
public:
	bool Initialize();
	void Destroy();

	ID3D12Device* GetDevice() const;
	IDXGIFactory6* GetFactory() const;
	IDXGIAdapter1* GetAdapter() const;

private:
	void EnableDebugLayer();
	bool PickAdapter();

	ComPtr<IDXGIFactory6> factory;
	ComPtr<IDXGIAdapter1> adapter;
	ComPtr<ID3D12Device> device;
#if defined(_DEBUG)
	ComPtr<ID3D12Debug3> debugController;
	ComPtr<IDXGIDebug1> dxgiDebug;
#endif
};

