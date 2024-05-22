#pragma once
#include <unordered_map>
#include <string>
#include "Texture.hpp"
#include "Vector2.hpp"


struct RasterFont
{
	std::unordered_map<char, Vector2<int32>> CharacterMap;
	std::string TextureName;
	uint32 Width;
	uint32 Height;
	uint32 HorizontalSpacing;
	uint32 VerticalSpacing;
	uint32 BorderSize;
	bool HasUpperCase;
};

