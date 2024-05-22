#pragma once
#include <SDL.h>
#include <utility>
#include "Surface.hpp"

class Texture
{
public:
	Texture() noexcept : mTexture(nullptr) {}
	Texture(const Texture& other) = delete;//for now no copy constructor
	Texture(Texture&& other) noexcept;
	Texture(Surface& surface, SDL_Renderer* renderer);
	Texture(SDL_Texture* texture);
	~Texture() noexcept;

	inline SDL_Texture* GetRawSurface() { return mTexture; }
	inline bool IsNull() const noexcept { return mTexture == nullptr; };
	inline Texture&& Move() { return std::move(*this); }

	inline void NewFromSurface(Surface& surface, SDL_Renderer* renderer);
	inline void Dispose();

	Texture& operator=(Texture other);
private:
	SDL_Texture* mTexture;
};