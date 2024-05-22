#pragma once
#include <SDL.h>
#include "IntTypes.h"

constexpr uint32 FPS_TARGET = 60;
constexpr float FIXED_TIME_STEP = 1.0f / FPS_TARGET;

class GlobalTimer
{
public:
	GlobalTimer();
	//void Tick();
	void TickFixedStep();
	inline float GetTimeDelta() { return mTimeDelta; }
	inline float& GetAccumulator() { return mAccumulator; }

private:
	float mTimeDelta;

	uint32 mLastTime32;
	float mLastTimeF;
	float mAccumulator;
};

