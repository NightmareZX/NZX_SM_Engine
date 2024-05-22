#include "GlobalTimer.hpp"

GlobalTimer::GlobalTimer()
{
	mLastTime32 = SDL_GetTicks();
	mTimeDelta = 0.0f;
	mLastTime32 = 0;
	mLastTimeF = 0.0f;
	mAccumulator = 0.0f;
}

void GlobalTimer::TickFixedStep()
{
	Uint32 currentTime = SDL_GetTicks();
	Uint32 timeDifference = currentTime - mLastTime32;
	mLastTime32 = currentTime;

	mTimeDelta = timeDifference / 1000.0f;

	mAccumulator += mTimeDelta;//convert to seconds
}
