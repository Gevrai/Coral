#include "Surface.h"

// FIXME make this a better one, maybe overlay file name
// Cyan surface
static SDL_Surface* surfaceFileNotFound() {
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 100,100,32,0,0,0,0);
	SDL_FillRect(surface, NULL, 255);
	return surface;
}

Surface::Surface()
	: surface(surfaceFileNotFound()), valid(false)
{}

// FIXME Maybe make this a copy so this instance is the only owner of this surface
Surface::Surface(SDL_Surface* surface)
	: surface(surface), valid(true)
{
	if (surface == nullptr) {
		surface = surfaceFileNotFound();
		valid = false;
	}
}

Surface::Surface(const std::string path)
{
	surface = IMG_Load(path.c_str());
	if(!surface) {
		PRINT_IMG_ERROR("Could not load image!");
		surface = surfaceFileNotFound();
		valid = false;
	} else
		valid = true;
}

Surface::~Surface()
{
	SDL_FreeSurface(surface);
}

SDL_Surface* Surface::getSDL_Surface() { return surface; }

RGBA Surface::operator()(int x, int y)
{
	return GetRGBA(x, y);
}

Uint32 Surface::width() const { return surface->w; }
Uint32 Surface::height() const { return surface->h; }
bool Surface::isValid() const { return valid; }

bool Surface::Fill(RGBA* color)
{
	return FillRect(NULL, color);
}

bool Surface::FillRect(Rect* rect, RGBA* color)
{
	SDL_Rect sdlrect = rect->getSDL_Rect();
	if (SDL_FillRect(surface, &sdlrect, SDL_MapRGB(surface->format, color->r, color->g, color->b)) < 0)
		return false;
	return true;
}

bool Surface::Blit(Surface* s, Rect* src, Rect* dst)
{
	SDL_Surface* _s = s->getSDL_Surface();
	SDL_Rect _src = src->getSDL_Rect();
	SDL_Rect _dst = dst->getSDL_Rect();
	if (SDL_BlitSurface(_s, &_src, surface, &_dst) < 0)
		return false;
	return true;
}

// Maybe temporarily
bool Surface::Blit(Surface* s)
{
	SDL_Surface* _s = s->getSDL_Surface();
	if (SDL_BlitSurface(_s, NULL, surface, NULL) < 0)
		return false;
	return true;
}

Rect Surface::GetRect()
{
	return Rect(surface->clip_rect);
}

RGBA Surface::GetRGBA(int x, int y)
{
	Uint32 pixel = 0;
	Uint8 r, g, b, a = 0;

	// Mosaic
	x = MOD(x,surface->w);
	y = MOD(y,surface->h);

	// Thread safe access
	SDL_LockSurface(surface);
	pixel = _GetPixel(x, y);
	SDL_UnlockSurface(surface);

	SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
	return RGBA(r, g, b, a);
}

bool Surface::_Lock()
{
	if (SDL_MUSTLOCK(surface))
		if (SDL_LockSurface(surface) < 0)
			return false;
	return true;
}

bool Surface::_Unlock()
{
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	return true;
}

Uint32 Surface::_GetPixel(int x, int y)
{
	int bpp = surface->format->BytesPerPixel;

	if (bpp == 4) {
		Uint32* pixels = (Uint32*) surface->pixels;
		return pixels[ y*surface->w + x ];
	}
	else if (bpp == 1) {
		Uint8* pixels = (Uint8*) surface->pixels;
		return pixels[ y*surface->w + x ];
	}
	else {
		printf("Unsupported bytes per pixel of %d... Aborting.", bpp);
		exit(-1);
	}
}

void Surface::_SetPixel(int x, int y, Uint32 pixel)
{
	Uint32* pixels = (Uint32*) surface->pixels;
	pixels[ ( y * surface->w ) + x ] = pixel;
}
