#pragma once
class Fence
{
public:
	bool Initialize(ID3D12Device*);
	void Destroy();

	void Signal(ID3D12CommandQueue*);
	void WaitForGpu();
	bool IsComplete() const;

private:
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceValue{};
	HANDLE fenceEvent{ nullptr };
};

