#include "Surface.h"


// #TODO fix the weird thing about default constructor
Surface::Surface()
{
	_Create(0, 0);
}

Surface::Surface(SDL_Surface* psurface)
{
	surface = psurface;
}

Surface::Surface(int w, int h)
{
	_Create(w, h);
}

Surface::Surface(Rect* rect)
{
	_Create(rect->w, rect->h);
}

Surface::Surface(const char * path)
{
	if (!Load(path))
		Error(SDL_GetError());
}

Surface::~Surface()
{
	_Destroy();
	
}

RGBA* Surface::operator()(int x, int y)
{
	return GetRGBA(x, y);
}

//#TODO find a way to refererence main overloaded operator from an overloaded overloaded operator MkAY?
RGBA* Surface::operator()(Point* p)
{
	return GetRGBA(p->x, p->y);
}

Surface::operator SDL_Surface*()
{
	return surface;
}

bool Surface::Fill(RGBA* color)
{
	return FillRect(GetRect(), color);
}

bool Surface::FillRect(Rect* rect, RGBA* color)
{
	if (SDL_FillRect(surface, *rect, SDL_MapRGB(surface->format, color->r, color->g, color->b)) < 0)
		return false;
	return true;
}

bool Surface::Blit(Surface* s, Rect* src, Rect* dst)
{
	if (SDL_BlitSurface(*s, *src, surface, *dst) < 0)
	{
		return false;
	}
	return true;
}

// Maybe temporarily
bool Surface::Blit(Surface* s)
{
	if (SDL_BlitSurface(*s, NULL, surface, NULL) < 0)
	{
		return false;
	}
	return true;
}

Rect* Surface::GetRect()
{
	return new Rect(&surface->clip_rect);
}

bool Surface::Save(const char* path)
{
	// #TODO Update to SDL_Image
	if (SDL_SaveBMP(surface, path) < 0)
		return false;
	return true;
}

bool Surface::Load(const char * path)
{
	// #TODO Update to SDL_Image
	surface = SDL_LoadBMP(path);
	if (surface)
		return true;
	return false;
}

RGBA* Surface::GetRGBA(int x, int y)
{
	Uint32 pixel = 0;
	Uint8 r, g, b, a = 0;
	RGBA* color = nullptr;
	
	// Hard Clipping
	/*Rect rect = Rect(0, 0, surface->w, surface->h);
	if (!rect.Collide(Point(x, y)))
		return NULL;*/

	// Mosaic
	if (x < 0) x = -x % surface->w;
	else x %= surface->w;
	if (y < 0) y = -y % surface->h;
	else y %= surface->h;

	// THREAD SAFETY
	_Lock();

	pixel = _GetPixel(x, y);

	_Unlock();
	SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
	color = new RGBA(r, g, b, a);

	return color;
}

RGBA* Surface::GetRGBA(Point* p)
{
	return GetRGBA(p->x,p->y);
}

bool Surface::_Create(int w, int h)
{
	surface = SDL_CreateRGBSurface(0, w, h, 32, NULL, NULL, NULL, NULL);	
	if (surface)
		return true;
	return false;
}

bool Surface::_Destroy()
{
	// #TODO find out why Surface get destroy while in scope
	if (surface)
	{
		SDL_FreeSurface(surface);
		return true;
	}
	return false;
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

// Copy pasted from http://sdl.beuc.net/sdl.wiki/Pixel_Access
Uint32 Surface::_GetPixel(int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

Uint32 Surface::_GetPixel(Point p)
{
	return _GetPixel(p.x, p.y);
}

// Copy pasted from http://sdl.beuc.net/sdl.wiki/Pixel_Access
void Surface::_SetPixel(int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}


