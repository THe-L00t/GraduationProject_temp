#include "pch.h"
#include "Timer.h"

void Timer::Reset()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	prevTime = startTime;

	secsPerTick = 1.0 / static_cast<double>(frequency.QuadPart);

	deltaTime = 0.f;
	totalTime = 0.0;
}

void Timer::Tick()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double delta = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) * secsPerTick;
	double total = static_cast<double>(currentTime.QuadPart - startTime.QuadPart) * secsPerTick;

	deltaTime = static_cast<float>(delta);
	totalTime = total;
	prevTime = currentTime;
}

float Timer::GetDeltaTime() const
{
	return deltaTime;
}

float Timer::GetTotalTime() const
{
	return totalTime;
}
