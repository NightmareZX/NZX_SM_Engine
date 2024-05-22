#include "TestGUI.hpp"

void TestGUI::Update()
{
	mTestLabel->SetText("Accumulator: " + std::to_string(mTestNum));
	UpdateControlList();
}

void TestGUI::Draw(Renderer& renderer)
{
	DrawControlList(renderer);
}

void TestGUI::Initialise(Renderer& renderer)
{
	mTestLabel = std::make_shared<GuiLabel>();
	mTestLabel->SetPosition(0, 0, 0, 0);
	renderer.RegisterFont("subversion", "C:\\Users\\Owner\\source\\repos\\SM_Engine\\Assets\\", "subversion_font.xml");
	mTestLabel->SetFont("subversion");
	mTestLabel->SetText("Hello from the gui!");
	mTestLabel->ToggleControl(true);
	mTestLabel->ToggleVisibility(true);

	mControlList.push_back(mTestLabel);

	mDrawBackground = true;
	SetBackgroundColour(10, 10, 10, 255);
}
