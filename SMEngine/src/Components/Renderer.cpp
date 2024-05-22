#include "Renderer.hpp"

using std::string;
using CStr = const char*;

Renderer::Renderer()
{
	mWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, 0);
	//throw error when window is null
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//throw error when renderer is null
}
Renderer::~Renderer()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void Renderer::PresentRenderer()
{
	SDL_RenderPresent(mRenderer);
}

void Renderer::ClearRenderer()
{
	SDL_RenderClear(mRenderer);
}
void Renderer::RegisterTexture(const string& name, const string& path)
{
	Surface temp = IMG_Load(path.c_str());
	Texture texture(temp, mRenderer);

	TextureInfo& textureInfo = mTextureMap[name];
	textureInfo.Texture = texture.Move();
	textureInfo.ReferenceCount = 0;
}
void Renderer::RegisterFont(const string& name, const string& path, const string& filename)
{
	//IMPLEMENT ERROR CHECKING
	RasterFont& fontInfo = mRasterFontMap[name];

	XMLFile fontData;
	fontData.LoadFile(string(path + filename).c_str());

	XMLElement* props = fontData.FirstChildElement("RasterFont")->FirstChildElement("Properties");

	bool boolval = false;
	uint32 value = 0;
	CStr textureName;

	props->FirstChildElement("TextureName")->QueryStringAttribute("value", &textureName);
	RegisterTexture(textureName, path + textureName);
	fontInfo.TextureName = textureName;
	props->FirstChildElement("CharacterWidth")->QueryUnsignedAttribute("value", &value);
	fontInfo.Width = value;
	props->FirstChildElement("CharacterHeight")->QueryUnsignedAttribute("value", &value);
	fontInfo.Height = value;
	props->FirstChildElement("BorderSize")->QueryUnsignedAttribute("value", &value);
	fontInfo.BorderSize = value;
	props->FirstChildElement("HorizontalSpacing")->QueryUnsignedAttribute("value", &value);
	fontInfo.HorizontalSpacing = value;
	props->FirstChildElement("VerticalSpacing")->QueryUnsignedAttribute("value", &value);
	fontInfo.VerticalSpacing = value;
	props->FirstChildElement("HasUppercase")->QueryBoolAttribute("value", &boolval);
	fontInfo.HasUpperCase = boolval;

	for (XMLElement* value = fontData.FirstChildElement("RasterFont")->FirstChildElement("CharacterMap")->FirstChildElement();
		value != nullptr; value = value->NextSiblingElement())
	{
		CStr characterStr;
		auto err = value->QueryStringAttribute("char", &characterStr);
		char character = characterStr[0];
		int32 x = 0;
		int32 y = 0;
		value->QueryIntAttribute("x", &x);
		value->QueryIntAttribute("y", &y);

		fontInfo.CharacterMap[character] = Vector2<int32>(x, y);
	}
}
void Renderer::RenderText(const string& font, const int32 x, const int32 y, const string& text)
{
	RasterFont& fontInfo = mRasterFontMap[font];
	int32 xPos = 0, yPos = 0;

	for (char character : text)
	{
		if (character == ' ')
		{
			xPos += fontInfo.Width + fontInfo.HorizontalSpacing;
			continue;
		}
		else if (character == '\n')
		{
			xPos = 0;
			yPos += fontInfo.Height + fontInfo.VerticalSpacing;
			continue;
		}

		if (!fontInfo.HasUpperCase)
		{
			character = std::tolower(character);
		}

		Vector2<int32> positions = fontInfo.CharacterMap[character];
		Texture& texture = mTextureMap[fontInfo.TextureName].Texture;

		Rectangle source =
		{
			.x = static_cast<int32>(positions.x),
			.y = static_cast<int32>(positions.y),
			.w = static_cast<int32>(fontInfo.Width),
			.h = static_cast<int32>(fontInfo.Height)
		};

		Rectangle destination =
		{
			.x = static_cast<int32>(xPos),
			.y = static_cast<int32>(yPos),
			.w = static_cast<int32>(fontInfo.Width),
			.h = static_cast<int32>(fontInfo.Height)
		};

		SDL_RenderCopy(mRenderer, texture.GetRawSurface(), &source, &destination);

		xPos += fontInfo.Width + fontInfo.HorizontalSpacing;
	}
}

void Renderer::DrawSolidRectangle(const Colour& colour, const Rectangle& rectangle, bool fill)
{
	SDL_SetRenderDrawColor(mRenderer, colour.r, colour.g, colour.b, colour.a);
	if (fill)
	{
		SDL_RenderFillRect(mRenderer, &rectangle);
	}
	else
	{
		SDL_RenderDrawRect(mRenderer, &rectangle);
	}
	SDL_SetRenderDrawColor(mRenderer, mRenderColour.r, mRenderColour.g, mRenderColour.b, mRenderColour.a);
}