#include "GuiHandler.hpp"


GuiHandler::GuiHandler(size numberOfGuis)
	:mGuiArray(numberOfGuis)
{
}
void GuiHandler::Update()
{
	for (size i = 0; i < mGuiArray.GetLength(); i++)
	{
		GuiPtr& currPtr = mGuiArray[i];
		if (currPtr != nullptr && currPtr->IsEnabled())
		{
			currPtr->Update();
		}
	}
}
void GuiHandler::Draw(Renderer& renderer)
{
	for (size i = 0; i < mGuiArray.GetLength(); i++)
	{
		GuiPtr& currPtr = mGuiArray[i];
		if (currPtr != nullptr && currPtr->IsEnabled() && currPtr->IsVisible())
		{
			currPtr->Draw(renderer);
		}
	}
}
//void GuiHandler::RegisterGUI(Size index, BaseGui* gui)
//{
//	mGuiArray[index].reset(gui);
//}
void GuiHandler::ToggleVisibility(size index, bool toggle)
{
	//SDL_assert(index >= mGuiArray.GetLength());
	GuiPtr& currPtr = mGuiArray[index];
	if (currPtr != nullptr) currPtr->ToggleVisibility(toggle);
}
void GuiHandler::ToggleEnable(size index, bool toggle)
{
	//SDL_assert(index >= mGuiArray.GetLength());
	GuiPtr& currPtr = mGuiArray[index];
	if (currPtr != nullptr) currPtr->ToggleGUI(toggle);
}