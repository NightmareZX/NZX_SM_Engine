#pragma once
#include "IntTypes.h"


enum FlipFlags : uint32
{
	FLIP_HORIZONTALLY = 0b10000000000000000000000000000000,
	FLIP_VERTICALLY = 0b01000000000000000000000000000000
};

enum class EditorState : uint8
{
	None = 0,
	LevelEditor,
	AnimationEditor,
};