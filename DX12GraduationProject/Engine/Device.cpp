#include "pch.h"
#include "Device.h"

bool Device::Initialize()
{
    EnableDebugLayer();

    UINT factoryFlags = 0;
#if defined(_DEBUG)
    factoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    HRESULT hr = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&factory));
    if (FAILED(hr)) return false;

    if (not PickAdapter()) return false;
    
    hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
    if (FAILED(hr)) return false;

#if defined(_DEBUG)
    ComPtr<ID3D12InfoQueue> infoQueue;
    if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
        infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, FALSE);
    }
#endif
    return true;
    
}

void Device::Destroy()
{
    adapter.Reset();
    device.Reset();
    factory.Reset();
    
#if defined(_DEBUG)
    debugController.Reset();

    if (dxgiDebug) {
        dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL,
            (DXGI_DEBUG_RLO_FLAGS)(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
    }
    dxgiDebug.Reset();
#endif

}

ID3D12Device* Device::GetDevice() const
{
    return device.Get();
}

IDXGIFactory6* Device::GetFactory() const
{
    return factory.Get();
}

IDXGIAdapter1* Device::GetAdapter() const
{
    return adapter.Get();
}

void Device::EnableDebugLayer()
{
#if defined(_DEBUG)
    ComPtr<ID3D12Debug> debugBase;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugBase)))) {
        debugBase->EnableDebugLayer();

        if (SUCCEEDED(debugBase->QueryInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->SetEnableGPUBasedValidation(TRUE);
            debugController->SetEnableSynchronizedCommandQueueValidation(TRUE);
        }
    }

    DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));
#endif
}

bool Device::PickAdapter()
{
    for (UINT i = 0; ; ++i)
    {
        ComPtr<IDXGIAdapter1> candidate;

        HRESULT hr = factory->EnumAdapterByGpuPreference(
            i,
            DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
            IID_PPV_ARGS(&candidate)
        );

        if (hr == DXGI_ERROR_NOT_FOUND) break;

        DXGI_ADAPTER_DESC1 desc;
        candidate->GetDesc1(&desc);

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

        if (SUCCEEDED(D3D12CreateDevice(candidate.Get(),
            D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), nullptr))) {
            adapter = candidate;
            return true;
        }
    }
    return false;
}


