#pragma once
#include <iostream>
#include <utility>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "IntTypes.h"
#include "Enums.hpp"
#include "Structs.hpp"
#include "Constants.hpp"

class Editor
{
	using string = std::string;
public:
	Editor(int argc, char* arhv[]);
	int MainLoop();
	void Init();

	//===================================
	//	Windows
	//===================================
	void LevelEditor(bool enable);
	void WorldEditor(bool enable);

	//===================================
	//	Widgets
	//===================================
	void TileGrid(bool enable, const string& tilesetName);

	//===================================
	//	Utility
	//===================================
	void ImGuiRenderTile(const string& tilesetName, uint32 tile);

	void DrawTileLayer(const TileLayer& tileLayer);
	void ResizeRoomLayers(RoomData& room);

	ImVec2 UVfromPixel(ImVec2 pixel, ImVec2 size);
	void DrawLine(ImVec2 firstPoint, ImVec2 secondPoint, SDL_Color color);

	inline ImTextureID SDL_to_ImGuiTexture(SDL_Texture* texture) { return (ImTextureID)(intptr_t)texture; }
	inline void FlipUVsHorizontally(ImVec2& uv1, ImVec2& uv2) { std::swap(uv1.x, uv2.x); }
	inline void FlipUVsVertically(ImVec2& uv1, ImVec2& uv2) { std::swap(uv1.y, uv2.y); }

	bool RegisterTileSet(const string& name, const string& path);
	void UnRegisterTileSet(const string& name);
	TileSet GetTileSet(const string& name);

	bool RegisterTexture(const string& name,const string& path, bool surfaceOnly = false);
	void UnRegisterTexture(const string& name);
	TextureInfo GetTexture(const string& name);

private:
	//===================================
	//	Core
	//===================================

	int mErrorCode;
	bool mRunning;
	SDL_Color mClearColor;

	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;

	EditorState mCurrentState;
	//===================================
	//	Texture Management
	//===================================
	std::unordered_map<string, TextureInfo> mTextureMap;
	std::unordered_map<string, TileSet> mTileSetMap;

	//===================================
	//	Mouse Events
	//===================================

	bool mMiddleMouseDragging;
	bool mMiddleMouseDragDone;
	ImVec2 mMiddleMouseDragDelta;
	ImVec2 mMiddleMousePressedPos;
	ImVec2 mMouseLastPos;

	//===================================
	//		Tile Editor
	//===================================
	RoomData mLoadedRoom;
	uint32 mSelectedTile;

	//Int32 mRoomColumns;
	//Int32 mRoomRows;

	ImVec2 mTileMapPos;
	float mTileMapZoom;
	float mGuiTileScale;

	bool mFlipTileX;
	bool mFlipTileY;
	//===================================
	//		World Data
	//===================================

	//===================================
	//		Room Data
	//===================================

	//===================================
	//		Config Data
	//===================================

};

