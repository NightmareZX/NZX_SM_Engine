#include "Engine.hpp"

Engine::Engine(int argc, char* argv[], size actionCount)
	: mRunning(false), mFrameAdvanceMode(false), mAdvanceFrameOnce(false), mEventHandler(actionCount)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	mRunning = true;
}

int Engine::MainLoop()
{
	Initialise();
	while (mRunning)
	{
		mGlobalTimer.TickFixedStep();
		mEventHandler.ListenForEvents();
		if (mEventHandler.GetQuitStatus()) break;

		PreUpdate();

		if (mFrameAdvanceMode && mAdvanceFrameOnce)
		{
			Update();
			Render();
		}
		else
		{
			//We use fixed time step to update game logic for easier consistency
			float& accumulator = mGlobalTimer.GetAccumulator();
			while (accumulator >= FIXED_TIME_STEP)
			{
				Update();
				Render();
				accumulator -= FIXED_TIME_STEP;
			}
		}

		PostUpdate();
	}

	PreExit();

	SDL_Quit();
	return 0;
}