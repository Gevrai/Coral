#include "Surface.h"


// #TODO fix the weird thing about default constructor
Surface::Surface()
{
	_Create(0, 0);
}

Surface::Surface(SDL_Surface* psurface)
{
	//#TODO Copying the whole thing SDL_ConvertSurface.. works for now
	//surface = SDL_ConvertSurface(s, s->format, SDL_SWSURFACE);
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

Uint32 Surface::operator()(int x, int y)
{
	return GetPixel(x, y);
}

//#TODO find a way to refererence main overloaded operator from an overloaded overloaded operator MkAY?
Uint32 Surface::operator()(Point* p)
{
	return GetPixel(p->x, p->y);
}

Surface::operator SDL_Surface*()
{
	return surface;
}

bool Surface::Fill(Uint8 r, Uint8 g, Uint8 b)
{
	return Fill(SDL_MapRGB(surface->format, r, g, b));
}

bool Surface::Fill(Uint32 pixel)
{
	if (SDL_FillRect(surface, NULL, pixel) < 0)
		return false;
	return true;
}

bool Surface::FillRect(Rect rect, Uint32 pixel)
{
	if (SDL_FillRect(surface, rect, pixel) < 0)
		return false;
	return true;
}

bool Surface::FillRect(Rect rect, Uint8 r, Uint8 g, Uint8 b)
{
	return FillRect(rect,SDL_MapRGB(surface->format, r, g, b));
}

bool Surface::Blit(Surface* s, Rect* src, Rect* dst)
{
	if (SDL_BlitSurface(*s, *src, surface, *dst) < 0)
	{
		return false;
	}
	return true;
}

// Maybe temporary
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

int Surface::GetValue(int x,int y)
{
//	__debugbreak();
	Uint32 pixel = GetPixel(x, y);

	int r = pixel >> 16 && 0xFF;
	int g = pixel >> 8 && 0xFF;
	int b = pixel && 0xFF;

//	__debugbreak();

	return r + g + b / 3;
}

int Surface::GetValue(Point* p)
{
	return GetValue(p->x, p->y);
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

Uint32 Surface::GetPixel(int x, int y)
{
	Uint32 pixel;
	
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

	return pixel;
}

Uint32 Surface::GetPixel(Point* p)
{
	return GetPixel(p->x,p->y);
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


