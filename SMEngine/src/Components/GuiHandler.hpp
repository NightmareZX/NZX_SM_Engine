#pragma once
#include "BaseGui.hpp"
#include "Array.hpp"

using GuiPtr = std::shared_ptr<BaseGui>;

class GuiHandler
{
public:
	GuiHandler(size numberOfGuis);
	void Update();
	void Draw(Renderer& renderer);
	void ToggleVisibility(size index, bool toggle);
	void ToggleEnable(size index, bool toggle);

	inline void RegisterGUI(size index, GuiPtr gui) { mGuiArray[index] = gui; }
	inline GuiPtr& AccessGUI(size index) { return mGuiArray[index]; }
private:
	//LinkedList<GuiPtr> mActiveGuiList;
	Array<GuiPtr> mGuiArray;
};