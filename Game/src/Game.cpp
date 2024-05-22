#include "Game.hpp"

Game::Game(int argc, char* argv[]) : 
	Engine(argc, argv, static_cast<size>(GameAction::ActionsCount))
{

}

void Game::Initialise()
{
	//mRenderer.RegisterFont("subversion", "C:\\Users\\Owner\\source\\repos\\SM_Engine\\Assets\\", "subversion_font.xml");

	mEventHandler.SetAction(static_cast<size>(GameAction::MOVE_LEFT), SDL_Scancode::SDL_SCANCODE_LEFT);
	mEventHandler.SetAction(static_cast<size>(GameAction::MOVE_RIGHT), SDL_Scancode::SDL_SCANCODE_RIGHT);
	mEventHandler.SetAction(static_cast<size>(GameAction::JUMP), SDL_Scancode::SDL_SCANCODE_A);
	mEventHandler.SetAction(static_cast<size>(GameAction::DOWN), SDL_Scancode::SDL_SCANCODE_DOWN);
	mEventHandler.SetAction(static_cast<size>(GameAction::DEBUG_LOG_SDL_ERROR), SDL_Scancode::SDL_SCANCODE_P);
	mEventHandler.SetAction(static_cast<size>(GameAction::DEBUG_RESTART_MUSIC), SDL_Scancode::SDL_SCANCODE_K);
	mEventHandler.SetAction(static_cast<size>(GameAction::DEBUG_ENABLE_FRAME_ADVANCE), SDL_Scancode::SDL_SCANCODE_M);
	mEventHandler.SetAction(static_cast<size>(GameAction::DEBUG_ADVANCE_FRAME), SDL_Scancode::SDL_SCANCODE_B);

	//init GUIs
	mTestGui.Initialise(mRenderer);
	mTestGui.ToggleGUI(true);
	mTestGui.ToggleVisibility(true);
	mGuiUpdateList.push_back(&mTestGui);

}

void Game::PreUpdate()
{
	if (mEventHandler.GetActionOnce(static_cast<size>(GameAction::DEBUG_ENABLE_FRAME_ADVANCE)))
	{
		mFrameAdvanceMode = !mFrameAdvanceMode;
		float& accumulator = mGlobalTimer.GetAccumulator();
		accumulator = 0.0f;
	}

	mAdvanceFrameOnce = (mEventHandler.GetActionOnce(static_cast<size>(GameAction::DEBUG_ADVANCE_FRAME)) && mFrameAdvanceMode) ? true : false;

}

void Game::Update()
{
	mTestGui.SetTestNum(mGlobalTimer.GetAccumulator());

	//update GUIs
	for (BaseGui* currPtr : mGuiUpdateList)
	{
		if (currPtr != nullptr && currPtr->IsEnabled())
		{
			currPtr->Update();
		}
	}
}

void Game::PostUpdate()
{

}

void Game::Render()
{
	mTestGui.SetTestNum(mGlobalTimer.GetAccumulator());

	//render GUIs
	for (BaseGui* currPtr : mGuiUpdateList)
	{
		if (currPtr != nullptr && currPtr->IsEnabled() && currPtr->IsVisible())
		{
			currPtr->Draw(mRenderer);
		}
	}

	mRenderer.PresentRenderer();
	mRenderer.ClearRenderer();
}

void Game::PreExit()
{

}