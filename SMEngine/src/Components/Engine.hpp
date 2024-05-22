#pragma once
#include "Renderer.hpp"
#include "EventHandler.hpp"
#include "GlobalTimer.hpp"
#include "GuiHandler.hpp"


class Engine
{
public:
	Engine(int argc, char* argv[], size actionCount);

	virtual void Initialise() = 0;
	virtual void PreUpdate() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Render() = 0;
	virtual void PreExit() = 0;

	int MainLoop();
protected:
	bool mRunning;
	bool mFrameAdvanceMode;
	bool mAdvanceFrameOnce;

	GlobalTimer mGlobalTimer;
	Renderer mRenderer;
	EventHandler mEventHandler;
};

