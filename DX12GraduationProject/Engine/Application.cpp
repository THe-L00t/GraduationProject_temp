#include "pch.h"
#include "Application.h"

void Application::Run()
{
    InitInternal();   // Window 생성, Timer::Reset()
    OnInit();

    isRunning = true;
    while (isRunning) {
        if (!window->ProcessMessages()) break;

        if (window->IsResized()) {
            OnResize(window->GetWidth(), window->GetHeight());
            window->ClearResizeFlag();
        }

        timer->Tick();
        OnUpdate(timer->GetDeltaTime());
        OnRender();    // 커맨드 기록
        OnPresent();   // Execute + Present
    }

    OnDestroy();
    DestroyInternal();
}

void Application::InitInternal()
{
    window = std::make_unique<Window>();
    window->Initialize(GetModuleHandle(nullptr), 1280, 730, L"DX12 Engine");

    timer = std::make_unique<Timer>();
    timer->Reset();
}

void Application::DestroyInternal()
{
    window->Destroy();
}

