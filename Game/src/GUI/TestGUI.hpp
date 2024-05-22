#pragma once
#include "BaseGui.hpp"
#include "Controls/GuiLabel.hpp"

class TestGUI : public BaseGui
{
public:
	TestGUI():mTestNum(0){}

	void Initialise(Renderer& renderer) override;
	void Update() override;
	void Draw(Renderer& renderer) override;

	inline void SetTestNum(float num) { mTestNum = num; }
private:
	LabelPtr mTestLabel;
	float mTestNum;
};