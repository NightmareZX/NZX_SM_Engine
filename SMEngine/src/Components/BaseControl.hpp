#pragma once
#include <string>
#include <memory>
#include "IntTypes.h"
#include "Rectangle.hpp"
#include "Renderer.hpp"

class BaseControl
{
public:
	BaseControl();

	virtual void Update() = 0;
	virtual void Draw(Renderer& renderer, int32 x, int32 y) = 0;

	inline void ToggleVisibility(bool toggle) { mIsVisible = toggle; }
	inline void ToggleControl(bool toggle) { mIsEnabled = toggle; }
	inline const bool IsVisible() const { return mIsVisible; }
	inline const bool IsEnabled() const { return mIsEnabled; }
	inline void SetPosition(int32 x, int32 y, int32 w, int32 h)
	{
		mRelativePosition.x = x;
		mRelativePosition.y = y;
		mRelativePosition.w = w;
		mRelativePosition.h = h;
	}
protected:
	bool mIsVisible;
	bool mIsEnabled;

	Rectangle mRelativePosition;
	//String mName;
};