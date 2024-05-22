#pragma once
#include <SDL.h>
//#include "Hashmap.hpp"
#include "Array.hpp"
#include "IntTypes.h"

class EventHandler
{
public:
	EventHandler(size numberOfActions);
	
	inline bool GetQuitStatus() const { return mQuitStatus; }
	inline void KeyPressed() { mKeyStates = SDL_GetKeyboardState(nullptr); }
	inline void KeyReleased() { mKeyStates = SDL_GetKeyboardState(nullptr); }
	inline void SetAction(size actionIndex, SDL_Scancode key) { mKeyBindings[actionIndex] = key; }

	bool GetAction(size actionIndex);
	bool GetActionOnce(size actionIndex);
	void ListenForEvents();
	//void WindowEvent(SDL_Event event);
	
private:
	const uint8* mKeyStates;
	uint8* mLastKeyStates;
	//Hashmap<ActionEnum, SDL_Scancode> mKeyBindings;
	Array<SDL_Scancode> mKeyBindings;
	bool mQuitStatus;
};

