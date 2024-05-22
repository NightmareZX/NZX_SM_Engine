#include "Surface.hpp"

Surface::Surface(const Surface& other) : mSurface(SDL_DuplicateSurface(other.mSurface)) {}

Surface::Surface(Surface&& other) noexcept
	: mSurface(other.mSurface)
{
	other.mSurface = nullptr;
}

Surface::Surface(SDL_Surface* surface)
{
	mSurface = surface;
}

Surface::~Surface()
{
	Dispose();
}

void Surface::Dispose()
{
	SDL_FreeSurface(mSurface);
}

Surface& Surface::operator=(Surface other)
{
	std::swap(mSurface, other.mSurface);
	return *this;
}