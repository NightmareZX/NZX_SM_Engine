#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <SDL.h>
#include "imgui.h"
#include "IntTypes.h"
#include "Constants.hpp"
#include "Matrix.hpp"


struct WorldAreas
{
	std::string AreaName;
	std::filesystem::path AreaPath;
};
struct WorldData
{
	std::filesystem::path WorldPath;
	std::vector<WorldAreas> AreaList;
	//events
	//global values (ints, std::strings)
};

struct TileLayer
{
	std::string TileSetName;
	Matrix<uint32> TileMatrix;
};
struct GameObject
{
	std::string ObjectName;
	std::string Texture;
};
struct RoomData
{
	std::string RoomName;
	std::filesystem::path RoomPath;
	//Size in sectors
	int32 SectorColumns = 1;
	int32 SectorRows = 1;
	//Size in tiles
	uint32 Width = SECTOR_SIZE;
	uint32 Height = SECTOR_SIZE;

	//Tile layers
	TileLayer BackgroundLayer;
	TileLayer MiddlegroundLayer;
	TileLayer ForegroundLayer;
	TileLayer CollisionLayer = TileLayer("collision");

	//Object layer
	std::vector<GameObject> LevelObjects;
};

struct TextureInfo
{
	SDL_Texture* Texture = nullptr;
	SDL_Surface* Surface = nullptr;
	uint32 ReferenceCount = 0;
};

struct TileSet
{
	std::vector<SDL_Rect> Tiles;
	uint32 TileCount = 0;
	uint32 ReferenceCount = 0;
	ImVec2 Size = ImVec2(0, 0);
	uint32 Rows = 0;
	uint32 Columns = 0;
};