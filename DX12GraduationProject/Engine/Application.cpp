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
