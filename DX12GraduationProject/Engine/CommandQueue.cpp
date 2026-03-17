#include "pch.h"
#include "CommandQueue.h"

bool CommandQueue::Initialize(ID3D12Device* device)
{
	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;

	HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&queue));
	if (FAILED(hr)) return false;

	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));
	if (FAILED(hr)) return false;

	hr = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		allocator.Get(),
		nullptr,
		IID_PPV_ARGS(&cmdList));
	if (FAILED(hr)) return false;

	cmdList->Close();

	fence = std::make_unique<Fence>();
	if (not fence->Initialize(device)) return false;

	return true;
}

void CommandQueue::Destroy()
{
	fence->WaitForGpu();
	fence->Destroy();
	fence.reset();

	cmdList.Reset();
	allocator.Reset();
	queue.Reset();
}

void CommandQueue::Open()
{
	allocator->Reset();
	cmdList->Reset(allocator.Get(), nullptr);
}

void CommandQueue::Close()
{
	cmdList->Close();
}

void CommandQueue::Execute()
{
	ID3D12CommandList* lists[] = { cmdList.Get() };
	queue->ExecuteCommandLists(1, lists);
}

void CommandQueue::Flush()
{
	Execute();
	fence->Signal(queue.Get());
	fence->WaitForGpu();
}

ID3D12CommandQueue* CommandQueue::GetQueue() const
{
	return queue.Get();
}

ID3D12GraphicsCommandList* CommandQueue::GetList() const
{
	return cmdList.Get();
}

void CommandQueue::Signal()
{
	fence->Signal(queue.Get());
}

void CommandQueue::WaitForGpu()
{
	fence->WaitForGpu();
}
