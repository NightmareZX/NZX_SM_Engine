#include "Texture.hpp"

Texture::Texture(Texture&& other) noexcept
	: mTexture(other.mTexture)
{
	other.mTexture = nullptr;
}

Texture::Texture(Surface& surface, SDL_Renderer* renderer)
{
	mTexture = SDL_CreateTextureFromSurface(renderer, surface.GetRawSurface());
}

Texture::Texture(SDL_Texture* texture)
{
	mTexture = texture;
}

Texture::~Texture()
{
	Dispose();
}

void Texture::NewFromSurface(Surface& surface, SDL_Renderer* renderer)
{
	Dispose();
	mTexture = SDL_CreateTextureFromSurface(renderer, surface.GetRawSurface());
}

void Texture::Dispose()
{
	if (mTexture == nullptr) return;
	SDL_DestroyTexture(mTexture);
}

Texture& Texture::operator=(Texture other)
{
	std::swap(mTexture, other.mTexture);
	return *this;
}