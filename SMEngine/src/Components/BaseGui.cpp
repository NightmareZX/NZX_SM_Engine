#include "BaseGui.hpp"

BaseGui::BaseGui(): mIsEnabled(false), mIsVisible(false)
{
	mGlobalPosition.x = 0;
	mGlobalPosition.y = 0;
	mGlobalPosition.w = 0;
	mGlobalPosition.h = 0;

	mBackgroundColour.r = 0;
	mBackgroundColour.g = 0;
	mBackgroundColour.b = 0;
	mBackgroundColour.a = 0;
}

void BaseGui::UpdateControlList()
{
	for (ControlPtr control : mControlList)
	{
		if (control != nullptr && control->IsEnabled())
		{
			control->Update();
		}
	}
}

void BaseGui::DrawControlList(Renderer& renderer)
{
	if (mDrawBackground)
	{
		renderer.DrawSolidRectangle(mBackgroundColour, mGlobalPosition, true);
	}
	for (ControlPtr control : mControlList)
	{
		if (control != nullptr && control->IsEnabled() && control->IsVisible())
		{
			control->Draw(renderer, mGlobalPosition.x, mGlobalPosition.y);
		}
	}
}