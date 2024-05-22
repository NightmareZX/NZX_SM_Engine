#pragma once
#include "Engine.hpp"
#include "Actions.hpp"
//#include "GameGUIs.hpp"
#include "TestGUI.hpp"

class Game : public Engine
{
public:
	Game(int argc, char* argv[]);

	void Initialise() override;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;
	void Render() override;
	void PreExit() override;

private:
	//GUIs
	TestGUI mTestGui;

	std::vector<BaseGui*> mGuiUpdateList;
	//Objects


};

