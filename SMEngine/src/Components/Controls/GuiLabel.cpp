#include "GuiLabel.hpp"


GuiLabel::GuiLabel()
{

}

void GuiLabel::Draw(Renderer& renderer, int32 x, int32 y)
{
	renderer.RenderText(mFont, x + mRelativePosition.x, y + mRelativePosition.y, mText);
}