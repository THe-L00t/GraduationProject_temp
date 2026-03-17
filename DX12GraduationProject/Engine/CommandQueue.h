#pragma once
#include "Fence.h"
#include <memory>
class CommandQueue
{
public:
	bool Initialize(ID3D12Device*);
	void Destroy();

	void Open();
	void Close();
	void Execute();
	void Flush();

	ID3D12CommandQueue* GetQueue() const;
	ID3D12GraphicsCommandList* GetList() const;

	void Signal();
	void WaitForGpu();

private:
	ComPtr<ID3D12CommandQueue> queue;
	ComPtr<ID3D12CommandAllocator> allocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;

	std::unique_ptr<Fence> fence;
};

