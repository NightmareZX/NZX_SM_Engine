#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "Texture.hpp"
#include "RasterFont.hpp"
#include "Rectangle.hpp"
#include "Colour.hpp"
#include "XML.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void PresentRenderer();
	void ClearRenderer();

	void RegisterTexture(const std::string& name, const std::string& path);
	void RegisterFont(const std::string& name, const std::string& path, const std::string& filename);
	void RenderText(const std::string& font, const int32 x, const int32 y, const std::string& text);
	void DrawSolidRectangle(const Colour& colour, const Rectangle& rectangle, bool fill);
private:
	struct TextureInfo
	{
		Texture Texture;
		size ReferenceCount;
	};

	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	Colour mRenderColour;
	std::unordered_map<std::string, TextureInfo> mTextureMap;
	std::unordered_map<std::string, RasterFont> mRasterFontMap;
};