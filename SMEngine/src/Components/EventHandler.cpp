#pragma once
#include "EventHandler.hpp"

EventHandler::EventHandler(size numberOfActions)
	:mKeyBindings(numberOfActions)
{
	mQuitStatus = false;
	mKeyStates = SDL_GetKeyboardState(nullptr);
	mLastKeyStates = new uint8[512];
	for (size i = 0; i < 512; i++)
		mLastKeyStates[i] = 0;
}

void EventHandler::ListenForEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_EventType::SDL_QUIT: mQuitStatus = true; break;
	case SDL_EventType::SDL_KEYDOWN: KeyPressed(); break;
	case SDL_EventType::SDL_KEYUP: KeyReleased(); break;
	case SDL_EventType::SDL_WINDOWEVENT: 
		//WindowEvent(event); 
		break;
	default:
		break;
	}
}

//Returns true as long as the button is held
bool EventHandler::GetAction(size actionIndex)
{
	if (actionIndex >= mKeyBindings.GetLength()) { return false; }

	SDL_Scancode keyToCheck = mKeyBindings[actionIndex];
	if (mKeyStates[keyToCheck] == 1)
		return true;
	return false;
}
//It returns true on the first frame the button is pressed, if the button is held then it returns false
bool EventHandler::GetActionOnce(size actionIndex)
{
	if (actionIndex >= mKeyBindings.GetLength()) { return false; }

	SDL_Scancode keyToCheck = mKeyBindings[actionIndex];
	if (mKeyStates[keyToCheck] == 1 && mLastKeyStates[keyToCheck] == 0)
	{
		mLastKeyStates[keyToCheck] = 1;
		return true;
	}
	else if (mKeyStates[keyToCheck] == 1 && mLastKeyStates[keyToCheck] == 1)
	{
		return false;
	}
	mLastKeyStates[keyToCheck] = 0;
	return false;
}
//void EventHandler::WindowEvent(SDL_Event event)
//{
//	if (event.window.event == SDL_WINDOWEVENT_RESIZED)
//	{
//		//RenderManager::GetInstance()->SetWindowDimensions(event.window.data1, event.window.data2);
//	}
//}