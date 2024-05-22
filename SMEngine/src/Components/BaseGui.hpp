#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IntTypes.h"
#include "Rectangle.hpp"
#include "BaseControl.hpp"
#include "Renderer.hpp"
#include "Colour.hpp"

using ControlPtr = std::shared_ptr<BaseControl>;

class BaseGui
{
public:
	BaseGui();

	//internal update function used by the GUI manager
	void UpdateControlList();
	//internal draw function used by the GUI manager
	void DrawControlList(Renderer& renderer);



	virtual void Initialise(Renderer& renderer) = 0;
	virtual void Update() = 0;
	virtual void Draw(Renderer& renderer) = 0;

	inline void ToggleVisibility(bool toggle) { mIsVisible = toggle; }
	inline void ToggleGUI(bool toggle) { mIsEnabled = toggle; }
	inline const bool IsVisible() const { return mIsVisible; }
	inline const bool IsEnabled() const { return mIsEnabled; }
	inline void SetPosition(int32 x, int32 y, int32 w, int32 h)
	{
		mGlobalPosition.x = x;
		mGlobalPosition.y = y;
		mGlobalPosition.w = w;
		mGlobalPosition.h = h;
	}
	inline void SetBackgroundColour(uint8 r, uint8 g, uint8 b, uint8 a)
	{
		mBackgroundColour.r = r;
		mBackgroundColour.g = g;
		mBackgroundColour.b = b;
		mBackgroundColour.a = a;
	}

protected:
	bool mIsVisible;
	bool mIsEnabled;
	bool mDrawBackground;

	Rectangle mGlobalPosition;
	Colour mBackgroundColour;
	//String mName;
	std::vector<ControlPtr> mControlList;
};