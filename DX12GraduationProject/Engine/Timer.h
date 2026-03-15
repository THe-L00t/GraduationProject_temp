#pragma once
class Timer
{
public:
	void Reset();
	void Tick();

	float GetDeltaTime() const;
	float GetTotalTime() const;

private:
	LARGE_INTEGER	frequency{};
	LARGE_INTEGER	startTime{};
	LARGE_INTEGER	prevTime{};

	double			secsPerTick{};

	float			deltaTime{};
	double			totalTime{};
};

