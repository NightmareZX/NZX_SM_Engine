#pragma once
#include "IntTypes.h"

//The size of the tiles in pixels
constexpr uint32 TILE_SIZE = 16;

//the amount of sub pixels within a pixel
constexpr float SUB_PIXEL_SIZE = 1.0f / TILE_SIZE;

//The size of the sectors by tiles
constexpr uint32 SECTOR_SIZE = 16;
