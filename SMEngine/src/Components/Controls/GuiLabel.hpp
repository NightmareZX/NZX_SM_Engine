#pragma once
#include "BaseControl.hpp"

class GuiLabel : public BaseControl
{
	using string = std::string;
public:
	GuiLabel();

	void Update() override {}
	void Draw(Renderer& renderer, int32 x, int32 y) override;

	inline void SetText(const string& text) { mText = text; }
	inline string GetText() const { return mText; }
	inline void SetFont(const string& font) { mFont = font; }
	inline string GetFont() const { return mFont; }
private:
	string mText;
	string mFont;
};

using LabelPtr = std::shared_ptr<GuiLabel>;