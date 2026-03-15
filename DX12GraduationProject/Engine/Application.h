#pragma once
#include <memory>
#include "Window.h"
#include "Timer.h"

class Application
{
public:
	void Run();
	void Quit() { isRunning = false; };

	Window* GetWindow() const { return window.get(); };
	Timer* GetTimer() const { return timer.get(); };

protected:
    // DX12 커맨드 3단계에 대응하는 훅
    virtual void OnInit() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}  // Command List 기록
    virtual void OnPresent() {}  // Execute + SwapChain::Present
    virtual void OnResize(uint32_t w, uint32_t h) {}
    virtual void OnDestroy() {}

    // 서브시스템 소유 (초기화 순서 = 선언 순서)
    std::unique_ptr<Window> window;
    std::unique_ptr<Timer>  timer;
    // std::unique_ptr<Device> m_device;   ← 1주차 후반 추가

private:
    void InitInternal();
    void DestroyInternal();

    bool isRunning = false;
};

