#pragma once
#include <SDL.h>
#include <utility>

class Surface
{
public:
	Surface() noexcept : mSurface(nullptr) {}
	Surface(const Surface& other);
	Surface(Surface&& other) noexcept;
	Surface(SDL_Surface* surface);
	~Surface() noexcept;

	inline int GetWidth() const { return mSurface->w; }
	inline int GetHeight() const { return mSurface->h; }
	inline SDL_Surface* GetRawSurface() { return mSurface; }
	inline bool IsNull() const { return mSurface == nullptr; };
	inline Surface&& Move() { return std::move(*this); }

	inline void Dispose();

	Surface& operator=(Surface other);
private:
	SDL_Surface* mSurface;
};