#include "Editor.hpp"

Editor::Editor(int argc, char* arhv[])
{
	mErrorCode = 0;
	mRunning = true;
	SDL_Init(SDL_INIT_VIDEO);

	//Debug inits
	mTileMapPos.x = 1280 / 2;
	mTileMapPos.y = 720 / 2;
	mTileMapZoom = 2.0f;
	mClearColor = SDL_Color(115, 140, 153, 255);
	mFlipTileX = false;
	mFlipTileY = false;
	mSelectedTile = 0;
	mGuiTileScale = 1.0f;
	mLoadedRoom = RoomData();

	mWindow = SDL_CreateWindow("Editor",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
	if (mWindow == nullptr)
	{
		mErrorCode = 1;
		mRunning = false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		mErrorCode = 1;
		mRunning = false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
	ImGui_ImplSDLRenderer_Init(mRenderer);

	mMouseLastPos = ImGui::GetMousePos();
}
void Editor::Init()
{
	bool check = RegisterTileSet("collision", "C:\\Users\\Owner\\source\\repos\\SM_Engine\\Assets\\Tilesets\\collission_tileset.png");
	//bool check = RegisterTexture("collision", "C:\\Users\\Owner\\source\\repos\\SM_Engine\\Assets\\Tilesets\\collission_tileset.png");
	//IM_ASSERT(!check);

	mCurrentState = EditorState::LevelEditor;
	mLoadedRoom.CollisionLayer.TileMatrix.New(16,16);
}


int Editor::MainLoop()
{
	Init();
	while (mRunning)
	{
		SDL_RenderClear(mRenderer);
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				mRunning = false;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(mWindow))
				mRunning = false;
		}
		//Check
		if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) && !mMiddleMouseDragging)
		{
			mMiddleMousePressedPos = ImGui::GetMousePos();
			mMiddleMouseDragDelta.x = 0.0f;
			mMiddleMouseDragDelta.y = 0.0f;
			mMiddleMouseDragging = true;
		}
		else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) && mMiddleMouseDragging)
		{
			ImVec2 currentPos = ImGui::GetMousePos();

			mMiddleMouseDragDelta.x = mMiddleMousePressedPos.x - currentPos.x;
			mMiddleMouseDragDelta.y = mMiddleMousePressedPos.y - currentPos.y;

			//std::cout << "X: " << mMiddleMouseDragDelta.x << "Y: " << mMiddleMouseDragDelta.y << '\n';
		}
		else if (!ImGui::IsMouseDown(ImGuiMouseButton_Middle) && mMiddleMouseDragging)
		{
			mMiddleMouseDragging = false;
			mMiddleMouseDragDone = true;
			//std::cout << "Done\n";
		}

		//Init new frame
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		//

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		switch (mCurrentState)
		{
		case EditorState::LevelEditor:
			LevelEditor(true);
			break;
			
		case EditorState::AnimationEditor:	
			break;
			
		default:
			break;
		}

		

		//ImGui::ShowDemoWindow();

		mMouseLastPos = ImGui::GetMousePos();
		mMiddleMouseDragDone = false;
		//Render Frame
		ImGui::Render();
		SDL_SetRenderDrawColor(mRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(mRenderer);
		//
	}

	//cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	return mErrorCode;
}
void Editor::LevelEditor(bool enable)
{
	if (!enable) { return; }

	ImGuiIO& io = ImGui::GetIO();

	if (io.MouseWheel != 0.0f)
	{
		mTileMapZoom += io.MouseWheel * 0.1;
		mTileMapPos.x += (TILE_SIZE * mTileMapZoom) - TILE_SIZE;
		mTileMapPos.y += (TILE_SIZE * mTileMapZoom) - TILE_SIZE;
	}

	if (mMiddleMouseDragging)
	{
		mTileMapPos.x += -mMiddleMouseDragDelta.x;
		mTileMapPos.y += -mMiddleMouseDragDelta.y;
	}
	if (mMiddleMouseDragDone)
	{
		mTileMapPos.x += -mMiddleMouseDragDelta.x;
		mTileMapPos.y += -mMiddleMouseDragDelta.y;
	}

	DrawTileLayer(mLoadedRoom.CollisionLayer);

	//Draw gridlines
	for (size y = 0; y <= mLoadedRoom.Height; y++)
	{
		ImVec2 firstPoint = ImVec2(mTileMapPos.x, (y * TILE_SIZE) * mTileMapZoom + mTileMapPos.y);
		ImVec2 secondPoint = ImVec2((mLoadedRoom.Height * TILE_SIZE) * mTileMapZoom + mTileMapPos.x,
			(y * TILE_SIZE) * mTileMapZoom + mTileMapPos.y);
		DrawLine(firstPoint, secondPoint, SDL_Color(180, 180, 180, 255));
	}
	for (size x = 0; x <= mLoadedRoom.Width; x++)
	{
		ImVec2 firstPoint = ImVec2((x * TILE_SIZE) * mTileMapZoom + mTileMapPos.x, mTileMapPos.y);
		ImVec2 secondPoint = ImVec2((x * TILE_SIZE) * mTileMapZoom + mTileMapPos.x,
			(mLoadedRoom.Width * TILE_SIZE) * mTileMapZoom + mTileMapPos.y);
		DrawLine(firstPoint, secondPoint, SDL_Color(180, 180, 180, 255));
	}

	//
	if (mSelectedTile != 0)
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 mapSize = ImVec2(
			mTileMapPos.x + (mLoadedRoom.Width * TILE_SIZE) * mTileMapZoom,
			mTileMapPos.y + (mLoadedRoom.Height * TILE_SIZE) * mTileMapZoom);

		if (mousePos.x >= mTileMapPos.x && mousePos.y >= mTileMapPos.y && mousePos.x <= mapSize.x && mousePos.y <= mapSize.y)
		{
			ImVec2 relativePos = ImVec2(mousePos.x - mTileMapPos.x, mousePos.y - mTileMapPos.y);
			int32 gridPosX = floorf(relativePos.x / (TILE_SIZE * mTileMapZoom));
			int32 gridPosY = floorf(relativePos.y / (TILE_SIZE * mTileMapZoom));
			TileSet tileSet = GetTileSet("collision");

			uint32 tile = mSelectedTile;
			int32 flipFlags = SDL_FLIP_NONE;

			if (tile & FLIP_HORIZONTALLY)
			{
				flipFlags |= SDL_FLIP_HORIZONTAL;
				tile ^= FLIP_HORIZONTALLY;
			}
			if (tile & FLIP_VERTICALLY)
			{
				flipFlags |= SDL_FLIP_VERTICAL;
				tile ^= FLIP_VERTICALLY;
			}
			tile--;

			int32 tileTextureX = (tile % tileSet.Columns) * TILE_SIZE;
			int32 tileTextureY = (tile / tileSet.Columns) * TILE_SIZE;
			SDL_Rect src = SDL_Rect(tileTextureX, tileTextureY, TILE_SIZE, TILE_SIZE);
			//SDL_Rect dst = SDL_Rect(
			//	mTileMapPos.x + (x * TILE_SIZE) * mTileMapZoom,
			//	mTileMapPos.y + (y * TILE_SIZE) * mTileMapZoom,
			//	TILE_SIZE * mTileMapZoom,
			//	TILE_SIZE * mTileMapZoom);

			//SDL_RenderCopyEx(mRenderer, tileSetTexture.Texture, &src, &dst, 0, nullptr, static_cast<SDL_RendererFlip>(flipFlags));

		}
	}

	//Render the GUI
	ImGui::Begin("Level Editor");
	{
		if (ImGui::BeginTabBar("Tile Editor Tabs"))
		{
			if (ImGui::BeginTabItem("Properties"))
			{
				ImGui::InputInt("Width", &mLoadedRoom.SectorColumns, 1, 10);
				if (mLoadedRoom.SectorColumns < 1) mLoadedRoom.SectorColumns = 1;
				mLoadedRoom.Width = mLoadedRoom.SectorColumns * SECTOR_SIZE;

				ImGui::InputInt("Height", &mLoadedRoom.SectorRows, 1, 10);
				if (mLoadedRoom.SectorRows < 1) mLoadedRoom.SectorRows = 1;
				mLoadedRoom.Height = mLoadedRoom.SectorRows * SECTOR_SIZE;

				ResizeRoomLayers(mLoadedRoom);

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Tiles"))
			{
				ImGui::SliderFloat("Tile Scale", &mGuiTileScale, 1.0f, 3.0f);

				ImGui::Text("Selected Tile:");
				ImGuiRenderTile("collision", mSelectedTile);

				ImGui::Checkbox("Flip X", &mFlipTileX);
				ImGui::SameLine();
				ImGui::Checkbox("Flip Y", &mFlipTileY);

				ImGui::Text("Tileset:");
				TileGrid(true, "collision");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Objects"))
			{
				ImGui::Text("This is some useful text.");
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	
	if (mMiddleMouseDragging)
	{
		mTileMapPos.x -= -mMiddleMouseDragDelta.x;
		mTileMapPos.y -= -mMiddleMouseDragDelta.y;
	}
}
void Editor::WorldEditor(bool enable)
{
	ImGui::Begin("World Editor");
	{
		ImGui::End();
	}
}

//credit to Roger Schoellgen https://www.youtube.com/watch?v=_ityQfP5Cd4
void Editor::TileGrid(bool enable, const string& tilesetName)
{
	if (!enable) { return; }
	ImGui::BeginChild("TileMap");
	{
		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 scrollPos = ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY());
		const float gridScale = mGuiTileScale;

		TileSet tileset = GetTileSet(tilesetName);
		if (tileset.ReferenceCount == 0) { return; }//invalid tileset

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		drawList->PushClipRect(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y));

		uint32 tileCount = tileset.TileCount;
		const int32 columnCount = 8;
		int32 rowCount = ceilf((float)tileCount / columnCount);

		ImVec2 tileGridPos = ImVec2(windowPos.x - scrollPos.x, windowPos.y - scrollPos.y);
		ImVec2 tileGridSize = ImVec2((columnCount * TILE_SIZE) * gridScale, (rowCount * TILE_SIZE) * gridScale);

		uint32 intColour = IM_COL32(100, 148, 237, 255);
		drawList->AddRectFilled(tileGridPos, ImVec2(tileGridPos.x + tileGridSize.x, tileGridPos.y + tileGridSize.y), intColour);

		//draw tiles
		for (size i = 0; i < tileCount; i++)
		{
			int32 x = i % columnCount;
			int32 y = i / columnCount;
			int32 xTile = x * TILE_SIZE;
			int32 yTile = y * TILE_SIZE;

			int32 tileTextureX = (i % tileset.Columns) * TILE_SIZE;
			int32 tileTextureY = (i / tileset.Columns) * TILE_SIZE;

			ImVec2 pos = ImVec2(tileGridPos.x + xTile * gridScale - scrollPos.x,
				tileGridPos.y + yTile * gridScale - scrollPos.y);
			ImVec2 size = ImVec2(pos.x + TILE_SIZE * gridScale, pos.y + TILE_SIZE * gridScale);

			ImVec2 uv1 = UVfromPixel(ImVec2(tileTextureX, tileTextureY), tileset.Size);
			ImVec2 uv2 = UVfromPixel(ImVec2(tileTextureX + TILE_SIZE, tileTextureY + TILE_SIZE), tileset.Size);

			if (mFlipTileX) { FlipUVsHorizontally(uv1, uv2); }
			if (mFlipTileY) { FlipUVsVertically(uv1, uv2); }

			ImTextureID tilesetTexture = SDL_to_ImGuiTexture(GetTexture(tilesetName).Texture);

			drawList->AddImage(tilesetTexture, pos, size, uv1, uv2);
		}

		//grid lines
		uint32 intGridColour = IM_COL32(173, 173, 173, 255);
		const float gridThickness = 1.0f;
		for (size x = 0; x <= columnCount; x++)
		{
			ImVec2 p1 = ImVec2(tileGridPos.x + (x * TILE_SIZE) * gridScale, tileGridPos.y);
			ImVec2 p2 = ImVec2(tileGridPos.x + (x * TILE_SIZE) * gridScale, tileGridPos.y + tileGridSize.y);
			drawList->AddLine(p1, p2, intGridColour, gridThickness);
		}
		for (size y = 0; y <= rowCount; y++)
		{
			ImVec2 p1 = ImVec2(tileGridPos.x, tileGridPos.y + (y * TILE_SIZE) * gridScale);
			ImVec2 p2 = ImVec2(tileGridPos.x + tileGridSize.x, tileGridPos.y + (y * TILE_SIZE) * gridScale);
			drawList->AddLine(p1, p2, intGridColour, gridThickness);
		}

		//dummy to define widget size for stuff like scrolling
		ImGui::Dummy(ImVec2((columnCount * TILE_SIZE) * gridScale, (rowCount * TILE_SIZE) * gridScale));

		int32 tileIndex = -1;
		ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 relativeMousePos = ImVec2(mousePos.x - windowPos.x + scrollPos.x, mousePos.y - windowPos.y + scrollPos.y);
		int32 xIndex = relativeMousePos.x / (TILE_SIZE * gridScale);
		int32 yIndex = relativeMousePos.y / (TILE_SIZE * gridScale);
		if (xIndex >= 0 && yIndex >= 0 && xIndex < columnCount && yIndex < rowCount)
		{
			tileIndex = xIndex + (yIndex * columnCount);
		}
		if (tileIndex >= 0 
			&& tileIndex < tileCount 
			&& ImGui::IsMouseHoveringRect(tileGridPos, ImVec2(tileGridPos.x + tileGridSize.x, tileGridSize.y + tileGridPos.y)))
		{
			ImVec2 topCorner = ImVec2(xIndex * (TILE_SIZE * gridScale) + windowPos.x - scrollPos.x,
				yIndex * (TILE_SIZE * gridScale) + windowPos.y - scrollPos.y);
			ImVec2 bottomCorner = ImVec2(topCorner.x + (TILE_SIZE * gridScale), topCorner.y + (TILE_SIZE * gridScale));

			drawList->AddRect(topCorner, bottomCorner, IM_COL32(255,255,255,255), 0.0f, 0, 4.0f);

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				mSelectedTile = tileIndex + 1;
				//x flip flag
				if(mFlipTileX){ mSelectedTile |= FLIP_HORIZONTALLY; }
				//y flip flag
				if(mFlipTileY){ mSelectedTile |= FLIP_VERTICALLY; }
			}
		}

		drawList->PopClipRect();
		ImGui::EndChild();
	}
}

void Editor::DrawTileLayer(const TileLayer& tileLayer)
{
	TileSet tileSet = GetTileSet(tileLayer.TileSetName);
	if (tileSet.ReferenceCount == 0) return;
	TextureInfo tileSetTexture = GetTexture(tileLayer.TileSetName);
	if (tileSetTexture.ReferenceCount == 0) return;

	for (size y = 0; y < mLoadedRoom.Height; y++)
	{
		for (size x = 0; x < mLoadedRoom.Width; x++)
		{
			uint32 tile = tileLayer.TileMatrix(y, x);
			if (tile == 0) continue;
			int32 flipFlags = SDL_FLIP_NONE;

			if (tile & FLIP_HORIZONTALLY)
			{
				flipFlags |= SDL_FLIP_HORIZONTAL;
				tile ^= FLIP_HORIZONTALLY;
			}
			if (tile & FLIP_VERTICALLY)
			{
				flipFlags |= SDL_FLIP_VERTICAL;
				tile ^= FLIP_VERTICALLY;
			}
			tile--;

			int32 tileTextureX = (tile % tileSet.Columns) * TILE_SIZE;
			int32 tileTextureY = (tile / tileSet.Columns) * TILE_SIZE;
			SDL_Rect src = SDL_Rect(tileTextureX, tileTextureY, TILE_SIZE, TILE_SIZE);
			SDL_Rect dst = SDL_Rect(
				mTileMapPos.x + (x * TILE_SIZE) * mTileMapZoom,
				mTileMapPos.y + (y * TILE_SIZE) * mTileMapZoom,
				TILE_SIZE * mTileMapZoom,
				TILE_SIZE * mTileMapZoom);

			SDL_RenderCopyEx(mRenderer, tileSetTexture.Texture, &src, &dst, 0, nullptr, static_cast<SDL_RendererFlip>(flipFlags));
		}
	}
}
void Editor::ResizeRoomLayers(RoomData& roomData)
{
	Matrix<uint32>& tileMap = roomData.CollisionLayer.TileMatrix;
	//if the collision tile map is not the same size then the rest aren't either
	if (tileMap.GetColumnLength() != roomData.Width || tileMap.GetRowLength() != roomData.Height)
	{
		tileMap.Resize(roomData.Height, roomData.Width);
		roomData.BackgroundLayer.TileMatrix.Resize(roomData.Height, roomData.Width);
		roomData.MiddlegroundLayer.TileMatrix.Resize(roomData.Height, roomData.Width);
		roomData.ForegroundLayer.TileMatrix.Resize(roomData.Height, roomData.Width);
	}
}
void Editor::ImGuiRenderTile(const string& tilesetName, uint32 tile)
{
	const float scale = mGuiTileScale;
	if (tile == 0)
	{
		ImVec2 dummySize = ImVec2(TILE_SIZE * scale, TILE_SIZE * scale);
		ImGui::Dummy(dummySize);
		return;
	}
	bool xFlip = false;
	bool yFlip = false;
	if (tile & FLIP_HORIZONTALLY)
	{
		xFlip = true;
		tile ^= FLIP_HORIZONTALLY;
	}
	if (tile & FLIP_VERTICALLY)
	{
		yFlip = true;
		tile ^= FLIP_VERTICALLY;
	}
	tile--;

	TileSet tileset = GetTileSet(tilesetName);
	ImTextureID tilesetTexture = SDL_to_ImGuiTexture(GetTexture(tilesetName).Texture);

	int32 tileTextureX = (tile % tileset.Columns) * TILE_SIZE;
	int32 tileTextureY = (tile / tileset.Columns) * TILE_SIZE;

	ImVec2 size = ImVec2(TILE_SIZE * scale, TILE_SIZE * scale);

	ImVec2 uv1 = UVfromPixel(ImVec2(tileTextureX, tileTextureY), tileset.Size);
	ImVec2 uv2 = UVfromPixel(ImVec2(tileTextureX + TILE_SIZE, tileTextureY + TILE_SIZE), tileset.Size);

	if (xFlip) { FlipUVsHorizontally(uv1, uv2); }
	if (yFlip) { FlipUVsVertically(uv1, uv2); }

	ImGui::Image(tilesetTexture, size, uv1, uv2);
}
ImVec2 Editor::UVfromPixel(ImVec2 pixel, ImVec2 size)
{
	float x = (pixel.x == 0.0f) ? 0.0f : pixel.x / size.x;
	float y = (pixel.y == 0.0f) ? 0.0f : pixel.y / size.y;
	return ImVec2(x, y);
}

void Editor::DrawLine(ImVec2 firstPoint, ImVec2 secondPoint, SDL_Color color)
{
	SDL_Color temp;
	SDL_GetRenderDrawColor(mRenderer, &temp.r, &temp.g, &temp.b, &temp.a);
	SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);

	SDL_RenderDrawLineF(mRenderer, firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);

	SDL_SetRenderDrawColor(mRenderer, temp.r, temp.g, temp.b, temp.a);
}

bool Editor::RegisterTileSet(const string& name, const string& path)
{
	auto tileset = mTileSetMap.find(name);
	if (tileset != mTileSetMap.end())
	{
		tileset->second.ReferenceCount++;
	}
	else
	{
		bool check = RegisterTexture(name, path);
		if (!check) { return check; }
		TileSet& tileSet = mTileSetMap[name];
		TextureInfo textureInfo = GetTexture(name);
		tileSet.Size = ImVec2(textureInfo.Surface->w, textureInfo.Surface->h);
		tileSet.Columns = tileSet.Size.x / TILE_SIZE;
		tileSet.Rows = tileSet.Size.y / TILE_SIZE;
		tileSet.TileCount = tileSet.Columns * tileSet.Rows;
		for (size y = 0; y < tileSet.Rows; y++)
		{
			for (size x = 0; x < tileSet.Columns; x++)
			{
				SDL_Rect tile = SDL_Rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				tileSet.Tiles.push_back(tile);
				//SDL_Surface* temp = SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
				//SDL_UpperBlit(textureInfo.Surface, &src, temp, nullptr);
				//SDL_Texture* tile = SDL_CreateTextureFromSurface(mRenderer, temp);
				//tileSet.Tiles.push_back(tile);
				//SDL_FreeSurface(temp);
			}
		}

		tileSet.ReferenceCount = 1;
	}

}

void Editor::UnRegisterTileSet(const string& name)
{
	auto tileset = mTileSetMap.find(name);
	if (tileset != mTileSetMap.end())
	{
		if (tileset->second.ReferenceCount == 0)
		{
			//tileset->second.Dispose();
			UnRegisterTexture(name);
			mTileSetMap.erase(tileset);
		}
		else
		{
			tileset->second.ReferenceCount--;
		}
	}
	else
	{
		return;
	}
}
TileSet Editor::GetTileSet(const string& name)
{
	auto tileset = mTileSetMap.find(name);
	if (tileset != mTileSetMap.end())
	{
		return tileset->second;
	}
	return TileSet();
}

bool Editor::RegisterTexture(const string& name, const string& path, bool surfaceOnly)
{
	auto texture = mTextureMap.find(name);
	//texture exists
	if (texture != mTextureMap.end())
	{
		texture->second.ReferenceCount++;
	}
	//texture doesnt exist
	else
	{
		//automatically creates new texture info
		TextureInfo& textureInfo = mTextureMap[name];
		textureInfo.Surface = IMG_Load(path.c_str());
		if (textureInfo.Surface == nullptr) { return false; }
		if (!surfaceOnly)
		{
			textureInfo.Texture = SDL_CreateTextureFromSurface(mRenderer, textureInfo.Surface);
			if (textureInfo.Texture == nullptr) { return false; }
		}
		textureInfo.ReferenceCount = 1;
	}
	return true;
}
void Editor::UnRegisterTexture(const string& name)
{
	auto texture = mTextureMap.find(name);
	if (texture != mTextureMap.end())
	{
		if (texture->second.ReferenceCount == 0)
		{
			SDL_DestroyTexture(texture->second.Texture);
			SDL_FreeSurface(texture->second.Surface);
			mTextureMap.erase(texture);
		}
		else
		{
			texture->second.ReferenceCount--;
		}
	}
	else
	{
		return;
	}
}
TextureInfo Editor::GetTexture(const string& name)
{
	auto texture = mTextureMap.find(name);
	if (texture != mTextureMap.end())
	{
		return texture->second;
	}
	return TextureInfo(nullptr, nullptr, 0);
}