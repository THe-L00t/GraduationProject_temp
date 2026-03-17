#include "pch.h"
#include "Fence.h"

bool Fence::Initialize(ID3D12Device* device)
{
	HRESULT hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr)) return false;

	fenceValue = 0;

	fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (not fenceEvent) return false;

	return true;
}

void Fence::Destroy()
{
	if (fenceEvent) {
		CloseHandle(fenceEvent);
		fenceEvent = nullptr;
	}
	fence.Reset();
}

void Fence::Signal(ID3D12CommandQueue* queue)
{
	++fenceValue;
	queue->Signal(fence.Get(), fenceValue);
}

void Fence::WaitForGpu()
{
	if (fence->GetCompletedValue() < fenceValue) {
		fence->SetEventOnCompletion(fenceValue, fenceEvent);
		WaitForSingleObject(fenceEvent, INFINITE);
	}
}

bool Fence::IsComplete() const
{
	return fence->GetCompletedValue() >= fenceValue;
}
